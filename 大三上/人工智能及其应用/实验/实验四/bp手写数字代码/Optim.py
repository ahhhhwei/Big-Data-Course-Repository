import random

import numpy as np

from Model import neural_network
from Accuracy import accuracy
from Method import plot_loss_and_accuracy


def BGD(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y, lambda_reg, iter_num, alpha_rate, X_test,
        y_test):
    # 创建空列表来存储损失和准确度
    loss_history = []
    train_accuracy_history = []  # 用于存储训练集准确度的历史数据
    test_accuracy_history = []  # 用于存储测试集准确度的历史数据

    for i in range(iter_num):
        cost, grad = neural_network(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y, lambda_reg)
        nn_params -= alpha_rate * grad
        loss_history.append(cost)

        # 计算并记录训练集和测试集准确度
        train_accuracy, test_accuracy = accuracy(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y,
                                                 X_test, y_test)
        train_accuracy_history.append(train_accuracy)
        test_accuracy_history.append(test_accuracy)

        print(f"Iteration {i}: Cost {cost}")
        print('Training Set Accuracy: {:f}'.format(train_accuracy))
        print('Test Set Accuracy: {:f}'.format(test_accuracy))

    plot_loss_and_accuracy(loss_history, train_accuracy_history, test_accuracy_history)
    return nn_params


def SGD(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y, lambda_reg, iter_num, alpha_rate, X_test,
        y_test):
    batch_size = 1
    m = X.shape[0]
    # 创建空列表来存储损失和准确度
    loss_history = []
    train_accuracy_history = []  # 用于存储训练集准确度的历史数据
    test_accuracy_history = []  # 用于存储测试集准确度的历史数据

    for i in range(iter_num):
        indices = list(range(m))
        random.shuffle(indices)
        totalcost = 0
        for j in range(0, m, batch_size):
            batch_indices = indices[j:j + batch_size]
            X_batch = X[batch_indices]
            y_batch = y[batch_indices]

            cost, grad = neural_network(nn_params, input_layer_size, hidden_layer_size, num_labels, X_batch, y_batch,
                                        lambda_reg)
            nn_params -= alpha_rate * grad
            totalcost += cost
        train_accuracy, test_accuracy = accuracy(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y,
                                                 X_test, y_test)
        train_accuracy_history.append(train_accuracy)
        test_accuracy_history.append(test_accuracy)
        loss_history.append(totalcost / m)
        print(f"Iteration {i}: Cost {totalcost / m}")
        print('Training Set Accuracy: {:f}'.format(train_accuracy))
        print('Test Set Accuracy: {:f}'.format(test_accuracy))

    plot_loss_and_accuracy(loss_history, train_accuracy_history, test_accuracy_history)

    return nn_params


def OGD(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y, lambda_reg, iter_num, alpha_rate, X_test,
        y_test):
    batch_size = 32
    m = X.shape[0]
    # 创建空列表来存储损失和准确度
    loss_history = []
    train_accuracy_history = []  # 用于存储训练集准确度的历史数据
    test_accuracy_history = []  # 用于存储测试集准确度的历史数据

    for i in range(iter_num):
        indices = list(range(m))
        totalcost = 0
        for j in range(0, m, batch_size):
            batch_indices = indices[j:j + batch_size]
            X_batch = X[batch_indices]
            y_batch = y[batch_indices]

            cost, grad = neural_network(nn_params, input_layer_size, hidden_layer_size, num_labels, X_batch, y_batch,
                                        lambda_reg)
            totalcost += cost
            nn_params -= alpha_rate * grad
        loss_history.append(totalcost / m)
        train_accuracy, test_accuracy = accuracy(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y,
                                                 X_test, y_test)
        train_accuracy_history.append(train_accuracy)
        test_accuracy_history.append(test_accuracy)
        print(f"Iteration {i}: Cost {totalcost / m}")
        print('Training Set Accuracy: {:f}'.format(train_accuracy))
        print('Test Set Accuracy: {:f}'.format(test_accuracy))
    plot_loss_and_accuracy(loss_history, train_accuracy_history, test_accuracy_history)

    return nn_params


def MiniBGD(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y, lambda_reg, iter_num, alpha_rate, X_test,
            y_test):
    batch_size = 64
    m = X.shape[0]
    loss_history = []
    train_accuracy_history = []  # 用于存储训练集准确度的历史数据
    test_accuracy_history = []  # 用于存储测试集准确度的历史数据
    for i in range(iter_num):
        # 随机打乱数据和标签，以创建随机的小批次
        indices = list(range(m))
        random.shuffle(indices)
        totalcost = 0
        for j in range(0, m, batch_size):
            batch_indices = indices[j:j + batch_size]
            X_batch = X[batch_indices]
            y_batch = y[batch_indices]

            cost, grad = neural_network(nn_params, input_layer_size, hidden_layer_size, num_labels, X_batch, y_batch,
                                        lambda_reg)
            nn_params -= alpha_rate * grad
            totalcost += cost
        loss_history.append(totalcost / batch_size)
        train_accuracy, test_accuracy = accuracy(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y,
                                                 X_test, y_test)
        train_accuracy_history.append(train_accuracy)
        test_accuracy_history.append(test_accuracy)
        print(f"Iteration {i}: Cost {totalcost / batch_size}")
        print('Training Set Accuracy: {:f}'.format(train_accuracy))
        print('Test Set Accuracy: {:f}'.format(test_accuracy))
    plot_loss_and_accuracy(loss_history, train_accuracy_history, test_accuracy_history)

    return nn_params


def Momentum(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y, lambda_reg, iter_num, alpha_rate, X_test,
             y_test):
    beta = 0.9
    # 初始化动量向量
    v = np.zeros(nn_params.shape)
    # 创建空列表来存储损失和准确度
    loss_history = []
    train_accuracy_history = []  # 用于存储训练集准确度的历史数据
    test_accuracy_history = []  # 用于存储测试集准确度的历史数据
    m = X.shape[0]  # 总样本数
    batch_size = 64
    for i in range(iter_num):
        totalcost = 0
        # 随机打乱数据和标签，以创建随机的小批次
        indices = list(range(m))
        random.shuffle(indices)
        for j in range(0, m, batch_size):
            batch_indices = indices[j:j + batch_size]
            X_batch = X[batch_indices]
            y_batch = y[batch_indices]
            cost, grad = neural_network(nn_params, input_layer_size, hidden_layer_size, num_labels, X_batch, y_batch,
                                        lambda_reg)
            # 更新动量
            v = beta * v + alpha_rate * grad
            # 更新参数
            nn_params -= v
            totalcost += cost

        # 计算并记录训练集和测试集准确度
        train_accuracy, test_accuracy = accuracy(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y,
                                                 X_test, y_test)
        train_accuracy_history.append(train_accuracy)
        test_accuracy_history.append(test_accuracy)
        loss_history.append(totalcost / batch_size)
        print(f"Iteration {i}: Cost {totalcost / batch_size}")
        print('Training Set Accuracy: {:f}'.format(train_accuracy))
        print('Test Set Accuracy: {:f}'.format(test_accuracy))

    plot_loss_and_accuracy(loss_history, train_accuracy_history, test_accuracy_history)
    return nn_params


def Adagrad(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y, lambda_reg, iter_num, alpha_rate, X_test,
            y_test):
    epsilon = 1e-8
    # 初始化梯度平方累积
    G = np.zeros(nn_params.shape)
    # 创建空列表来存储损失和准确度
    loss_history = []
    train_accuracy_history = []  # 用于存储训练集准确度的历史数据
    test_accuracy_history = []  # 用于存储测试集准确度的历史数据
    m = X.shape[0]  # 总样本数
    batch_size = 64
    for i in range(iter_num):
        totalcost = 0
        # 随机打乱数据和标签，以创建随机的小批次
        indices = list(range(m))
        random.shuffle(indices)
        for j in range(0, m, batch_size):
            batch_indices = indices[j:j + batch_size]
            X_batch = X[batch_indices]
            y_batch = y[batch_indices]
            cost, grad = neural_network(nn_params, input_layer_size, hidden_layer_size, num_labels, X_batch, y_batch,
                                        lambda_reg)
            # 更新梯度平方累积
            G += np.square(grad)
            # 计算适应的学习率
            alpha = alpha_rate / np.sqrt(G + epsilon)
            # 更新参数
            nn_params -= alpha * grad
            totalcost += cost
        # 计算并记录训练集和测试集准确度
        train_accuracy, test_accuracy = accuracy(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y,
                                                 X_test, y_test)
        train_accuracy_history.append(train_accuracy)
        test_accuracy_history.append(test_accuracy)
        loss_history.append(totalcost / batch_size)

        print(f"Iteration {i}: Cost {totalcost / batch_size}")
        print('Training Set Accuracy: {:f}'.format(train_accuracy))
        print('Test Set Accuracy: {:f}'.format(test_accuracy))
    plot_loss_and_accuracy(loss_history, train_accuracy_history, test_accuracy_history)
    return nn_params


def Adam(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y, lambda_reg, iter_num, alpha_rate, X_test,
         y_test):
    beta1 = 0.9
    beta2 = 0.999
    epsilon = 1e-8
    # 初始化一阶矩和二阶矩
    m = np.zeros(nn_params.shape)
    v = np.zeros(nn_params.shape)
    t = 0
    # 创建空列表来存储损失和准确度
    loss_history = []
    train_accuracy_history = []  # 用于存储训练集准确度的历史数据
    test_accuracy_history = []  # 用于存储测试集准确度的历史数据
    M = X.shape[0]  # 总样本数
    batch_size = 64
    for i in range(iter_num):
        totalcost = 0
        # 随机打乱数据和标签，以创建随机的小批次
        indices = list(range(M))
        random.shuffle(indices)
        for j in range(0, M, batch_size):
            batch_indices = indices[j:j + batch_size]
            X_batch = X[batch_indices]
            y_batch = y[batch_indices]
            cost, grad = neural_network(nn_params, input_layer_size, hidden_layer_size, num_labels, X_batch, y_batch,
                                        lambda_reg)
            t += 1
            # 更新一阶矩和二阶矩
            m = beta1 * m + (1 - beta1) * grad
            v = beta2 * v + (1 - beta2) * (grad ** 2)
            # 偏差修正
            m_hat = m / (1 - beta1 ** t)
            v_hat = v / (1 - beta2 ** t)
            # 计算适应的学习率
            alpha = alpha_rate / (np.sqrt(v_hat) + epsilon)
            # 更新参数
            nn_params -= alpha * m_hat
            totalcost += cost
        # 计算并记录训练集和测试集准确度
        train_accuracy, test_accuracy = accuracy(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y,
                                                 X_test, y_test)
        train_accuracy_history.append(train_accuracy)
        test_accuracy_history.append(test_accuracy)
        loss_history.append(totalcost / batch_size)
        print(f"Iteration {i}: Cost {totalcost / batch_size}")
        print('Training Set Accuracy: {:f}'.format(train_accuracy))
        print('Test Set Accuracy: {:f}'.format(test_accuracy))

    plot_loss_and_accuracy(loss_history, train_accuracy_history, test_accuracy_history)
    return nn_params


def Adamax(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y, lambda_reg, iter_num, alpha_rate, X_test,
           y_test):
    beta1 = 0.9
    beta2 = 0.999
    epsilon = 1e-8
    # 初始化一阶矩和 max 累积
    m = np.zeros(nn_params.shape)
    u = np.zeros(nn_params.shape)

    # 创建空列表来存储损失和准确度
    loss_history = []
    train_accuracy_history = []  # 用于存储训练集准确度的历史数据
    test_accuracy_history = []  # 用于存储测试集准确度的历史数据
    M = X.shape[0]  # 总样本数
    batch_size = 32
    for i in range(iter_num):
        totalcost = 0
        # 随机打乱数据和标签，以创建随机的小批次
        indices = list(range(M))
        random.shuffle(indices)
        for j in range(0, M, batch_size):
            batch_indices = indices[j:j + batch_size]
            X_batch = X[batch_indices]
            y_batch = y[batch_indices]
            cost, grad = neural_network(nn_params, input_layer_size, hidden_layer_size, num_labels, X_batch, y_batch,
                                        lambda_reg)
            # 更新一阶矩和 max 累积
            m = beta1 * m + (1 - beta1) * grad
            u = np.maximum(beta2 * u, np.abs(grad))
            # 计算适应的学习率
            alpha = alpha_rate / (u + epsilon)
            # 更新参数
            nn_params -= alpha * m
            # 记录损失和准确度
            totalcost += cost
        # 计算并记录训练集和测试集准确度
        train_accuracy, test_accuracy = accuracy(nn_params, input_layer_size, hidden_layer_size, num_labels, X, y,
                                                 X_test, y_test)
        train_accuracy_history.append(train_accuracy)
        test_accuracy_history.append(test_accuracy)
        loss_history.append(totalcost / batch_size)
        print(f"Iteration {i}: Cost {totalcost / batch_size}")
        print('Training Set Accuracy: {:f}'.format(train_accuracy))
        print('Test Set Accuracy: {:f}'.format(test_accuracy))

    plot_loss_and_accuracy(loss_history, train_accuracy_history, test_accuracy_history)
    return nn_params
