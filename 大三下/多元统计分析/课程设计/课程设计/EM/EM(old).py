import numpy as np

# 创建一个有缺损值的矩阵
matrix = [
    [None, 0, 3],
    [7, 2, 6],
    [5, 1, 2],
    [None, None, 5]
]

# matrix = [
#     [3, 6, 0],
#     [4, 4, 3],
#     [None, 8, 3],
#     [5, None, None]
# ]

MU = []
COV = []
a = 0
while(a < 1):
    a += 1
    # print("预测:")
    # print("1.打印原始矩阵：")
    # # 打印矩阵
    # for row in matrix:
    #     modified_row = ['-' if x is None else x for x in row]
    #     print(*modified_row)

    # 将None替换为numpy中的nan，便于后续处理
    matrix_np = np.array(matrix, dtype=np.float64)
    matrix_np[matrix_np == None] = np.nan
    print(matrix_np)

    # 计算每列的均值
    if len(MU) == 0:
        col_means = np.nanmean(matrix_np, axis=0)
    else:
        col_means = [element for row in MU for element in row]
    
    print(col_means)
    # 填补空缺值为每列的均值
    for i in range(len(matrix)):
        for j in range(len(matrix[i])):
            if np.isnan(matrix_np[i, j]):
                matrix_np[i][j] = col_means[j]

    # print("2.打印填补缺失值后的矩阵：")
    # # 打印填补后的矩阵
    # for row in matrix_np:
    #     print(row)

    # 计算列与列之间的协方差矩阵
    if len(COV) == 0:
        cov_matrix = np.cov(matrix_np, rowvar=False, bias=True)
    else:
        cov_matrix = np.cov(COV, rowvar=False, bias=True)
    print("3.打印协方差矩阵:")
    print(cov_matrix)

    T_1 = np.array(matrix, dtype=np.float64).T
    T_1 = np.nansum(T_1, axis=1)
    T_2 = np.array([[0 if x is None else x for x in row] for row in matrix], dtype=np.float64)
    T_2 = T_2.T @ T_2

    # 遍历数据集
    for row in matrix:
        is_nan = False
        # 分块
        # 均值分块
        mu1 = []
        mu2 = []

        # 已知分量
        x_knowed = []

        # 记录缺失值位置
        x_pos = []
        # 记录已知值位置
        x_knowed_pos = []

        for index in range(len(row)):
            if row[index] is None:
                is_nan = True
                x_pos.append(index)
                mu1.append(col_means[index])
            else:
                x_knowed_pos.append(index)
                mu2.append(col_means[index])
                x_knowed.append(row[index])
        
        if is_nan:
            print("4.1.打印分块后均值向量：")
            print(mu1, mu2)

            # 协方差矩阵分块
            Sigma11 = []
            Sigma12 = []
            Sigma21 = []
            Sigma22 = []
            for index in range(len(row)):
                for jndex in range(len(row)):
                    if row[index] is None and row[jndex] is None:
                        Sigma11.append(cov_matrix[index][jndex])
                    elif row[index] is None and row[jndex] is not None:
                        Sigma12.append(cov_matrix[index][jndex])
                    elif row[index] is not None and row[jndex] is None:
                        Sigma21.append(cov_matrix[index][jndex])
                    elif row[index] is not None and row[jndex] is not None:
                        Sigma22.append(cov_matrix[index][jndex])
            
            Sigma11 = np.array(Sigma11).reshape((len(mu1), len(mu1)))
            Sigma12 = np.array(Sigma12).reshape((len(mu1), len(mu2)))
            Sigma21 = np.array(Sigma21).reshape((len(mu2), len(mu1)))
            Sigma22 = np.array(Sigma22).reshape((len(mu2), len(mu2)))
            mu1 = np.array(mu1)
            mu2 = np.array(mu2)
            x_knowed = np.array(x_knowed)

            print("4.2.打印分块后协方差矩阵：")
            print(Sigma11)
            print(Sigma12)
            print(Sigma21)
            print(Sigma22)

            # T_1部分
            x_modify = mu1 + Sigma12 @ np.linalg.inv(Sigma22) @ (x_knowed - mu2)
            print("5.1.T_1部分：")
            print(x_modify)

            for e in range(len(x_modify)):
                T_1[x_pos[e]] += x_modify[e]
            x_modify = x_modify.reshape((1, len(x_modify)))
            x_knowed = x_knowed.reshape((1, len(x_knowed)))

            # T_2部分
            product_correction1 = Sigma11 - Sigma12 @ np.linalg.inv(Sigma22) @ Sigma21 + x_modify.T @ x_modify
            product_correction2 = x_modify.T @ x_knowed
            for e in range(len(product_correction1)):
                for f in range(len(product_correction1[e])):
                    T_2[x_pos[e]][x_pos[f]] += product_correction1[e][f]

            for e in range(len(product_correction2)):
                for f in range(len(product_correction2[e])):
                    if x_pos[e] < x_knowed_pos[f]:
                        T_2[x_pos[e]][x_knowed_pos[f]] += product_correction2[e][f]  
                    else:
                        T_2[x_knowed_pos[f]][x_pos[e]] += product_correction2[e][f]  
            
            print("5.2.T_2部分:")
            print(product_correction1)
            print(product_correction2)

            print("T_2-------------------------------------------------------------------------------")
            print(T_2)

    # 计算矩阵的上三角掩码（不包括对角线）
    upper_triangle_mask = np.triu(np.ones_like(T_2, dtype=bool), k=1)

    # 获取右上部分的值
    upper_triangle_values = T_2[upper_triangle_mask]

    # 计算左下部分对应的索引
    lower_left_indices = np.tril_indices_from(T_2, k=-1)

    # 将右上部分的值对称复制到左下部分
    T_2[lower_left_indices] = upper_triangle_values

    T_1 = T_1.reshape((len(T_1), 1))
    print("T_1:")
    print(T_1)

    print("T_2:")
    print(T_2)

    print("估计:")
    mu = T_1 / len(matrix)
    MU = mu
    print("\mu:")
    print(mu)
    Sigma = T_2 / len(matrix) - mu @ mu.T
    COV = Sigma
    print("\Sigma:")
    print(Sigma)

    print("-------------------------------------------")

# a = np.array([0.25, 1])
# b = np.array([[0.5, 0.75], [0.75, 2.5]])
# print(0.5 - a @ np.linalg.inv(b) @ a.T + 5.72727273 ** 2)