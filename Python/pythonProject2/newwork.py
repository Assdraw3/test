import torch
import torch.nn as nn
import torch.optim as optim
from torchvision import datasets, transforms
from torch.utils.data import DataLoader
import matplotlib.pyplot as plt

# ================== 1. 设备配置 ==================
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
print(f"Using device: {device}")

# ================== 2. 数据预处理与加载 ==================
transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize((0.5,), (0.5,))  # 归一化到 [0, 1]
])

train_dataset = datasets.MNIST(root='./data', train=True, download=True, transform=transform)
test_dataset = datasets.MNIST(root='./data', train=False, download=True, transform=transform)

train_loader = DataLoader(train_dataset, batch_size=64, shuffle=True)
test_loader = DataLoader(test_dataset, batch_size=1000, shuffle=False)


# ================== 3. 模型定义 ==================
class FCNN(nn.Module):
    def __init__(self):
        super(FCNN, self).__init__()
        self.model = nn.Sequential(
            nn.Linear(28 * 28, 256),
            nn.ReLU(),
            nn.Dropout(0.2),
            nn.Linear(256, 128),
            nn.ReLU(),
            nn.Dropout(0.2),
            nn.Linear(128, 10)
        )

    def forward(self, x):
        x = x.view(x.size(0), -1)  # 展平
        return self.model(x)


model = FCNN().to(device)


# ================== 4. 训练函数 ==================
def train_model(optimizer_type='fixed', epochs=50):
    criterion = nn.CrossEntropyLoss()

    if optimizer_type == 'fixed':
        optimizer = optim.SGD(model.parameters(), lr=0.01, momentum=0.9)
        scheduler = None
    elif optimizer_type == 'decay':
        optimizer = optim.SGD(model.parameters(), lr=0.01, momentum=0.9)
        scheduler = optim.lr_scheduler.StepLR(optimizer, step_size=10, gamma=0.9)

    train_losses = []
    test_accuracies = []

    for epoch in range(epochs):
        model.train()
        running_loss = 0.0
        for data, target in train_loader:
            data, target = data.to(device), target.to(device)

            optimizer.zero_grad()
            output = model(data)
            loss = criterion(output, target)
            loss.backward()
            optimizer.step()

            running_loss += loss.item()

        if scheduler:
            scheduler.step()

        # 测试
        model.eval()
        correct = 0
        total = 0
        with torch.no_grad():
            for data, target in test_loader:
                data, target = data.to(device), target.to(device)
                output = model(data)
                _, predicted = torch.max(output.data, 1)
                total += target.size(0)
                correct += (predicted == target).sum().item()

        epoch_loss = running_loss / len(train_loader)
        epoch_acc = 100 * correct / total
        train_losses.append(epoch_loss)
        test_accuracies.append(epoch_acc)

        print(f'Epoch [{epoch + 1}/{epochs}], Loss: {epoch_loss:.4f}, Test Acc: {epoch_acc:.2f}%')

    return train_losses, test_accuracies


# ================== 5. 执行训练 ==================
# 重新初始化模型以确保公平对比
model_fixed = FCNN().to(device)
loss_fixed, acc_fixed = train_model('fixed', epochs=50)

model_decay = FCNN().to(device)
loss_decay, acc_decay = train_model('decay', epochs=50)

# ================== 6. 结果可视化 ==================
plt.figure(figsize=(12, 5))

# 损失曲线
plt.subplot(1, 2, 1)
plt.plot(loss_fixed, label='Fixed LR', color='blue')
plt.plot(loss_decay, label='Decayed LR', color='red')
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.title('Training Loss Comparison')
plt.legend()
plt.grid(True)

# 准确率曲线
plt.subplot(1, 2, 2)
plt.plot(acc_fixed, label='Fixed LR', color='blue')
plt.plot(acc_decay, label='Decayed LR', color='red')
plt.xlabel('Epoch')
plt.ylabel('Accuracy (%)')
plt.title('Test Accuracy Comparison')
plt.legend()
plt.grid(True)

# 【重要】保存图片，用于插入Word报告
plt.savefig('mnist_sgd_comparison.png', dpi=300, bbox_inches='tight')
print("图片已保存为 mnist_sgd_comparison.png")
plt.show()
