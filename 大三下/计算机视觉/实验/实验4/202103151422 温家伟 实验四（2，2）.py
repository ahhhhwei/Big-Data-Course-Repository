import cv2
import numpy as np
import os

video = cv2.VideoCapture("./光伏热成像原始视频.mov")
if not os.path.exists("Photovoltaic thermal imaging"):
    image_path = os.makedirs("Photovoltaic thermal imaging")

# 截图的图片命名
imgPath = "frame"

# 视频帧总数
sum = video.get(7)

time = (int)(sum / 100)
# 重置视频总帧数
sum = 0
# 需要截取的图片数量
i = 0

while True:
    ret, frame = video.read()
    # 读取视频帧
    if ret == False:
        # 判断是否读取成功
        break
    sum += 1
    if sum % time == 0 and i < 100:
        i += 1
        # 使用i为图片命名
        imgPath = "Photovoltaic thermal imaging/{}.jpg".format(i)
        # 将提取的视频帧存储进imgPath
        cv2.imwrite(imgPath, frame)

print("分帧成功")  # 提取结束，打印分帧成功

img = cv2.imread("Photovoltaic thermal imaging/85.jpg")
# 转化为灰度图
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# 高斯模糊降噪
blurred = cv2.GaussianBlur(gray, (5, 5), 0)

# 二值化隔离出高亮区域
thresh = cv2.threshold(blurred, 220, 255, cv2.THRESH_BINARY)[1]

# 膨胀腐蚀处理噪点
thresh = cv2.erode(thresh, (3, 3), iterations=3)
thresh = cv2.dilate(thresh, (3, 3), iterations=3)
# cv2.imwrite('thresh.jpg', thresh)


for i in range(720):
    for j in range(480):
        if thresh[j][i] != 0:
            img[j][i] = 0
            y1 = j
            x1 = i

# 应用阈值处理
_, thresh = cv2.threshold(thresh, 240, 255, cv2.THRESH_BINARY)

# 查找轮廓
contours, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

# 遍历每个轮廓
for contour in contours:
    # 忽略面积较小的轮廓
    area = cv2.contourArea(contour)
    if area < 5:
        continue

    # 计算轮廓的边界框
    x, y, w, h = cv2.boundingRect(contour)

    # 绘制边界框
    cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)

    label_x = int((x-15)*1.0/55)+1
    if y > 71 and y <= 146:label_y = 1
    if y > 146 and y <= 215: label_y = 2
    if y > 215 and y <= 300: label_y = 3
    if y > 300 and y <= 373: label_y = 4
    cv2.putText(img, "({},{})".format(label_x,label_y), (x, y - 15),cv2.FONT_HERSHEY_COMPLEX, 0.8, (0, 0, 255), 1)

cv2.imshow("image", img)
cv2.imwrite("out.png",img)
cv2.waitKey(0)
