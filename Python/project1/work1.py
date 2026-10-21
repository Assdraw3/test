import numpy as np
import matplotlib

matplotlib.use('Agg')  # 必须在导入 pyplot 之前设置
import matplotlib.pyplot as plt


# ===================== 实验1：感知器算法（蠓虫分类） =====================
class Perceptron:
    def __init__(self, learning_rate=0.1, max_iter=1000):
        self.lr = learning_rate
        self.max_iter = max_iter
        self.w = None

    def train(self, X, y):
        n_samples, n_features = X.shape
        X_aug = np.hstack([X, np.ones((n_samples, 1))])
        self.w = np.array([0.1, 0.1, 0.1])

        for epoch in range(self.max_iter):
            errors = 0
            for i in range(n_samples):
                xi = X_aug[i]
                yi = y[i]
                if yi * np.dot(self.w, xi) <= 0:
                    self.w += self.lr * yi * xi
                    errors += 1
            if errors == 0:
                print(f"感知器收敛于第 {epoch + 1} 轮")
                break
        return self.w

    def predict(self, X):
        X_aug = np.hstack([X, np.ones((X.shape[0], 1))])
        return np.sign(np.dot(X_aug, self.w))


# 训练数据（来自文档表3-1）
X_af = np.array([
    [1.24, 1.27], [1.36, 1.74], [1.38, 1.64], [1.38, 1.82],
    [1.38, 1.90], [1.40, 1.70], [1.48, 1.82], [1.54, 1.82]
])
y_af = np.ones(8)

X_apf = np.array([
    [1.14, 1.82], [1.18, 1.96], [1.20, 1.86],
    [1.26, 2.00], [1.28, 2.00], [1.30, 1.96]
])
y_apf = -np.ones(6)

X_train = np.vstack([X_af, X_apf])
y_train = np.hstack([y_af, y_apf])

# 训练感知器
perceptron = Perceptron(learning_rate=0.1)
w = perceptron.train(X_train, y_train)
print("训练得到的权向量:", w)

# 测试数据（来自文档）
test_data = np.array([
    [1.24, 1.80],  # Apf
    [1.28, 1.84],  # Apf
    [1.40, 2.04]  # Af
])
predictions = perceptron.predict(test_data)
print("测试结果:", predictions)

# 可视化训练结果并保存
plt.figure(figsize=(8, 6))
plt.scatter(X_af[:, 0], X_af[:, 1], c='red', marker='o', label='Af')
plt.scatter(X_apf[:, 0], X_apf[:, 1], c='blue', marker='*', label='Apf')
plt.scatter(test_data[:, 0], test_data[:, 1], c='black', marker='s', label='Test')

# 绘制决策边界：w1*x1 + w2*x2 + w0 = 0
x_min, x_max = X_train[:, 0].min() - 0.1, X_train[:, 0].max() + 0.1
x1_vals = np.linspace(x_min, x_max, 100)
x2_vals = -(w[0] * x1_vals + w[2]) / w[1]
plt.plot(x1_vals, x2_vals, 'g--', label='Decision Boundary')
plt.xlabel('Antenna Length')
plt.ylabel('Wing Length')
plt.title('Perceptron Classification (Midge Insects)')
plt.legend()
plt.grid(True)
plt.savefig('perceptron_result.png', dpi=300, bbox_inches='tight')
print("感知器分类结果已保存为: perceptron_result.png")
plt.close()


# ===================== 实验2：一对多两分法（三分类） =====================
def generate_3class_data(n_samples=100):
    """生成三类二维数据（三个高斯分布）"""
    np.random.seed(42)
    mean1 = [0, 0]
    mean2 = [3, 3]
    mean3 = [0, 4]
    cov = [[1, 0.5], [0.5, 1]]

    X1 = np.random.multivariate_normal(mean1, cov, n_samples // 3)
    X2 = np.random.multivariate_normal(mean2, cov, n_samples // 3)
    X3 = np.random.multivariate_normal(mean3, cov, n_samples // 3)

    X = np.vstack([X1, X2, X3])
    y = np.hstack([np.ones(n_samples // 3), 2 * np.ones(n_samples // 3), 3 * np.ones(n_samples // 3)])
    return X, y


def one_vs_rest_classifier(X, y, n_classes=3):
    """一对多分类器：为每个类别训练一个感知器"""
    classifiers = []
    for i in range(1, n_classes + 1):
        y_binary = np.where(y == i, 1, -1)
        clf = Perceptron(learning_rate=0.1, max_iter=500)
        clf.train(X, y_binary)
        classifiers.append(clf)
    return classifiers


def predict_one_vs_rest(classifiers, X):
    """预测：选择输出最大的分类器对应的类别"""
    scores = []
    for clf in classifiers:
        X_aug = np.hstack([X, np.ones((X.shape[0], 1))])
        score = np.dot(X_aug, clf.w)
        scores.append(score)
    scores = np.array(scores).T
    predictions = np.argmax(scores, axis=1) + 1
    return predictions


# 生成数据
X, y = generate_3class_data(150)
classifiers = one_vs_rest_classifier(X, y, n_classes=3)
y_pred = predict_one_vs_rest(classifiers, X)

# 计算准确率
accuracy = np.mean(y_pred == y)
print(f"\n三分类任务准确率: {accuracy * 100:.2f}%")

# 可视化分类结果并保存
plt.figure(figsize=(10, 4))

plt.subplot(1, 2, 1)
plt.scatter(X[y == 1, 0], X[y == 1, 1], c='red', alpha=0.6, label='Class 1')
plt.scatter(X[y == 2, 0], X[y == 2, 1], c='blue', alpha=0.6, label='Class 2')
plt.scatter(X[y == 3, 0], X[y == 3, 1], c='green', alpha=0.6, label='Class 3')
plt.title('Original Data (3 Classes)')
plt.legend()

plt.subplot(1, 2, 2)
plt.scatter(X[y_pred == 1, 0], X[y_pred == 1, 1], c='red', alpha=0.6, label='Class 1')
plt.scatter(X[y_pred == 2, 0], X[y_pred == 2, 1], c='blue', alpha=0.6, label='Class 2')
plt.scatter(X[y_pred == 3, 0], X[y_pred == 3, 1], c='green', alpha=0.6, label='Class 3')
plt.title('One-vs-Rest Classification Result')
plt.legend()

plt.tight_layout()
plt.savefig('one_vs_rest_result.png', dpi=300, bbox_inches='tight')
print("一对多分类结果已保存为: one_vs_rest_result.png")
plt.close()

# 打印每个分类器的权向量
print("\n各分类器权向量：")
for i, clf in enumerate(classifiers):
    print(f"Class {i + 1} 权向量: {clf.w}")


# ===================== 实验3：四分类（可选扩展） =====================
def generate_4class_data(n_samples=120):
    """生成四类二维数据"""
    np.random.seed(42)
    means = [[0, 0], [3, 3], [0, 4], [4, 0]]
    cov = [[1, 0.3], [0.3, 1]]

    X_list = []
    y_list = []
    for i, mean in enumerate(means):
        Xi = np.random.multivariate_normal(mean, cov, n_samples // 4)
        X_list.append(Xi)
        y_list.append((i + 1) * np.ones(n_samples // 4))

    X = np.vstack(X_list)
    y = np.hstack(y_list)
    return X, y


# 四分类实验
X4, y4 = generate_4class_data(120)
classifiers4 = one_vs_rest_classifier(X4, y4, n_classes=4)
y_pred4 = predict_one_vs_rest(classifiers4, X4)
accuracy4 = np.mean(y_pred4 == y4)
print(f"\n四分类任务准确率: {accuracy4 * 100:.2f}%")

# 保存四分类结果
plt.figure(figsize=(12, 4))

plt.subplot(1, 2, 1)
for i in range(1, 5):
    plt.scatter(X4[y4 == i, 0], X4[y4 == i, 1], alpha=0.6, label=f'Class {i}')
plt.title('Original Data (4 Classes)')
plt.legend()

plt.subplot(1, 2, 2)
for i in range(1, 5):
    plt.scatter(X4[y_pred4 == i, 0], X4[y_pred4 == i, 1], alpha=0.6, label=f'Class {i}')
plt.title('One-vs-Rest Classification (4 Classes)')
plt.legend()

plt.tight_layout()
plt.savefig('four_class_result.png', dpi=300, bbox_inches='tight')
print("四分类结果已保存为: four_class_result.png")
plt.close()

print("\n" + "=" * 50)
print("所有实验完成！生成的图像文件：")
print("1. perceptron_result.png  - 感知器分类结果")
print("2. one_vs_rest_result.png - 三分类结果")
print("3. four_class_result.png  - 四分类结果")
print("=" * 50)