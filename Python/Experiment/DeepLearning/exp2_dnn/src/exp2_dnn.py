"""
实验2：深度网络模型优化 完整补全版
基于实验1脚手架修改，不修改脚手架基础框架部分
"""
import os
import random
import numpy as np
import matplotlib
matplotlib.use('Agg')   # 避免 Tk/Tcl 报错
import matplotlib.pyplot as plt
import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, random_split
from torchvision import datasets, transforms

# ====================== 脚手架已完成部分，请勿修改 ======================
os.makedirs("outputs/figures_exp2", exist_ok=True)
os.makedirs("outputs/checkpoints_exp2", exist_ok=True)

SEED = 42
random.seed(SEED)
np.random.seed(SEED)
torch.manual_seed(SEED)
if torch.cuda.is_available():
    torch.cuda.manual_seed_all(SEED)

device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"使用设备: {device}")

transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.2860,), (0.3530,))
])

full_train_set = datasets.FashionMNIST(root="./data", train=True, download=True, transform=transform)
test_set = datasets.FashionMNIST(root="./data", train=False, download=True, transform=transform)
train_set, val_set = random_split(full_train_set, lengths=[55000, 5000])
val_set.dataset.transform = transform

BATCH_SIZE = 64
train_loader = DataLoader(train_set, batch_size=BATCH_SIZE, shuffle=True)
val_loader = DataLoader(val_set, batch_size=BATCH_SIZE, shuffle=False)
test_loader = DataLoader(test_set, batch_size=BATCH_SIZE, shuffle=False)

print(f"训练集:{len(train_set)} 验证集:{len(val_set)} 测试集:{len(test_set)}")

def train_one_epoch(model, dataloader, criterion, optimizer, device):
    model.train()
    total_loss = 0.0
    correct = 0
    total_num = 0
    for images, labels in dataloader:
        images = images.to(device)
        labels = labels.to(device)
        optimizer.zero_grad()
        outputs = model(images)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        total_loss += loss.item() * images.size(0)
        pred = torch.argmax(outputs, dim=1)
        correct += torch.sum(pred == labels).item()
        total_num += images.size(0)
    avg_loss = total_loss / total_num
    avg_acc = correct / total_num * 100.0
    return avg_loss, avg_acc

def evaluate(model, dataloader, criterion, device):
    model.eval()
    total_loss = 0.0
    correct = 0
    total_num = 0
    with torch.no_grad():
        for images, labels in dataloader:
            images = images.to(device)
            labels = labels.to(device)
            outputs = model(images)
            loss = criterion(outputs, labels)
            total_loss += loss.item() * images.size(0)
            pred = torch.argmax(outputs, dim=1)
            correct += torch.sum(pred == labels).item()
            total_num += images.size(0)
    avg_loss = total_loss / total_num
    avg_acc = correct / total_num * 100.0
    return avg_loss, avg_acc

# ====================== 【学生实现开始】 ======================
class MLP(nn.Module):
    def __init__(self, dropout_rate=0.0):
        super().__init__()
        self.dropout_rate = dropout_rate
        self.fc1 = nn.Linear(28 * 28, 256)
        self.relu1 = nn.ReLU()
        self.dropout1 = nn.Dropout(dropout_rate) if dropout_rate > 0 else nn.Identity()

        self.fc2 = nn.Linear(256, 128)
        self.relu2 = nn.ReLU()
        self.dropout2 = nn.Dropout(dropout_rate) if dropout_rate > 0 else nn.Identity()

        self.fc3 = nn.Linear(128, 10)

    def forward(self, x):
        x = x.view(x.size(0), -1)
        x = self.fc1(x)
        x = self.relu1(x)
        x = self.dropout1(x)
        x = self.fc2(x)
        x = self.relu2(x)
        x = self.dropout2(x)
        x = self.fc3(x)
        return x


# 全部实验组配置（A~G）
exp_configs = [
    # ===== 任务2：优化算法对比 =====
    {"exp_name": "A1_SGD", "dropout_rate": 0.0, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "A2_SGD_Nesterov", "dropout_rate": 0.0, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": True, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "A3_Adam", "dropout_rate": 0.0, "opt_type": "Adam", "lr": 0.001, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "A4_AdamW", "dropout_rate": 0.0, "opt_type": "AdamW", "lr": 0.001, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},

    # ===== 任务2：学习率调度对比 =====
    {"exp_name": "B1_FixedLR", "dropout_rate": 0.0, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "B2_StepLR", "dropout_rate": 0.0, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 0.0, "scheduler_type": "StepLR", "step_size": 5, "gamma": 0.5, "use_early_stop": False, "patience": 3},
    {"exp_name": "B3_Cosine", "dropout_rate": 0.0, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 0.0, "scheduler_type": "Cosine", "T_max": 20, "use_early_stop": False, "patience": 3},
    {"exp_name": "B4_ReducePlateau", "dropout_rate": 0.0, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 0.0, "scheduler_type": "ReducePlateau", "patience_lr": 3, "factor": 0.5, "use_early_stop": False, "patience": 3},

    # ===== 任务3：Dropout对比 =====
    {"exp_name": "C1_NoDropout", "dropout_rate": 0.0, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "C2_Dropout02", "dropout_rate": 0.2, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "C3_Dropout05", "dropout_rate": 0.5, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},

    # ===== 任务3：L2权重衰减对比 =====
    {"exp_name": "D1_NoWD", "dropout_rate": 0.0, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "D2_WD1e4", "dropout_rate": 0.0, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 1e-4, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "D3_WD1e3", "dropout_rate": 0.0, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 1e-3, "scheduler_type": None, "use_early_stop": False, "patience": 3},

    # ===== 任务3：早停对比 =====
    {"exp_name": "E1_NoEarlyStop", "dropout_rate": 0.0, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "E2_EarlyStop_patience3", "dropout_rate": 0.0, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": True, "patience": 3},

    # ===== 任务3：正则化组合对比 =====
    {"exp_name": "F1_NoReg", "dropout_rate": 0.0, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "F2_Dropout02", "dropout_rate": 0.2, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "F3_WD1e4", "dropout_rate": 0.0, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 1e-4, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "F4_Dropout02_WD1e4", "dropout_rate": 0.2, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 1e-4, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "F5_AllReg", "dropout_rate": 0.2, "opt_type": "SGD", "lr": 0.01, "momentum": 0.9, "nesterov": False, "weight_decay": 1e-4, "scheduler_type": None, "use_early_stop": True, "patience": 3},

    # ===== 任务4：多变量组合调优（Adam + lr×Dropout）=====
    {"exp_name": "G1", "dropout_rate": 0.0, "opt_type": "Adam", "lr": 0.001, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "G2", "dropout_rate": 0.2, "opt_type": "Adam", "lr": 0.001, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "G3", "dropout_rate": 0.5, "opt_type": "Adam", "lr": 0.001, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "G4", "dropout_rate": 0.0, "opt_type": "Adam", "lr": 0.01, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "G5", "dropout_rate": 0.2, "opt_type": "Adam", "lr": 0.01, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "G6", "dropout_rate": 0.5, "opt_type": "Adam", "lr": 0.01, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "G7", "dropout_rate": 0.0, "opt_type": "Adam", "lr": 0.1, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "G8", "dropout_rate": 0.2, "opt_type": "Adam", "lr": 0.1, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
    {"exp_name": "G9", "dropout_rate": 0.5, "opt_type": "Adam", "lr": 0.1, "weight_decay": 0.0, "scheduler_type": None, "use_early_stop": False, "patience": 3},
]


def run_single_experiment(cfg):
    epochs = 20
    model = MLP(dropout_rate=cfg["dropout_rate"]).to(device)
    total_params = sum(p.numel() for p in model.parameters())
    print(f"[{cfg['exp_name']}] 模型参数量：{total_params}")

    criterion = nn.CrossEntropyLoss()

    # 优化器
    if cfg["opt_type"] == "SGD":
        optimizer = optim.SGD(
            model.parameters(),
            lr=cfg["lr"],
            momentum=cfg.get("momentum", 0.0),
            nesterov=cfg.get("nesterov", False),
            weight_decay=cfg.get("weight_decay", 0.0)
        )
    elif cfg["opt_type"] == "Adam":
        optimizer = optim.Adam(
            model.parameters(),
            lr=cfg["lr"],
            weight_decay=cfg.get("weight_decay", 0.0)
        )
    elif cfg["opt_type"] == "AdamW":
        optimizer = optim.AdamW(
            model.parameters(),
            lr=cfg["lr"],
            weight_decay=cfg.get("weight_decay", 0.0)
        )
    else:
        raise ValueError(f"未知优化器: {cfg['opt_type']}")

    # 学习率调度器
    scheduler = None
    sched_type = cfg.get("scheduler_type", None)
    if sched_type == "StepLR":
        scheduler = optim.lr_scheduler.StepLR(optimizer, step_size=cfg["step_size"], gamma=cfg["gamma"])
    elif sched_type == "Cosine":
        scheduler = optim.lr_scheduler.CosineAnnealingLR(optimizer, T_max=cfg["T_max"])
    elif sched_type == "ReducePlateau":
        scheduler = optim.lr_scheduler.ReduceLROnPlateau(
            optimizer, mode='min', patience=cfg.get("patience_lr", 3), factor=cfg.get("factor", 0.5)
        )

    best_val_acc = 0.0
    best_val_loss = float("inf")
    best_model_path = f"outputs/checkpoints_exp2/{cfg['exp_name']}_best.pth"

    train_loss_list = []
    train_acc_list = []
    val_loss_list = []
    val_acc_list = []

    use_early_stop = cfg["use_early_stop"]
    patience = cfg["patience"]
    early_stop_counter = 0

    for epoch in range(1, epochs + 1):
        tr_loss, tr_acc = train_one_epoch(model, train_loader, criterion, optimizer, device)
        va_loss, va_acc = evaluate(model, val_loader, criterion, device)

        train_loss_list.append(tr_loss)
        train_acc_list.append(tr_acc)
        val_loss_list.append(va_loss)
        val_acc_list.append(va_acc)

        # 学习率调度
        if scheduler is not None:
            if isinstance(scheduler, optim.lr_scheduler.ReduceLROnPlateau):
                scheduler.step(va_loss)
            else:
                scheduler.step()

        # 最优模型保存（以验证精度为准）
        if va_acc > best_val_acc:
            best_val_acc = va_acc
            best_val_loss = va_loss
            torch.save(model.state_dict(), best_model_path)

        # 早停判断（基于验证损失）
        if use_early_stop:
            if va_loss < best_val_loss:
                best_val_loss = va_loss
                early_stop_counter = 0
            else:
                early_stop_counter += 1

            if early_stop_counter >= patience:
                print(f"[{cfg['exp_name']}] Early stopping at epoch {epoch}")
                break

        print(f"[{cfg['exp_name']}] Epoch:{epoch:2d} "
              f"TrLoss:{tr_loss:.4f} TrAcc:{tr_acc:.2f}% | "
              f"ValLoss:{va_loss:.4f} ValAcc:{va_acc:.2f}%")

    # 加载最优模型测试
    model.load_state_dict(torch.load(best_model_path, map_location=device))
    model.eval()
    te_loss, te_acc = evaluate(model, test_loader, criterion, device)
    print(f"\n[{cfg['exp_name']}] 测试集结果 TestLoss:{te_loss:.4f} TestAcc:{te_acc:.2f}%\n")

    history = {
        "train_loss": train_loss_list,
        "train_acc": train_acc_list,
        "val_loss": val_loss_list,
        "val_acc": val_acc_list,
        "test_loss": te_loss,
        "test_acc": te_acc,
        "params": total_params
    }
    return history


# 批量运行
all_results = dict()
for config in exp_configs:
    exp_hist = run_single_experiment(config)
    all_results[config["exp_name"]] = exp_hist

# 绘制对比图：验证精度曲线
plt.figure(figsize=(12, 5))
plt.subplot(1, 2, 1)
for exp_name, hist in all_results.items():
    plt.plot(hist["val_acc"], label=exp_name)
plt.xlabel("Epoch")
plt.ylabel("Val Acc(%)")
plt.title("Validation Accuracy Comparison")
plt.legend(fontsize=7)

plt.subplot(1, 2, 2)
for exp_name, hist in all_results.items():
    plt.plot(hist["val_loss"], label=exp_name)
plt.xlabel("Epoch")
plt.ylabel("Val Loss")
plt.title("Validation Loss Comparison")
plt.legend(fontsize=7)

plt.tight_layout()
plt.savefig("outputs/figures_exp2/compare_all.png", dpi=150)
plt.close()

print("全部实验完成！结果已保存至 outputs/")