from scipy.io import loadmat
from Method import initialise, predict
from Optim import *
from draw import drawpic, draw_accuracy_curve

if __name__ == '__main__':
    '''
    导入数据集，划分为60，000个训练样本，10，000个测试样本
    '''
    # 加载数据文件
    data = loadmat('mnist-original.mat')
    # 提取数据的特征矩阵，并进行转置
    X = data['data']
    X = X.transpose()
    # 然后将特征除以255，重新缩放到[0,1]的范围内，以避免在计算过程中溢出
    X = X / 255
    # 从数据中提取labels
    y = data['label']
    y = y.flatten()
    # 将数据分割为60,000个训练集
    train_size = 60000
    X_train = X[:train_size, :]
    y_train = y[:train_size]
    # 和10,000个测试集
    test_size = 10000
    X_test = X[train_size:train_size + test_size, :]
    y_test = y[train_size:train_size + test_size]
    '''
    构建三层全连接神经网络的参数
    '''
    # 输入层，隐藏层，输出层节点个数
    input_layer_size = 784  # 图片大小为 (28 X 28) px 所以设置784个特征
    hidden_layer_size = 16
    num_labels = 10  # 拥有十个标准为 [0, 9] 十个数字
    # 初始化层之间的权重 Thetas
    initial_Theta1 = initialise(hidden_layer_size, input_layer_size)  # 输入层和隐藏层之间的权重
    initial_Theta2 = initialise(num_labels, hidden_layer_size)  # 隐藏层和输出层之间的权重
    # 设置神经网络的参数
    initial_nn_params = np.concatenate((initial_Theta1.flatten(), initial_Theta2.flatten()))
    '''
    进行神经网络的训练
    '''
    # 设置学习率和迭代次数
    alpha = 0.01
    max_iter = 50
    lambda_reg = 0.1  # 避免过拟合
    # 训练神经网络，根据函数选择优化方法
    initial_nn_params = MiniBGD(initial_nn_params, input_layer_size, hidden_layer_size, num_labels, X_train, y_train,
                                lambda_reg, max_iter, alpha, X_test, y_test)

    # 重新分割，获得三个层次之间两两的权重
    Theta1 = np.reshape(initial_nn_params[:hidden_layer_size * (input_layer_size + 1)], (
        hidden_layer_size, input_layer_size + 1))  # shape = (100, 785)
    Theta2 = np.reshape(initial_nn_params[hidden_layer_size * (input_layer_size + 1):],
                        (num_labels, hidden_layer_size + 1))  # shape = (10, 101)
    # 测试集的准确度
    pred = predict(Theta1, Theta2, X_test)
    print('Test Set Accuracy: {:f}'.format((np.mean(pred == y_test) * 100)))
    # 训练集的准确度
    pred = predict(Theta1, Theta2, X_train)
    print('Training Set Accuracy: {:f}'.format((np.mean(pred == y_train) * 100)))

    # 将Theta参数保存在txt文件中，用作后续程序识别
    np.savetxt('Theta1.txt', Theta1, delimiter=' ')
    np.savetxt('Theta2.txt', Theta2, delimiter=' ')

    # 寻找最佳超参数
    # data = []
    # best_asem = []
    # for alpha in [0.5, 0.1, 0.01, 0.001]:
    #     for lambda_reg in [0.01, 0.1, 1.0]:
    #         for max_iter in [10, 50, 100, 200]:
    #             initial_nn_params = MiniBGD(initial_nn_params, input_layer_size, hidden_layer_size, num_labels, X_train,
    #                                         y_train,
    #                                         lambda_reg, max_iter, alpha, X_test, y_test)
    #             Theta1 = np.reshape(initial_nn_params[:hidden_layer_size * (input_layer_size + 1)], (
    #                 hidden_layer_size, input_layer_size + 1))  # shape = (100, 785)
    #             Theta2 = np.reshape(initial_nn_params[hidden_layer_size * (input_layer_size + 1):],
    #                                 (num_labels, hidden_layer_size + 1))  # shape = (10, 101)
    #             # 测试集的准确度
    #             pred = predict(Theta1, Theta2, X_test)
    #             print(f'alpha={alpha},lambda_reg={lambda_reg},max_iter={max_iter}')
    #             print('Accuracy: {:f}'.format((np.mean(pred == y_test) * 100)))
    #             data.append((alpha, lambda_reg, max_iter, np.mean(pred == y_test) * 100))
    # drawpic(data)
    # draw_accuracy_curve(data)
