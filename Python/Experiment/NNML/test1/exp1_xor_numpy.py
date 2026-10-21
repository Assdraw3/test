"""
实验1：多层感知机 Numpy手动实现版本
"""
import numpy as np
import matplotlib.pyplot as plt
from tqdm import tqdm

SEED = 42
np.random.seed(SEED)

# ---------------------- 构建XOR数据集 ----------------------
X_np = np.array([[0, 0],
                 [0, 1],
                 [1, 0],
                 [1, 1]], dtype=np.float32)
Y_np = np.array([[0],
                 [1],
                 [1],
                 [0]], dtype=np.float32)

# ---------------------- 激活、损失函数 ----------------------
def sigmoid(z):
    return 1.0 / (1.0 + np.exp(-np.clip(z, -500, 500)))

def sigmoid_deriv(a):
    """a 是 sigmoid 输出值"""
    return a * (1.0 - a)

def mse_loss(y_pred, y_true):
    return np.mean((y_pred - y_true) ** 2)

# -------- 超参数 --------
lr_np = 0.1
max_epoch_np = 10000
input_dim = 2
hidden_dim = 3
output_dim = 1

# 权重初始化（He-like，小随机）
W1 = np.random.randn(input_dim, hidden_dim) * 0.5
b1 = np.zeros((1, hidden_dim))
W2 = np.random.randn(hidden_dim, output_dim) * 0.5
b2 = np.zeros((1, output_dim))

np_loss_history = []
np_acc_history = []

print("======== Numpy版本训练开始 ========")
for epoch in tqdm(range(max_epoch_np)):
    # -------- 前向传播 --------
    h1 = X_np @ W1 + b1
    a1 = sigmoid(h1)
    h2 = a1 @ W2 + b2
    y_pred_np = sigmoid(h2)

    loss = mse_loss(y_pred_np, Y_np)
    np_loss_history.append(loss)

    # 精度
    pred_class = (y_pred_np > 0.5).astype(int)
    acc = np.mean(pred_class == Y_np) * 100
    np_acc_history.append(acc)

    # -------- 反向传播（手动） --------
    # 输出层误差
    delta2 = (y_pred_np - Y_np) * sigmoid_deriv(y_pred_np)  # [4,1]
    dW2 = a1.T @ delta2 / X_np.shape[0]
    db2 = np.mean(delta2, axis=0, keepdims=True)

    # 隐藏层误差
    delta1 = (delta2 @ W2.T) * sigmoid_deriv(a1)  # [4,3]
    dW1 = X_np.T @ delta1 / X_np.shape[0]
    db1 = np.mean(delta1, axis=0, keepdims=True)

    # -------- 梯度下降 --------
    W1 -= lr_np * dW1
    b1 -= lr_np * db1
    W2 -= lr_np * dW2
    b2 -= lr_np * db2

# 训练结束推理
print("\nNumpy版本训练完成，预测结果：")
h1 = X_np @ W1 + b1
a1 = sigmoid(h1)
h2 = a1 @ W2 + b2
y_pred_final = sigmoid(h2)
print(y_pred_final)
print("预测类别：", (y_pred_final > 0.5).astype(int).flatten())

# 查找收敛轮次
converge_epoch = None
for i, l in enumerate(np_loss_history):
    if l < 0.05:
        converge_epoch = i
        break

print(f"收敛轮次（loss<0.05）：{converge_epoch if converge_epoch else '未收敛'}")

# 绘图
plt.figure(figsize=(10, 5))
plt.plot(np_loss_history, label="Numpy manual BP")
plt.xlabel("Epoch")
plt.ylabel("MSE Loss")
plt.title("Numpy手动实现损失曲线")
plt.legend()
plt.grid(True)
plt.savefig("numpy_loss_curve.png", dpi=150)
plt.show()

def count_numpy_params(W1, b1, W2, b2):
    return np.prod(W1.shape) + np.prod(b1.shape) + np.prod(W2.shape) + np.prod(b2.shape)

print(f"\nNumpy版本总参数量: {count_numpy_params(W1, b1, W2, b2)}")
print(f"最终训练损失: {np_loss_history[-1]:.6f}")
print(f"最终训练精度: {np_acc_history[-1]:.2f}%")