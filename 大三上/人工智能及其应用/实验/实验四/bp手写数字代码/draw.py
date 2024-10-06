import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


# data = [
#     (0.5, 0.01, 10, 94.09),
#     (0.5, 0.01, 50, 94.63),
#     (0.5, 0.01, 100, 94.43),
#     (0.5, 0.01, 200, 94.56),
#     (0.5, 0.1, 10, 92.85),
#     (0.5, 0.1, 50, 93.10),
#     (0.5, 0.1, 100, 92.97),
#     (0.5, 0.1, 200, 92.60),
#     (0.5, 1.0, 10, 86.64),
#     (0.5, 1.0, 50, 87.19),
#     (0.5, 1.0, 100, 86.01),
#     (0.5, 1.0, 200, 87.96),
#     (0.1, 0.01, 10, 93.22),
#     (0.1, 0.01, 50, 94.39),
#     (0.1, 0.01, 100, 94.71),
#     (0.1, 0.01, 200, 95.00),
#     (0.1, 0.1, 10, 93.37),
#     (0.1, 0.1, 50, 92.91),
#     (0.1, 0.1, 100, 92.96),
#     (0.1, 0.1, 200, 92.90),
#     (0.1, 1.0, 10, 87.17),
#     (0.1, 1.0, 50, 87.92),
#     (0.1, 1.0, 100, 88.19),
#     (0.1, 1.0, 200, 88.09),
#     (0.01, 0.01, 10, 90.60),
#     (0.01, 0.01, 50, 93.02),
#     (0.01, 0.01, 100, 94.11),
#     (0.01, 0.01, 200, 94.66),
#     (0.01, 0.1, 10, 94.60),
#     (0.01, 0.1, 50, 93.70),
#     (0.01, 0.1, 100, 92.98),
#     (0.01, 0.1, 200, 92.82),
#     (0.01, 1.0, 10, 89.76),
#     (0.01, 1.0, 50, 88.19),
#     (0.01, 1.0, 100, 88.14),
#     (0.01, 1.0, 200, 88.17),
#     (0.001, 0.01, 10, 88.50),
#     (0.001, 0.01, 50, 89.95),
#     (0.001, 0.01, 100, 91.36),
#     (0.001, 0.01, 200, 92.43),
#     (0.001, 0.1, 10, 92.48),
#     (0.001, 0.1, 50, 92.65),
#     (0.001, 0.1, 100, 92.63),
#     (0.001, 0.1, 200, 92.71),
#     (0.001, 1.0, 10, 92.64),
#     (0.001, 1.0, 50, 90.94),
#     (0.001, 1.0, 100, 88.85),
#     (0.001, 1.0, 200, 88.26)
# ]
def drawpic(data):
    alphas = [item[0] for item in data]
    lambda_regs = [item[1] for item in data]
    max_iters = [item[2] for item in data]
    accuracies = [item[3] for item in data]

    # 创建一个三维散点图
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(alphas, lambda_regs, max_iters, c=accuracies, cmap='viridis', marker='o')

    # 设置坐标轴标签
    ax.set_xlabel('Alpha')
    ax.set_ylabel('Lambda Reg')
    ax.set_zlabel('Max Iter')

    # 添加颜色条
    cbar = plt.colorbar(ax.scatter(alphas, lambda_regs, max_iters, c=accuracies, cmap='viridis', marker='o'))
    cbar.set_label('Accuracy')

    # 显示图表
    plt.show()
    data.sort(key=lambda x: (x[0], x[1], x[2]))  # 按照alpha、lambda_reg和max_iter排序


def draw_accuracy_curve(data):
    alphas = [item[0] for item in data]
    lambda_regs = [item[1] for item in data]
    max_iters = [item[2] for item in data]
    accuracies = [item[3] for item in data]

    # 创建一个新的图形
    plt.figure()

    # 绘制折线图
    plt.plot(range(len(accuracies)), accuracies, marker='o', linestyle='-')
    plt.xticks(range(len(accuracies)), [f'{alpha}, {lambda_reg}, {max_iter}' for alpha, lambda_reg, max_iter in
                                        zip(alphas, lambda_regs, max_iters)], rotation=45)
    plt.xlabel('Hyperparameters (alpha, lambda_reg, max_iter)')
    plt.ylabel('Accuracy')
    plt.title('Accuracy vs. Hyperparameters')

    # 显示图表
    plt.tight_layout()
    plt.show()