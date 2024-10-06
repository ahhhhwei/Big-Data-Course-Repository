import cv2
import matplotlib.pyplot as plt

# 读取图像
img = cv2.imread("smog.jpg")

# 转为灰度图像
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# 直方图均衡化
equ_histogram = cv2.equalizeHist(gray)

# 创建一个 2x3 的画布，用于展示多个图像和直方图
plt.figure(figsize=(12, 6))

# 设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei']  # 使用黑体显示中文
plt.rcParams['axes.unicode_minus'] = False  # 解决负号显示为方块的问题

# 显示原始图像
plt.subplot(2, 3, 1)
plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
plt.title('原始图像')

# 显示灰度图像
plt.subplot(2, 3, 2)
plt.imshow(gray, cmap='gray')
plt.title('灰度图像')

# 显示直方图均衡化后的图像
plt.subplot(2, 3, 3)
plt.imshow(equ_histogram, cmap='gray')
plt.title('直方图均衡化后图像')

# 保存直方图均衡化后的图像
cv2.imwrite("result.jpg", equ_histogram)

# 绘制原始灰度图像的直方图
plt.subplot(2, 3, 5)
plt.hist(gray.flatten(), bins=256, range=[0, 256], color='r', histtype='bar')
plt.title('灰度直方图')

# 绘制直方图均衡化后图像的直方图
plt.subplot(2, 3, 6)
plt.hist(equ_histogram.flatten(), bins=256, range=[0, 256], color='r', histtype='bar')
plt.title('直方图均衡化后直方图')

# 显示图像和直方图
plt.show()
