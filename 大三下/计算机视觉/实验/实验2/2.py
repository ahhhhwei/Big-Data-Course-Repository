import cv2
import numpy as np

def apply_smooth(image):
    smooth_kernel = np.ones((5, 5), dtype=np.float32) / 25.0
    smooth_result = cv2.filter2D(image, -1, smooth_kernel)
    return smooth_result

def apply_sharpen(image):
    sharpen_kernel = np.array([[0, -1, 0],
                               [-1, 5, -1],
                               [0, -1, 0]], dtype=np.float32)
    sharpen_result = cv2.filter2D(image, -1, sharpen_kernel)
    return sharpen_result

image = cv2.imread('smog.jpg')
height, width, _ = image.shape
new_width = int(360 * (width / height))
original_image = image
smooth_result = apply_smooth(image)
sharpen_result = apply_sharpen(image)

cv2.imshow('Original', original_image)
cv2.imshow('Smoothed', smooth_result)
cv2.imshow('Sharpened', sharpen_result)

# 调整窗口大小
cv2.resizeWindow('Original', new_width, 360)
cv2.resizeWindow('Smoothed', new_width, 360)
cv2.resizeWindow('Sharpened', new_width, 360)

# 移动窗口
cv2.moveWindow('Original', 0, 0)
cv2.moveWindow('Smoothed', new_width + 10, 0)
cv2.moveWindow('Sharpened', 2 * (new_width + 10), 0)

cv2.waitKey(0)
cv2.destroyAllWindows()
