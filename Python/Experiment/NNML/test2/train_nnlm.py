import matplotlib
matplotlib.use('Agg')  # 必须在 import pyplot 之前
import matplotlib.pyplot as plt
"""
train_nnlm.py 主训练流程入口
实验2：NNLM神经网络语言模型（古诗词下一字预测）
运行：python train_nnlm.py
TODO标记为学生需要完成的代码位置
poem_data.py：数据集预处理【完整，学生不用修改】
nnlm_model.py：NNLM模型定义【学生补全网络层与forward前向传播】
"""
import os
import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
from tqdm import tqdm
import matplotlib.pyplot as plt

# 导入数据集模块（已完整实现）
from poem_data import (
    filter_and_export_poem,
    build_vocab,
    generate_window_samples,
    PoemDataset
)
# 导入模型定义模块，由学生在nnlm_model.py实现NNLM类
from nnlm_model import NNLM

# ===================== 全局配置、随机种子（保证实验可复现） =====================
SEED = 42
np.random.seed(SEED)
torch.manual_seed(SEED)

# 和实验文档保持一致的超参数
WINDOW_SIZE = 3        # 上下文窗口大小：3个汉字预测下1个汉字
EMBEDDING_DIM = 64     # 词嵌入维度
HIDDEN_DIM = 128       # MLP隐藏层神经元数
BATCH_SIZE = 32        # 批次大小
EPOCHS = 30            # 训练轮数
LR = 0.001             # Adam学习率
TXT_OUT_PATH = "poem_small.txt"

# 自动选择设备：有GPU用GPU，否则CPU
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"训练使用设备: {device}")

# ===================== 工具函数 =====================
def calc_ppl(loss_val):
    """
    计算语言模型困惑度 PPL = exp(loss)
    :param loss_val: 单轮平均交叉熵损失
    :return: 困惑度ppl
    PPL越小代表语言模型预测效果越好
    """
    if loss_val < 0:
        raise ValueError("损失值不能为负数，请检查loss计算")
    return np.exp(loss_val)


def predict_topk(model, ctx, char2id, id2char, device, k=5):
    model.eval()
    ctx_ids = [char2id[c] for c in ctx]
    ctx_tensor = torch.tensor(ctx_ids).unsqueeze(0).to(device)
    with torch.no_grad():
        logits = model(ctx_tensor)
    topk_probs, topk_indices = torch.topk(logits, k, dim=1)
    topk_ids = topk_indices[0].cpu().tolist()
    candidates = [id2char[i] for i in topk_ids]
    return candidates
    """
    TODO6：给定长度为3的汉字字符串上下文，预测top‑5候选下一个汉字
    :param model: 训练完成的NNLM模型
    :param context_chars: str，输入上下文，例如"春眠不"，长度必须等于WINDOW_SIZE=3
    :param char2id: 字符到id词典
    :param id2char: id到字符词典
    :param k: 返回候选字符数量
    :return: list[str] top‑k候选汉字列表
    """
    model.eval()
    # 校验输入上下文长度
    assert len(context_chars) == WINDOW_SIZE, f"输入上下文长度必须等于{WINDOW_SIZE}"

    # -------- TODO6‑1：把输入汉字转为id列表，OOV字符抛出异常 --------
    ctx_ids = []
    for ch in context_chars:
        if ch not in char2id:
            raise KeyError(f"字符【{ch}】不在词表中，无法做预测")
        ctx_ids.append(char2id[ch])

    # -------- TODO6‑2：转为torch张量，增加batch维度，移动到模型device --------
    # hint: tensor shape 需要变成 [1, window_size]
    # ctx_tensor = torch.tensor(...).unsqueeze(0).to(device)
    ctx_tensor = None

    # -------- TODO6‑3：推理，关闭梯度计算 torch.no_grad()，前向得到logits --------
    with torch.no_grad():
        # logits = model(ctx_tensor)
        logits = None

    # -------- TODO6‑4：对logits做topk，取出得分最高k个字符id --------
    # hint: torch.topk(), 在vocab维度取topk
    topk_ids = None

    # -------- TODO6‑5：id映射回汉字，组装候选列表返回 --------
    candidates = []

    return candidates


# ===================== 主训练入口 =====================
if __name__ == "__main__":
    # -------------------------- 步骤1：数据集处理（poem_data模块已经实现） --------------------------
    print("===== 1.预处理：筛选绝句、生成poem_small.txt =====")
    # 如果txt文件已经存在，跳过重新采样；需要重新生成数据集就手动删除poem_small.txt
    if not os.path.exists(TXT_OUT_PATH):
        filter_and_export_poem()
    else:
        print(f"{TXT_OUT_PATH} 已存在，跳过数据集导出；如需重新采样，请删除该文件。")

    print("===== 2.构建字符级词表 =====")
    char2id, id2char, vocab_size = build_vocab(TXT_OUT_PATH)
    print(f"词表大小 vocab_size = {vocab_size}")

    print("===== 3.滑动窗口生成NNLM训练样本 =====")
    contexts_np, targets_np = generate_window_samples(TXT_OUT_PATH, char2id, WINDOW_SIZE)
    print(f"总训练样本数量：{len(contexts_np)}")

    # 构建Dataset与DataLoader
    train_dataset = PoemDataset(contexts_np, targets_np)
    train_loader = torch.utils.data.DataLoader(
        train_dataset,
        batch_size=BATCH_SIZE,
        shuffle=True        # 每个epoch打乱样本顺序
    )

    # -------------------------- 步骤2：初始化模型、损失函数、优化器 --------------------------
    # 学生在 nnlm_model.py 完成NNLM网络定义
    model = NNLM(vocab_size, EMBEDDING_DIM, HIDDEN_DIM, WINDOW_SIZE).to(device)
    criterion = nn.CrossEntropyLoss()   # 多分类损失，输入logits，target为类别id
    optimizer = optim.Adam(model.parameters(), lr=LR)

    print("\n===== 开始训练 NNLM 语言模型 =====")
    # 保存训练历史，用于绘图
    train_loss_history = []
    train_ppl_history = []

    for epoch in range(EPOCHS):
        model.train()
        total_loss = 0.0
        batch_cnt = 0

        for batch_ctx, batch_tgt in tqdm(train_loader):
            optimizer.zero_grad()   # 梯度清零

            # 将张量搬运到GPU/CPU设备
            batch_ctx = batch_ctx.to(device)   # shape [B, window_size]
            batch_tgt = batch_tgt.to(device)   # shape [B,]

            # -------- TODO7：训练循环核心：前向传播、计算loss --------

            # hint: logits = model(batch_ctx) 输出shape: [B, vocab_size]
            # hint: loss = criterion(logits, batch_tgt)
            logits = model(batch_ctx)
            loss = criterion(logits, batch_tgt)

            loss.backward()     # 自动反向传播求梯度
            optimizer.step()    # 更新模型参数

            total_loss += loss.item()
            batch_cnt += 1

        # 每轮epoch结束，计算平均loss和PPL
        avg_loss = total_loss / batch_cnt
        avg_ppl = calc_ppl(avg_loss)
        train_loss_history.append(avg_loss)
        train_ppl_history.append(avg_ppl)

        print(f"Epoch [{epoch+1:2d}/{EPOCHS}] | Avg Loss:{avg_loss:.4f} | PPL:{avg_ppl:.2f}")

    # -------------------------- 训练结束：绘制损失与PPL曲线，保存图片 --------------------------
    plt.figure(figsize=(12, 4))
    # 子图1：训练损失
    plt.subplot(1, 2, 1)
    plt.plot(train_loss_history, label="Train Loss")
    plt.xlabel("Epoch")
    plt.ylabel("CrossEntropy Loss")
    plt.grid(True)
    plt.legend()

    # 子图2：困惑度PPL
    plt.subplot(1, 2, 2)
    plt.plot(train_ppl_history, label="PPL", color="orange")
    plt.xlabel("Epoch")
    plt.ylabel("PPL (Perplexity)")
    plt.grid(True)
    plt.legend()

    plt.tight_layout()
    # plt.show()        # 本地有图形界面打开；服务器无GUI注释本行
    plt.savefig("loss_ppl_curve.png", dpi=150)
    print("\n训练曲线已保存：loss_ppl_curve.png")

    # -------- TODO8：调用predict_topk，测试几组诗词上下文预测样例 --------
    test_context_list = ["春眠不", "床前明", "千山鸟"]
    for ctx in test_context_list:
        top5_result = predict_topk(model, ctx, char2id, id2char, device, k=5)
        print(f"上下文：{ctx} → top5下一字候选：{top5_result}")

    # -------- TODO9【拓展任务】词向量分析：取出embedding权重，计算汉字余弦相似度 --------
    # embedding_weight: [vocab_size, embedding_dim]
    embedding_weight = model.embedding.weight.data.cpu().numpy()
    print("\n词向量矩阵 shape：", embedding_weight.shape)
    # 学生自行补充：选取若干汉字，取出对应向量，计算余弦相似度，观察语义相近字符距离

    # 统计模型总参数量
    total_params = sum(p.numel() for p in model.parameters())
    print(f"\n模型总参数量：{total_params}")
