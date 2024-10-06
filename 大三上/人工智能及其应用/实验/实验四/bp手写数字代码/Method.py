import numpy as np
from matplotlib import pyplot as plt


# 初始化权重，b->a，给b层中加入一个偏置节点
def initialise(a, b):
    epsilon = 0.15
    c = np.random.rand(a, b + 1) * (
        # 随机初始化权重在 [-epsilon, +epsilon] 范围内
            2 * epsilon) - epsilon
    return c


def loss(Theta1, Theta2, y_vect, a3, lamb, m):
    # 计算损失值
    # 正则化方法选择
    # L2正则化
    L2_Reg = (lamb / (2 * m)) * (
            np.sum(np.square(Theta1[:, 1:])) + np.sum(np.square(Theta2[:, 1:])))
    # L1正则化
    L1_Reg = (lamb / (2 * m)) * (
            np.sum(np.abs(Theta1[:, 1:])) + np.sum(np.abs(Theta2[:, 1:]))
    )
    Reg = L2_Reg
    # 交叉熵损失（Cross-Entropy Loss）
    J = (1 / m) * (np.sum(np.sum(-y_vect * np.log(a3) - (1 - y_vect) * np.log(1 - a3)))) + Reg
    # 均方误差损失（Mean Squared Error Loss）
    # J = (1 / (2 * m)) * np.sum(np.square(a3 - y_vect)) + Reg
    return J


# 进行一次正向传播来得到结果，用于预测准确率
def predict(Theta1, Theta2, X):
    m = X.shape[0]
    one_matrix = np.ones((m, 1))
    X = np.append(one_matrix, X, axis=1)  # 给第一层加入偏置参数
    z2 = np.dot(X, Theta1.transpose())
    a2 = 1 / (1 + np.exp(-z2))  # 使用Sigmoid函数激活第二层
    one_matrix = np.ones((m, 1))
    a2 = np.append(one_matrix, a2, axis=1)  # 给第二层加入偏置参数
    z3 = np.dot(a2, Theta2.transpose())
    a3 = 1 / (1 + np.exp(-z3))  # 激活第三层
    p = (np.argmax(a3, axis=1))  # 输出预测的分类
    return p


def plot_loss_and_accuracy(loss_history, train_accuracy_history, test_accuracy_history):
    # 绘制损失曲线
    plt.figure(figsize=(12, 4))
    plt.subplot(1, 2, 1)
    plt.plot(range(len(loss_history)), loss_history, label='Loss')
    plt.xlabel('Iterations')
    plt.ylabel('Loss')
    plt.title('Training Loss')

    # 绘制准确度曲线
    plt.subplot(1, 2, 2)
    plt.plot(range(len(train_accuracy_history)), train_accuracy_history, label='Train Accuracy')
    plt.plot(range(len(test_accuracy_history)), test_accuracy_history, label='Test Accuracy')
    plt.xlabel('Iterations')
    plt.ylabel('Accuracy (%)')
    plt.title('Training and Test Accuracy')
    plt.legend()  # 添加图例

    plt.tight_layout()
    plt.show()
