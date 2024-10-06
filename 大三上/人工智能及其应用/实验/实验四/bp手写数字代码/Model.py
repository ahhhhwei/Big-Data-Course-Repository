import numpy as np
from Method import loss


# 进行一次向前传播和向后传播，并返回损失和梯度
def neural_network(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y, lamb):
    # 分割获得三个层次之间两两的权重
    Theta1 = np.reshape(nn_params[:hidden_layer_size * (input_layer_size + 1)],
                        (hidden_layer_size, input_layer_size + 1))
    Theta2 = np.reshape(nn_params[hidden_layer_size * (input_layer_size + 1):],
                        (num_labels, hidden_layer_size + 1))

    # 向前传播
    m = X.shape[0]
    one_matrix = np.ones((m, 1))
    X = np.append(one_matrix, X, axis=1)  # 向输入层添加偏置单元，使之成为偏差节点
    a1 = X
    z2 = np.dot(X, Theta1.transpose())
    a2 = 1 / (1 + np.exp(-z2))  # 采用Sigmoid函数对隐藏层进行激活
    one_matrix = np.ones((m, 1))
    a2 = np.append(one_matrix, a2, axis=1)  # 向隐藏层添加偏置单元，使之成为偏差节点
    z3 = np.dot(a2, Theta2.transpose())
    a3 = 1 / (1 + np.exp(-z3))  # 采用Sigmoid函数对输出层进行激活
    # 将标签改为一个长度为10的布尔向量，在向量的10个布尔数值里，哪个数等于1，它就代表着几
    y_vect = np.zeros((m, 10))
    for i in range(m):
        y_vect[i, int(y[i])] = 1

    # 计算损失值
    J = loss(Theta1, Theta2, y_vect, a3, lamb, m)

    # 向后传播
    Delta3 = a3 - y_vect
    Delta2 = np.dot(Delta3, Theta2) * a2 * (1 - a2)
    Delta2 = Delta2[:, 1:]

    # 计算梯度
    Theta1[:, 0] = 0
    Theta1_grad = (1 / m) * np.dot(Delta2.transpose(), a1) + (lamb / m) * Theta1
    Theta2[:, 0] = 0
    Theta2_grad = (1 / m) * np.dot(Delta3.transpose(), a2) + (lamb / m) * Theta2
    grad = np.concatenate((Theta1_grad.flatten(), Theta2_grad.flatten()))

    return J, grad
