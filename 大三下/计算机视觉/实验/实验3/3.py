import cv2
import numpy as np

# 读取目标对象图像和待匹配图像
target_image = cv2.imread('a.jpg', cv2.IMREAD_COLOR)
query_image = cv2.imread('c.png', cv2.IMREAD_COLOR)

# 调整图像大小
scale_percent = 50  # 缩小为原始大小的50%
width = int(target_image.shape[1] * scale_percent / 100)
height = int(target_image.shape[0] * scale_percent / 100)
target_image_resized = cv2.resize(target_image, (width, height))
query_image_resized = cv2.resize(query_image, (width, height))

# 创建SIFT对象
sift = cv2.SIFT_create()

# 使用SIFT算法检测关键点和描述子
keypoints_target, descriptors_target = sift.detectAndCompute(target_image_resized, None)
keypoints_query, descriptors_query = sift.detectAndCompute(query_image_resized, None)

# 使用FLANN匹配器
flann = cv2.FlannBasedMatcher({'algorithm': 0, 'trees': 5}, {'checks': 50})

# 使用KNN算法进行匹配
matches = flann.knnMatch(descriptors_target, descriptors_query, k=2)

# 提取最佳匹配
good_matches = []
for m, n in matches:
    if m.distance < 0.44* n.distance:
        good_matches.append(m)

# 绘制匹配结果
result_image = cv2.drawMatches(target_image_resized, keypoints_target, query_image_resized, keypoints_query, good_matches, None, flags=cv2.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)

# 显示结果
cv2.imshow('Object Detection', result_image)
cv2.waitKey(0)
cv2.destroyAllWindows()
