import gradio as gr
from tkinter import *
import numpy as np
from PIL import ImageGrab
from Method import predict
Theta1 = np.loadtxt('Theta1.txt')
Theta2 = np.loadtxt('Theta2.txt')

def predict_num(vec):
    tmp = np.zeros((785, 784))
    tmp[0:len(vec["composite"]), 0:len(vec["composite"][0])] = vec["composite"]
    print(len(tmp))
    pred = predict(Theta1, Theta2, tmp / 255)
    print(pred[0])
    print(vec["composite"])
    return vec["composite"]

demo = gr.Interface(
    fn=predict_num,
    inputs=gr.ImageEditor(type="numpy", crop_size="1:1", image_mode="L"),
    outputs=["image"],
)
demo.launch()
