import cv2
import numpy as np
import ctypes

# 自定义3x3卷积核
custom_kernel = np.array([[-10, -10, -10],
                          [-10, 81, -10],
                          [-10, -10, -10]])
# 增大模板权重系数，使得图像的边缘过分清晰

# 加载图像
img_path = "smog.jpg"
img = cv2.imread(img_path)

if img is None:
    print("Error: Unable to load image.")
    exit()

# 图像处理函数
def apply_custom_convolution(img, kernel):
    # 卷积操作
    conv_img = cv2.filter2D(img, -1, kernel)
    return conv_img

# 应用自定义卷积核进行图像处理
result_img = apply_custom_convolution(img, custom_kernel)

# 获取屏幕大小
user32 = ctypes.windll.user32
screen_width, screen_height = user32.GetSystemMetrics(0), user32.GetSystemMetrics(1)

# 创建一个窗口并显示原图和处理后的图像
window_name = "Image Comparison"
cv2.namedWindow(window_name, cv2.WINDOW_NORMAL)
cv2.resizeWindow(window_name, screen_width // 2, screen_height // 2)

# 将原图和处理后的图像水平拼接
comparison_img = np.hstack((img, result_img))

# 显示图像
cv2.imshow(window_name, comparison_img)
cv2.waitKey(0)
cv2.destroyAllWindows()

# 保存卷积核的模板阵列到TXT文档
kernel_txt_path = "custom_kernel.txt"
np.savetxt(kernel_txt_path, custom_kernel, fmt='%d')

print("图像处理完成，并保存为 result_image.jpg")
print("卷积核的模板阵列已保存到 custom_kernel.txt")
