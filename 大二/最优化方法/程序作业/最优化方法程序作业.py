#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
from sklearn.linear_model import Lasso


# 生成 Lasso 模型所需的数据
def lasso_data(n_samples=100, n_features=10, delta=1, mu=0.1, sigma=0.1):
    np.random.seed(10)
    x0 = np.zeros(n_features)  # 初始化系数向量 x0，长度为 n_features
    nz = np.random.choice(n_features, int(n_features / 2), replace=False)  # 随机挑选一些位置索引
    x0[nz] = np.random.randn(len(nz))  # 设置这些位置上的值为随机数
    A = np.random.randn(n_samples, n_features)  # 生成随机矩阵 A
    b = A.dot(x0) + sigma * np.random.randn(n_samples)  # 生成随机的响应变量 b
    return A, b, mu, delta, x0


# 定义光滑函数 l_smooth
def l_smooth(x, delta):
    if np.abs(x) < delta:  # 如果 abs(x) 小于 delta
        return (x ** 2) / (2 * delta)  # 则返回 (x**2) / (2 * delta)
    else:  # 如果 abs(x) 大于等于 delta
        return np.abs(x) - (delta / 2)  # 则返回 abs(x) - (delta / 2)


# 定义平滑绝对值函数 smooth_abs
def smooth_abs(x, delta):
    vec_abs = np.vectorize(lambda y: l_smooth(y, delta))  # 将 l_smooth 应用到 x 的每个元素上
    return np.sum(vec_abs(x))  # 返回 x 中所有元素经过 l_smooth 处理后的和


# 定义光滑 LASSO 模型函数 smooth_LASSO
def smooth_LASSO(A, b, mu, delta, x0, max_iter=1000, tol=1e-6, bb_init_step=None):
    m, n = A.shape  # 获取矩阵 A 的形状
    x = x0.copy()  # 初始化系数向量 x，长度为 n_features
    Ax = A.dot(x)  # 计算 A * x
    grad = A.T.dot(Ax - b) + mu * np.sign(x)  # 计算梯度的初始值

    if bb_init_step is None:
        bb_init_step = 1 / np.linalg.norm(grad)  # 计算 BB 算法的初始步长
    alpha = bb_init_step  # 初始化步长

    for k in range(max_iter):
        x_new = x - alpha * grad  # 计算 x_k+1
        Ax_new = A.dot(x_new)  # 计算 A * x_k+1
        grad_new = A.T.dot(Ax_new - b) + mu * np.vectorize(lambda y: l_smooth(y, delta))(x_new)  # 计算梯度

        # 计算 BB 步长
        y = grad_new - grad
        s = x_new - x
        alpha = np.dot(y, s) / np.linalg.norm(y) ** 2

        x = x_new  # 更新 x
        Ax = Ax_new  # 更新 A * x
        grad = grad_new  # 更新梯度
        if np.linalg.norm(grad) < tol:  # 如果梯度很小，就认为已经收敛了
            break

    return x


# 生成数据
n_samples, n_features = 100, 10
A, b, mu, delta, x_true = lasso_data(n_samples=n_samples, n_features=n_features)

# 计算 Lasso 模型的精确解
lasso_model = Lasso(alpha=mu / delta, fit_intercept=False)
lasso_model.fit(A, b)
x_opt = lasso_model.coef_

# 计算平滑 LASSO 模型的近似解
delta = 0.1
x_est = smooth_LASSO(A, b, mu, delta, x0=np.zeros(n_features), max_iter=10000)

print(f"True solution: {x_true}")
print(f"Lasso solution: {x_opt}")
print(f"Smooth Lasso solution: {x_est}")

import matplotlib.pyplot as plt

plt.plot(x_true, '*', color='blue', label='True Solution')
plt.plot(x_est, 'o', color='red', label='Smooth Lasso Solution')
plt.legend()
plt.show()

