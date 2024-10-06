import cv2
import numpy as np

# 读取输入图像
image = cv2.imread('smog.jpg')

# 将图像从BGR色彩空间转换为HSV色彩空间
hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

# 定义光照变化剧烈时的阈值范围（根据实际情况调整）
lower_shadow = np.array([0, 0, 0], dtype=np.uint8)
upper_shadow = np.array([180, 255, 50], dtype=np.uint8)

lower_highlight = np.array([0, 0, 200], dtype=np.uint8)
upper_highlight = np.array([180, 30, 255], dtype=np.uint8)

# 根据阈值进行图像分割
shadow_mask = cv2.inRange(hsv, lower_shadow, upper_shadow)
highlight_mask = cv2.inRange(hsv, lower_highlight, upper_highlight)

# 合并两个分割结果
result_mask = cv2.bitwise_or(shadow_mask, highlight_mask)

# 将原图和分割结果可视化
cv2.imshow('Origin', image)
cv2.imshow('Result', result_mask)

# 调整窗口大小
cv2.resizeWindow('Origin', image.shape[1] // 2, image.shape[0] // 2)
cv2.resizeWindow('Result', result_mask.shape[1] // 2, result_mask.shape[0] // 2)

cv2.imwrite('Q3processed.jpg', result_mask)
cv2.waitKey(0)
cv2.destroyAllWindows()

