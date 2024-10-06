import cv2
import numpy as np
import matplotlib.pyplot as plt

# 读取图像
image = cv2.imread('smog.jpg', 0)  # 读取为灰度图像

# 定义核（结构元素）
kernel = np.ones((5, 5), np.uint8)

# 腐蚀
erosion = cv2.erode(image, kernel, iterations=1)

# 膨胀
dilation = cv2.dilate(image, kernel, iterations=1)

# 开运算
opening = cv2.morphologyEx(image, cv2.MORPH_OPEN, kernel)

# 闭运算
closing = cv2.morphologyEx(image, cv2.MORPH_CLOSE, kernel)

# 使用subplot将四张图放在一起
plt.figure(figsize=(10, 8))

plt.subplot(2, 3, 1)
plt.imshow(image, cmap='gray')
plt.title('Original Image')

plt.subplot(2, 3, 2)
plt.imshow(erosion, cmap='gray')
plt.title('Erosion')

plt.subplot(2, 3, 3)
plt.imshow(dilation, cmap='gray')
plt.title('Dilation')

plt.subplot(2, 3, 4)
plt.imshow(opening, cmap='gray')
plt.title('Opening')

plt.subplot(2, 3, 5)
plt.imshow(closing, cmap='gray')
plt.title('Closing')

plt.show()
