import numpy as np
from Method import predict


def accuracy(initial_nn_params, input_layer_size, hidden_layer_size, num_labels, X_train, y_train, X_test, y_test):
    # 重新分割，获得三个层次之间两两的权重
    Theta1 = np.reshape(initial_nn_params[:hidden_layer_size * (input_layer_size + 1)], (
        hidden_layer_size, input_layer_size + 1))  # shape = (100, 785)
    Theta2 = np.reshape(initial_nn_params[hidden_layer_size * (input_layer_size + 1):],
                        (num_labels, hidden_layer_size + 1))  # shape = (10, 101)
    # 训练集的准确度
    train_pred = predict(Theta1, Theta2, X_train)
    train_accuracy = np.mean(train_pred == y_train) * 100

    # 测试集的准确度
    test_pred = predict(Theta1, Theta2, X_test)
    test_accuracy = np.mean(test_pred == y_test) * 100

    return train_accuracy, test_accuracy

