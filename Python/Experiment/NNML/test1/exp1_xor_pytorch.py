"""
实验1：多层感知机 PyTorch框架实现版本
"""
import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt
from tqdm import tqdm

SEED = 42
np.random.seed(SEED)
torch.manual_seed(SEED)

# ---------------------- 构建XOR数据集 ----------------------
X_np = np.array([[0, 0], [0, 1], [1, 0], [1, 1]], dtype=np.float32)
Y_np = np.array([[0], [1], [1], [0]], dtype=np.float32)

X_torch = torch.from_numpy(X_np)
Y_torch = torch.from_numpy(Y_np)

# ====================== 定义网络模型 ======================
class XORNet(nn.Module):
    def __init__(self, in_dim=2, hidden_dim=3, out_dim=1):
        super().__init__()
        self.fc1 = nn.Linear(in_dim, hidden_dim)
        self.sigmoid = nn.Sigmoid()
        self.fc2 = nn.Linear(hidden_dim, out_dim)

    def forward(self, x):
        x = self.fc1(x)
        x = self.sigmoid(x)
        x = self.fc2(x)
        x = self.sigmoid(x)
        return x

# -------- 超参数 --------
lr_torch = 0.1
max_epoch_torch = 10000

model = XORNet()
criterion = nn.MSELoss()
optimizer = optim.SGD(model.parameters(), lr=lr_torch)

torch_loss_history = []
torch_acc_history = []

print("\n======== PyTorch版本训练开始 ========")
model.train()
for epoch in tqdm(range(max_epoch_torch)):
    optimizer.zero_grad()
    pred = model(X_torch)
    loss = criterion(pred, Y_torch)

    loss.backward()
    optimizer.step()

    torch_loss_history.append(loss.item())

    # 精度
    with torch.no_grad():
        pred_class = (pred > 0.5).int()
        acc = (pred_class == Y_torch.int()).float().mean().item() * 100
        torch_acc_history.append(acc)

# 推理
model.eval()
with torch.no_grad():
    pred_out = model(X_torch)
print("\nPyTorch版本训练完成，预测结果：")
print(pred_out.numpy())
print("预测类别：", (pred_out > 0.5).int().numpy().flatten())

# 收敛轮次
converge_epoch = None
for i, l in enumerate(torch_loss_history):
    if l < 0.05:
        converge_epoch = i
        break
print(f"收敛轮次（loss<0.05）：{converge_epoch if converge_epoch else '未收敛'}")

# 绘图
plt.figure(figsize=(10, 5))
plt.plot(torch_loss_history, label="PyTorch autograd")
plt.xlabel("Epoch")
plt.ylabel("MSE Loss")
plt.title("PyTorch自动微分损失曲线")
plt.legend()
plt.grid(True)
plt.savefig("torch_loss_curve.png", dpi=150)
plt.show()

def count_torch_params(model):
    return sum(p.numel() for p in model.parameters())

print(f"PyTorch版本总参数量: {count_torch_params(model)}")
print(f"最终训练损失: {torch_loss_history[-1]:.6f}")
print(f"最终训练精度: {torch_acc_history[-1]:.2f}%")