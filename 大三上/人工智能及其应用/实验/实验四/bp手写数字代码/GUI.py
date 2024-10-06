from tkinter import *
from PIL import ImageTk, Image
import numpy as np
from PIL import ImageGrab
from Method import predict

window = Tk()
window.title("Handwritten digit recognition")

# 加载背景图片
bg_image = Image.open("background.png")
bg_photo = ImageTk.PhotoImage(bg_image)

# 创建标签并设置背景图像
bg_label = Label(window, image=bg_photo)
bg_label.place(x=0, y=0, relwidth=1, relheight=1)

l1 = Label()

def MyProject():
    global l1

    widget = cv
    # 设置画布的坐标（加入参数index=55就对齐了，不知道为什么）
    index = 55
    x = window.winfo_rootx() + widget.winfo_x() + index
    y = window.winfo_rooty() + widget.winfo_y() + index
    x1 = x + widget.winfo_width() + index
    y1 = y + widget.winfo_height() + index
    # print(x, y, x1, y1)
    # 从画布上提取图像并修改像素大小为 (28 X 28)
    img = ImageGrab.grab().crop((x, y, x1, y1)).resize((28, 28))
    # 灰度处理（感觉没必要，本身就是黑白）
    img = img.convert('L')
    # 提取图像的像素矩阵，并转换为(1, 784)的矩阵
    x = np.asarray(img)
    vec = np.zeros((1, 784))
    k = 0
    for i in range(28):
        for j in range(28):
            vec[0][k] = x[i][j]
            k += 1
    # print(vec)

    print(vec)
    # 加载之前存储的两层神将网络权重
    Theta1 = np.loadtxt('Theta1.txt')
    Theta2 = np.loadtxt('Theta2.txt')

    # 调用识别功能
    pred = predict(Theta1, Theta2, vec / 255)
    # 展示结果
    l1 = Label(window, text="识别数字 = " + str(pred[0]), font=('黑体', 20))
    l1.place(x=200, y=450)


lastx, lasty = None, None


# 清除界面功能实现
def clear_widget():
    global cv, l1
    cv.delete("all")
    l1.destroy()


# 开始识别
def event_activation(event):
    global lastx, lasty
    cv.bind('<B1-Motion>', draw_lines)
    lastx, lasty = event.x, event.y


# 展示界面
def draw_lines(event):
    global lastx, lasty
    x, y = event.x, event.y
    cv.create_line((lastx, lasty, x, y), width=30, fill='white', capstyle=ROUND, smooth=TRUE, splinesteps=12)
    lastx, lasty = x, y


# 标题展示
L1 = Label(window, text="温家伟的BP网络", font=('华文新魏', 30), fg="blue")
L1.place(x=140, y=10)

# 清楚界面按钮
b1 = Button(window, text="1. 清除", font=('方正姚体', 20), bg="orange", fg="black", command=clear_widget)
b1.place(x=120, y=370)

# 识别数字按钮
b2 = Button(window, text="2. 识别", font=('方正姚体', 20), bg="white", fg="red", command=MyProject)
b2.place(x=320, y=370)

# 设置手写界面参数
cv = Canvas(window, width=350, height=290, bg='black')
cv.place(x=120, y=70)

cv.bind('<Button-1>', event_activation)
window.geometry("600x500")
window.mainloop()
