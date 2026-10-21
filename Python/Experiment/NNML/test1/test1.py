# ============================================================
# NNLM（MLP 版）实验：含训练、PPL、绘图、结果统计
# 用法：python test1.py
# 依赖：pip install torch matplotlib
# 运行后会在当前目录生成：
#   loss_curve.png      训练损失曲线
#   ppl_compare.png     NNLM vs 线性模型 PPL 对比
#   results.json        实验结果汇总
# ============================================================
import json
import math
import os

import torch
import torch.nn as nn
import torch.optim as optim

# 绘图开关：没有 matplotlib 也不影响训练
try:
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
    from matplotlib import font_manager
    _HAS_PLOT = True
except ImportError:
    _HAS_PLOT = False


# ============================================================
# 1. 数据加载与预处理（字级别）
# ============================================================
def load_data(file_path):
    sentences = []
    with open(file_path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if line:
                sentences.append(list(line))
    return sentences


# ============================================================
# 2. 构建词表
# ============================================================
def build_vocab(sentences):
    vocab = set()
    for s in sentences:
        vocab.update(s)
    word2idx = {w: i for i, w in enumerate(sorted(vocab))}
    idx2word = {i: w for w, i in word2idx.items()}
    return word2idx, idx2word, len(vocab)


# ============================================================
# 3. 构造训练样本（滑动窗口）
# ============================================================
def build_dataset(sentences, word2idx, window_size=3):
    X, Y = [], []
    for s in sentences:
        if len(s) <= window_size:
            continue
        for i in range(len(s) - window_size):
            X.append([word2idx[w] for w in s[i:i + window_size]])
            Y.append(word2idx[s[i + window_size]])
    return torch.tensor(X), torch.tensor(Y)


# ============================================================
# 4. NNLM（MLP 版）
# ============================================================
class NNLM(nn.Module):
    def __init__(self, vocab_size, embed_dim, hidden_dim, window_size):
        super(NNLM, self).__init__()
        self.embedding = nn.Embedding(vocab_size, embed_dim)
        self.mlp = nn.Sequential(
            nn.Linear(embed_dim * window_size, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, vocab_size),
        )

    def forward(self, x):
        emb = self.embedding(x).view(x.size(0), -1)
        return self.mlp(emb)


# ============================================================
# 5. 线性模型（无隐藏层，对比用）
# ============================================================
class LinearNNLM(nn.Module):
    def __init__(self, vocab_size, embed_dim, window_size):
        super(LinearNNLM, self).__init__()
        self.embedding = nn.Embedding(vocab_size, embed_dim)
        self.linear = nn.Linear(embed_dim * window_size, vocab_size)

    def forward(self, x):
        emb = self.embedding(x).view(x.size(0), -1)
        return self.linear(emb)


# ============================================================
# 6. 训练（返回每轮 loss 记录）
# ============================================================
def train(model, X, Y, epochs=100, lr=1e-3, log_every=10):
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.Adam(model.parameters(), lr=lr)
    model.train()
    loss_history = []                 # ★ 新增：记录每轮 loss
    for epoch in range(epochs):
        logits = model(X)
        loss = criterion(logits, Y)
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        loss_history.append(loss.item())
        if epoch % log_every == 0:
            print(f"[Epoch {epoch}] Loss: {loss.item():.4f}")
    return loss_history


# ============================================================
# 7. 困惑度 PPL（全程 tensor，避免 .item() bug）
# ============================================================
@torch.no_grad()
def compute_ppl(model, X, Y):
    model.eval()
    probs = torch.softmax(model(X), dim=-1)
    true_probs = probs[range(len(Y)), Y]
    return float(torch.exp(-torch.log(true_probs).mean()))  # 本身就是 float


# ============================================================
# 8. 词向量查看
# ============================================================
@torch.no_grad()
def show_embeddings(model, idx2word, top_k=10):
    embeddings = model.embedding.weight.data
    print("\n示例词向量：")
    for i in range(min(top_k, embeddings.shape[0])):
        print(f"{idx2word[i]} : {embeddings[i].numpy()}")


# ============================================================
# 9. 绘图（★ 新增）
# ============================================================
def setup_chinese_font():
    if not _HAS_PLOT:
        return
    for fp in [
        r"C:\Windows\Fonts\msyh.ttc",      # 本机有微软雅黑就用它
        r"C:\Windows\Fonts\simhei.ttf",
    ]:
        if os.path.exists(fp):
            try:
                font_manager.fontManager.addfont(fp)
                plt.rcParams["font.sans-serif"] = [font_manager.FontProperties(fname=fp).get_name()]
                break
            except Exception:
                pass
    plt.rcParams["axes.unicode_minus"] = False


def plot_loss_curve(loss_history, save_path="loss_curve.png"):
    if not _HAS_PLOT:
        return
    plt.figure(figsize=(7.2, 4.2), dpi=150)
    plt.plot(range(len(loss_history)), loss_history, color="#1F3A5F", linewidth=1.8)
    plt.xlabel("Epoch（训练轮次）")
    plt.ylabel("Cross-Entropy Loss")
    plt.title("NNLM 训练损失收敛曲线")
    plt.grid(True, linestyle="--", alpha=0.4)
    plt.tight_layout()
    plt.savefig(save_path)
    plt.close()
    print(f"已保存：{save_path}")


def plot_ppl_compare(records, save_path="ppl_compare.png"):
    if not _HAS_PLOT:
        return
    names = [r["name"] for r in records]
    ppls = [r["ppl"] for r in records]
    colors = ["#1F3A5F"] * (len(records) - 1) + ["#C0504D"]
    plt.figure(figsize=(7.2, 4.0), dpi=150)
    bars = plt.bar(names, ppls, color=colors, width=0.6)
    for b, p in zip(bars, ppls):
        plt.text(b.get_x() + b.get_width() / 2, p + 0.1,
                 f"{p:.2f}", ha="center", va="bottom", fontsize=9)
    plt.ylabel("困惑度 PPL（越低越好）")
    plt.title("NNLM 与线性模型的困惑度对比")
    plt.tick_params(axis="x", labelsize=9)
    plt.ylim(0, max(ppls) * 1.25)
    plt.tight_layout()
    plt.savefig(save_path)
    plt.close()
    print(f"已保存：{save_path}")


# ============================================================
# 10. 主函数
# ============================================================
def main():
    setup_chinese_font()

    file_path = "data_exp1.txt"
    window_size = 3
    embed_dim = 16
    hidden_dim = 64
    epochs = 100

    sentences = load_data(file_path)
    word2idx, idx2word, vocab_size = build_vocab(sentences)
    X, Y = build_dataset(sentences, word2idx, window_size)
    print(f"词表大小: {vocab_size}")
    print(f"训练样本数: {len(X)}")

    # ---- 实验一：NNLM ----
    print("\n===== 训练 NNLM（含隐藏层）=====")
    model = NNLM(vocab_size, embed_dim, hidden_dim, window_size)
    loss_history = train(model, X, Y, epochs=epochs)
    ppl = compute_ppl(model, X, Y)
    print(f"NNLM PPL: {ppl:.2f}")
    show_embeddings(model, idx2word)

    # ---- 实验二：线性模型 ----
    # ---- 实验二：线性模型 ----
    print("\n===== 训练 LinearNNLM（无隐藏层）=====")
    linear_model = LinearNNLM(vocab_size, embed_dim, window_size)
    train(linear_model, X, Y, epochs=epochs)

    with torch.no_grad():
        linear_ppl = compute_ppl(linear_model, X, Y)
        linear_loss = torch.nn.CrossEntropyLoss()(linear_model(X), Y)

    print(f"LinearNNLM PPL: {linear_ppl:.2f}")

    # ---- 结果汇总 ----
    records = [
        {
            "name": f"NNLM(h={hidden_dim})",
            "hidden_dim": hidden_dim,
            "final_loss": round(loss_history[-1], 4),
            "ppl": round(ppl, 4),
        },
        {
            "name": "Linear（无隐藏层）",
            "hidden_dim": 0,
            "final_loss": round(float(linear_loss.detach()), 4),
            "ppl": round(linear_ppl, 4),
        },
    ]

    # ---- 结果汇总（★ 新增）----

    with open("results.json", "w", encoding="utf-8") as f:
        json.dump({
            "vocab_size": vocab_size,
            "train_samples": len(X),
            "window_size": window_size,
            "epochs": epochs,
            "results": records,
        }, f, ensure_ascii=False, indent=2)
    print("\n已保存：results.json")

    # ---- 绘图 ----
    if _HAS_PLOT:
        plot_loss_curve(loss_history, "loss_curve.png")
        plot_ppl_compare(records, "ppl_compare.png")
    else:
        print("\n提示：未安装 matplotlib，跳过绘图。安装：pip install matplotlib")


if __name__ == "__main__":
    main()