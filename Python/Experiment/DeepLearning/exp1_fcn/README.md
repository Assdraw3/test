# 实验一：全连接神经网络基础实验

## 环境依赖
见 requirements.txt

## 运行
python exp1.py

## 说明
- 数据集：Fashion-MNIST，自动下载
- 网络：784→256→128→10，ReLU，参数量 235,146
- 训练 20 epoch，batch_size=64，优化器 SGD(lr=0.01, momentum=0.9)
- 每轮记录训练/验证损失与精度，以验证集精度最优保存模型
- 最终在测试集评估，日志输出至控制台

## 输出
- 训练日志：终端输出
- 最优模型：outputs/checkpoints/best_model.pt
- 曲线图：outputs/figures/（由实验者自行生成插入报告）