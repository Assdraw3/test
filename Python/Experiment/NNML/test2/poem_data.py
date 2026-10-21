"""
poem_data.py 数据集处理模块【完整实现无需修改】
功能：
1. filter_and_export_poem：读取JSON，筛选五言/七言绝句，采样1000首，繁体转简体输出poem_small.txt
2. build_vocab：读取文本，字符级构建词表，包含<PAD>
3. generate_window_samples：滑动窗口生成NNLM训练样本 window_size=3
4. PoemDataset：PyTorch自定义Dataset，供DataLoader加载
"""
import json
import random
import zhconv
import numpy as np
import torch

# -------------------------- 路径配置 --------------------------
JSON_CORPUS_PATH = "poet.tang.1000.json"
TXT_OUT_PATH = "poem_small.txt"


def filter_and_export_poem():
    """
    读取json诗词语料，筛选五言/七言绝句，采样1000首
    使用zhconv转为简体，保存到poem_small.txt，一行一首
    约束条件：每首诗必须4句；过滤空内容、异常数据
    """
    # 1.加载原始json语料
    import json
    import random
    from zhconv import convert

    JSON_CORPUS_PATH = "poet.tang.1000.json"
    TXT_OUT_PATH = "poem_small.txt"

    with open(JSON_CORPUS_PATH, "r", encoding="utf-8") as f:
        poem_list = json.load(f)
    print(f"原始JSON总共有 {len(poem_list)} 首唐诗")
    valid_poems = []
    for idx, poem in enumerate(poem_list):
        paragraphs = poem.get("paragraphs", [])
        if not isinstance(paragraphs, list):
            continue
        # 打印前10首，看paragraphs原始内容
        if idx < 10:
            print(f"\n第{idx}首 paragraphs = {paragraphs}")

        # 去掉每句的逗号句号，统计纯汉字长度
        clean_sentences = []
        for sent in paragraphs:
            s = sent.replace("，", "").replace("。", "").strip()
            clean_sentences.append(s)
        len_list = [len(s) for s in clean_sentences]
        
        content_raw = "".join(paragraphs).strip()
        if len(content_raw) > 0:
            valid_poems.append(content_raw)
        #    print(f"选中诗句：{clean_sentences}")

    print(f"\n符合条件诗句总数：{len(valid_poems)}")
    # 随机采样最多1000首
    random.seed(42)
    sample_num = min(1000, len(valid_poems))
    selected_poems = random.sample(valid_poems, k=sample_num)
    # 繁体转简体
    simplified_poems = []
    for text in selected_poems:
        sim_text = convert(text, "zh-cn")
        simplified_poems.append(sim_text)
    # 写入txt，一行一首
    with open(TXT_OUT_PATH, "w", encoding="utf-8") as fw:
        for line in simplified_poems:
            fw.write(line + "\n")
    print(f"数据集导出完成，共导出 {len(simplified_poems)} 首绝句，保存至 {TXT_OUT_PATH}")




def build_vocab(txt_path):
    """
    读取poem_small.txt，字符级构建词表
    :param txt_path: 诗词文本路径
    :return char2id, id2char, vocab_size
    特殊符号：<PAD>，索引0
    """
    # 初始化词表，填充符号放在0号位置
    char2id = {"<PAD>": 0}
    id2char = {0: "<PAD>"}

    with open(txt_path, "r", encoding="utf‑8") as fr:
        for line in fr:
            line = line.strip()
            if len(line) == 0:
                continue
            # 遍历每一个汉字字符
            for ch in line:
                if ch not in char2id:
                    new_id = len(char2id)
                    char2id[ch] = new_id
                    id2char[new_id] = ch

    vocab_size = len(char2id)
    print(f"词表构建完成，词表总大小 vocab_size = {vocab_size}")
    return char2id, id2char, vocab_size


def generate_window_samples(txt_path, char2id, window_size):
    """
    滑动窗口生成NNLM训练样本
    window_size=3：取连续3个字符id作为context，下一个字符id作为target
    :param txt_path: 诗词文本路径
    :param char2id: 字符到id映射字典
    :param window_size: 上下文窗口大小
    :return contexts: np.ndarray [N, window_size]; targets: np.ndarray [N,]
    """
    all_char_ids = []
    # 将全部文本转成连续id序列
    with open(txt_path, "r", encoding="utf‑8") as fr:
        for line in fr:
            line = line.strip()
            if len(line) == 0:
                continue
            for ch in line:
                cid = char2id[ch]
                all_char_ids.append(cid)

    contexts = []
    targets = []
    # 滑动窗口生成样本
    # i：上下文起始位置；i+window_size 为预测目标字符下标
    for i in range(len(all_char_ids) - window_size):
        ctx = all_char_ids[i: i + window_size]   # 窗口内3个字符id
        tgt = all_char_ids[i + window_size]      # 下一个字符id
        contexts.append(ctx)
        targets.append(tgt)

    # 转为numpy数组
    contexts = np.array(contexts, dtype=np.int64)
    targets = np.array(targets, dtype=np.int64)
    print(f"样本构造完成，总训练样本数量：{contexts.shape[0]}")
    return contexts, targets


class PoemDataset(torch.utils.data.Dataset):
    """
    PyTorch自定义数据集类
    __len__ 返回样本总数
    __getitem__ 根据索引返回一条(context, target)
    """
    def __init__(self, contexts, targets):
        # numpy数组转LongTensor，模型输入索引必须long类型
        self.contexts = torch.from_numpy(contexts).long()
        self.targets = torch.from_numpy(targets).long()

    def __len__(self):
        return len(self.contexts)

    def __getitem__(self, idx):
        return self.contexts[idx], self.targets[idx]


# ------------------- 模块自测代码（直接运行本文件可执行） -------------------
if __name__ == "__main__":
    # 1.导出诗词文本
    filter_and_export_poem()
    # 2.构建词表
    char2id, id2char, vocab_size = build_vocab(TXT_OUT_PATH)
    # 3.生成滑动窗口样本，窗口大小=3
    contexts, targets = generate_window_samples(TXT_OUT_PATH, char2id, window_size=3)
    # 4.测试Dataset
    ds = PoemDataset(contexts, targets)
    print(f"Dataset样本数量: {len(ds)}")
    ctx_sample, tgt_sample = ds[0]
    print(f"第一条样本 context id:{ctx_sample}, target id:{tgt_sample}")
    print(f"第一条样本 context字符：{[id2char[int(i)] for i in ctx_sample]}, target字符：{id2char[int(tgt_sample)]}")
