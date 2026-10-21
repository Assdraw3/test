"""
实验1：全连接神经网络 MNIST分类 脚手架模板
注意：补全【学生实现】标记内的代码，不要修改脚手架基础框架
"""
import os
import random
import time
import numpy as np
import matplotlib
matplotlib.use('Agg')   # 使用非交互式后端，避免 Tk/Tcl 报错
import matplotlib.pyplot as plt

import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, random_split
from torchvision import datasets, transforms

# ====================== 脚手架已完成部分，请勿修改 ======================
os.makedirs("outputs/figures", exist_ok=True)
os.makedirs("outputs/checkpoints", exist_ok=True)

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
    transforms.Normalize((0.1307,), (0.3081,))
])

full_train_set = datasets.MNIST(
    root="./data", train=True, download=True, transform=transform
)
test_set = datasets.MNIST(
    root="./data", train=False, download=True, transform=transform
)

split_generator = torch.Generator().manual_seed(SEED)
train_set, val_set = random_split(
    full_train_set,
    lengths=[55000, 5000],
    generator=split_generator
)

BATCH_SIZE = 64
train_loader = DataLoader(
    train_set,
    batch_size=BATCH_SIZE,
    shuffle=True,
    generator=torch.Generator().manual_seed(SEED)
)
val_loader = DataLoader(val_set, batch_size=BATCH_SIZE, shuffle=False)
test_loader = DataLoader(test_set, batch_size=BATCH_SIZE, shuffle=False)

print(f"训练集样本数:{len(train_set)} 验证集样本数:{len(val_set)} 测试集样本数:{len(test_set)}")

# ====================== 【学生实现开始】 ======================
# 任务1：定义全连接神经网络模型 784-128-10，激活ReLU
class MLP(nn.Module):
    def __init__(self, hidden_dim=128):
        super().__init__()
        self.fc1 = nn.Linear(28 * 28, hidden_dim)
        self.relu = nn.ReLU()
        self.fc2 = nn.Linear(hidden_dim, 10)

    def forward(self, x):
        x = x.view(x.size(0), -1)   # 展平
        x = self.fc1(x)
        x = self.relu(x)
        x = self.fc2(x)
        return x


model = MLP(hidden_dim=128).to(device)

# 任务2：定义损失函数、优化器
criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(model.parameters(), lr=0.01, momentum=0.9)

# 统计模型总参数量
total_params = sum(p.numel() for p in model.parameters())
print(f"模型总参数量: {total_params}")


# 任务3：实现训练step函数
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

        total_loss += loss.item() * labels.size(0)
        total_num += labels.size(0)
        correct += (outputs.argmax(dim=1) == labels).sum().item()

    avg_loss = total_loss / total_num
    avg_acc = 100.0 * correct / total_num
    return avg_loss, avg_acc


# 任务4：实现验证step函数
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

            total_loss += loss.item() * labels.size(0)
            total_num += labels.size(0)
            correct += (outputs.argmax(dim=1) == labels).sum().item()

    avg_loss = total_loss / total_num
    avg_acc = 100.0 * correct / total_num
    return avg_loss, avg_acc


# 任务5：主训练循环
EPOCHS = 10

train_loss_list = []
train_acc_list = []
val_loss_list = []
val_acc_list = []

best_val_acc = 0.0
best_epoch = 0
best_model_path = "outputs/checkpoints/best_model.pt"

total_start_time = time.time()

for epoch in range(1, EPOCHS + 1):
    epoch_start_time = time.time()

    epoch_train_loss, epoch_train_acc = train_one_epoch(
        model, train_loader, criterion, optimizer, device
    )
    epoch_val_loss, epoch_val_acc = evaluate(
        model, val_loader, criterion, device
    )

    epoch_time = time.time() - epoch_start_time

    train_loss_list.append(epoch_train_loss)
    train_acc_list.append(epoch_train_acc)
    val_loss_list.append(epoch_val_loss)
    val_acc_list.append(epoch_val_acc)

    if epoch_val_acc > best_val_acc:
        best_val_acc = epoch_val_acc
        best_epoch = epoch
        torch.save(model.state_dict(), best_model_path)

    print(f"Epoch [{epoch}/{EPOCHS}] "
          f"Train Loss:{epoch_train_loss:.4f} Train Acc:{epoch_train_acc:.2f}% | "
          f"Val Loss:{epoch_val_loss:.4f} Val Acc:{epoch_val_acc:.2f}% | "
          f"Time:{epoch_time:.2f}s")

total_time = time.time() - total_start_time
print(f"总训练时间: {total_time:.2f} 秒")

best_val_loss = min(val_loss_list)
print(f"验证集最优损失: {best_val_loss:.4f}")
print(f"最优验证精度: {best_val_acc:.2f}% (Epoch {best_epoch})")


# 加载最优模型，在测试集评估
model.load_state_dict(
    torch.load(best_model_path, map_location=device, weights_only=True)
)
test_loss, test_acc = evaluate(model, test_loader, criterion, device)

print(f"\n【测试集结果】Test Loss:{test_loss:.4f} Test Acc:{test_acc:.2f}%")


# 任务6：绘制损失&精度曲线
plt.figure(figsize=(12, 5))

plt.subplot(1, 2, 1)
plt.plot(train_loss_list, label="Train")
plt.plot(val_loss_list, label="Val")
plt.xlabel("Epoch")
plt.ylabel("Loss")
plt.title("Loss Curve")
plt.legend()

plt.subplot(1, 2, 2)
plt.plot(train_acc_list, label="Train")
plt.plot(val_acc_list, label="Val")
plt.xlabel("Epoch")
plt.ylabel("Accuracy (%)")
plt.title("Accuracy Curve")
plt.legend()

plt.tight_layout()
plt.savefig("outputs/figures/result.png", dpi=150)
plt.close()

# ========= 【学生实现结束】 =========