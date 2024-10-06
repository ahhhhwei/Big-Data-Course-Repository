import cv2 as cv
import numpy as np

src = cv.imread("picture1.jpg")
img = src.copy()
img_gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

# 二值化图像（Canny边缘检测）
dst_img = cv.medianBlur(img_gray, 7)
dst_img = cv.Canny(dst_img, 50, 150)

# 霍夫线变换
lines = cv.HoughLines(dst_img, 1.2, np.pi / 180, 135)

# 存储直线的端点
line_endpoints = []

# 存储交点
intersection_points = []

# 将检测的线绘制在原图上
for line in lines:
    rho, theta = line[0]
    a = np.cos(theta)
    b = np.sin(theta)
    x0 = rho * a
    y0 = rho * b
    x1 = int(x0 + 1000 * (-b))
    y1 = int(y0 + 1000 * a)
    x2 = int(x0 - 1000 * (-b))
    y2 = int(y0 - 1000 * a)

    # 存储直线的端点
    line_endpoints.append(((x1, y1), (x2, y2)))

# 找直线交点
for i in range(len(line_endpoints)):
    for j in range(i + 1, len(line_endpoints)):
        line1 = line_endpoints[i]
        line2 = line_endpoints[j]

        x1, y1 = line1[0]
        x2, y2 = line1[1]

        x3, y3 = line2[0]
        x4, y4 = line2[1]

        # 计算直线交点
        det = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
        if det != 0:
            px = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / det
            py = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / det

            # 检查交点是否在图像内
            if 0 <= px < img.shape[1] and 0 <= py < img.shape[0]:
                intersection_points.append((px, py))

# 画交点之间的线段
for i in range(len(intersection_points)):
    for j in range(i + 1, len(intersection_points)):
        pt1 = intersection_points[i]
        pt2 = intersection_points[j]
        # 保证不画出对角线
        if (abs((int(pt1[0])) - int(pt2[0])) < 20 or abs((int(pt1[1])) - int(pt2[1])) < 20):
            # 画线段，使用红色
            cv.line(img, (int(pt1[0]), int(pt1[1])), (int(pt2[0]), int(pt2[1])), (0, 0, 255), 2)

# Hough圆检测
circles = cv.HoughCircles(dst_img, cv.HOUGH_GRADIENT, 1, 40,
                           param1=100, param2=90, minRadius=0, maxRadius=300)

if circles is not None:
    circles = np.uint16(np.around(circles))
    for i in circles[0, :]:
        # 画圆
        cv.circle(img, (i[0], i[1]), i[2], (0, 255, 0), 2)

        # 估算圆形直径
        diameter_pixels = i[2] * 2
        diameter_cm = (diameter_pixels / line_endpoints[0][1][1]) * 7  # 使用已知线段的长度进行比例计算
        print("估算的圆形直径（厘米）:", diameter_cm)
        cv.line(img, (i[0] - i[2], i[1]), (i[0] + i[2], i[1]), (255, 0, 0), 2)
        text = f"d = {diameter_cm:.2f} cm"
        cv.putText(img, text, (i[0] - int(i[2] / 2), i[1] - 10), cv.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 1,
                   cv.LINE_AA)

# 显示图像
cv.imshow("result", img)
cv.waitKey(0)
cv.imwrite("res.png",img)