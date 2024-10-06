import streamlit as st
from streamlit_webrtc import webrtc_streamer
import av
import cv2
import os
import dlib
import changeface as CF
import base64
import face2animal as FA
import numpy as np
from camera_input_live import camera_input_live
from PIL import Image
import tempfile

# 手势识别翻页
import time
import hand as htm  
import math 
from ctypes import cast, POINTER  
from comtypes import CLSCTX_ALL  
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume

# 多线程
import threading


session_state = st.session_state
session_state['page'] = '明星换脸'
page = st.sidebar.radio('导航栏', ['明星换脸', '动物变脸'])



class StarChFace:
    def __init__(self) -> None:
        here = os.path.dirname(os.path.abspath(__file__))
        models_folder_path = os.path.join(here, 'models')
        faces_folder_path = os.path.join(here, 'faces')
        predictor_path = os.path.join(models_folder_path, 'face_landmarks.dat')
        self.hand_detector = htm.handDetector(detectionCon=1)  # 创建一个手部检测器对象，设定检测置信度为1
        self.trend_queue = htm.TrendQueue(max_size=15) # 初始化坐标队列
        self.detector = dlib.get_frontal_face_detector()
        self.prevX = 0  # 初始化上一次手指的x坐标
        self.predictor = dlib.shape_predictor(predictor_path)
        self.faces_images = CF.ChangeFace.load_face_images(faces_folder_path)
        self.current_face_index = 0
        self.before = True

        # self.im1 = cv2.imread(self.faces_images[self.current_face_index])
        # self.im1 = cv2.resize(self.im1, (600, self.im1.shape[0] * 600 // self.im1.shape[1]))
        # self.landmarks1 = CF.ChangeFace.get_face_landmarks(self.im1, self.detector, self.predictor)
        # self.im1_size = CF.ChangeFace.get_image_size(self.im1)
        # self.im1_mask = CF.ChangeFace.get_face_mask(self.im1_size, self.landmarks1)


    # def process_image(self, frame):
    #     img = frame.to_ndarray(format="bgr24")
    #     landmarks2 = CF.ChangeFace.get_face_landmarks(img, self.detector, self.predictor)
    #     img1 = self.hand_detector.findHands(img)  # 在图像上寻找并标记手部
    #     lmList = self.hand_detector.findPosition(img1, draw=False)  # 获取手部关键点的位置，不绘制标记

    #     im1 = cv2.imread(self.faces_images[self.current_face_index])
    #     im1 = cv2.resize(im1, (600, im1.shape[0] * 600 // im1.shape[1]))
    #     landmarks1 = CF.ChangeFace.get_face_landmarks(im1, self.detector, self.predictor)
    #     im1_size = CF.ChangeFace.get_image_size(im1)
    #     im1_mask = CF.ChangeFace.get_face_mask(im1_size, landmarks1)
    #     if landmarks2 is not None:
    #         im2_size = CF.ChangeFace.get_image_size(img)
    #         im2_mask = CF.ChangeFace.get_face_mask(im2_size, landmarks2)
    #         affine_im1 = CF.ChangeFace.get_affine_image(im1, img, landmarks1, landmarks2)
    #         affine_im1_mask = CF.ChangeFace.get_affine_image(im1_mask, img, landmarks1, landmarks2)
    #         union_mask = CF.ChangeFace.get_mask_union(im2_mask, affine_im1_mask)
    #         seamless_im = CF.ChangeFace.skin_color_adjustment(affine_im1, img, mask=union_mask)
    #         point = CF.ChangeFace.get_mask_center_point(affine_im1_mask)
    #         seamless_im = cv2.seamlessClone(affine_im1, img, mask=union_mask, p=point, flags=cv2.NORMAL_CLONE)
    #         img = seamless_im

    # def process_hand(self, frame):
    #     img = frame.to_ndarray(format="bgr24")
    #     landmarks2 = CF.ChangeFace.get_face_landmarks(img, self.detector, self.predictor)
    #     img1 = self.hand_detector.findHands(img)  # 在图像上寻找并标记手部
    #     lmList = self.hand_detector.findPosition(img1, draw=False)  # 获取手部关键点的位置，不绘制标记

    #     im1 = cv2.imread(self.faces_images[self.current_face_index])
    #     im1 = cv2.resize(im1, (600, im1.shape[0] * 600 // im1.shape[1]))
    #     landmarks1 = CF.ChangeFace.get_face_landmarks(im1, self.detector, self.predictor)
    #     im1_size = CF.ChangeFace.get_image_size(im1)
    #     im1_mask = CF.ChangeFace.get_face_mask(im1_size, landmarks1)
    #     if len(lmList[0]) != 0:
    #         y2 = lmList[0][8][2]  # 获取第二个手指关节的坐标
    #         self.trend_queue.push(y2)
    #         now = self.trend_queue.detect_rising_trend()
    #         if now and not self.before:
    #             self.current_face_index = (self.current_face_index + 1) % len(self.faces_images)
    #             print("翻页")
    #         else:
    #             print("不翻页")
    #         self.before = now
    
    def recv(self, frame):
        img = frame.to_ndarray(format="bgr24")
        landmarks2 = CF.ChangeFace.get_face_landmarks(img, self.detector, self.predictor)
        img1 = self.hand_detector.findHands(img)  # 在图像上寻找并标记手部
        lmList = self.hand_detector.findPosition(img1, draw=False)  # 获取手部关键点的位置，不绘制标记

        im1 = cv2.imread(self.faces_images[self.current_face_index])
        im1 = cv2.resize(im1, (600, im1.shape[0] * 600 // im1.shape[1]))
        landmarks1 = CF.ChangeFace.get_face_landmarks(im1, self.detector, self.predictor)
        im1_size = CF.ChangeFace.get_image_size(im1)
        im1_mask = CF.ChangeFace.get_face_mask(im1_size, landmarks1)

        if landmarks2 is not None:
            im2_size = CF.ChangeFace.get_image_size(img)
            im2_mask = CF.ChangeFace.get_face_mask(im2_size, landmarks2)
            affine_im1 = CF.ChangeFace.get_affine_image(im1, img, landmarks1, landmarks2)
            affine_im1_mask = CF.ChangeFace.get_affine_image(im1_mask, img, landmarks1, landmarks2)
            union_mask = CF.ChangeFace.get_mask_union(im2_mask, affine_im1_mask)
            seamless_im = CF.ChangeFace.skin_color_adjustment(affine_im1, img, mask=union_mask)
            point = CF.ChangeFace.get_mask_center_point(affine_im1_mask)
            seamless_im = cv2.seamlessClone(affine_im1, img, mask=union_mask, p=point, flags=cv2.NORMAL_CLONE)
            img = seamless_im
        if len(lmList[0]) != 0:  # 如果检测到手部关键点
            x2, y2 = lmList[0][8][1], lmList[0][8][2]  # 获取第二个手指关节的坐标
            cv2.circle(img, (x2, y2), 15, (255, 0, 255), cv2.FILLED)  # 绘制第二个手指关节的圆圈

            self.trend_queue.push(y2)
            now = self.trend_queue.detect_rising_trend()

            # listener = keyboard.Listener(on_press=on_press)
            # listener.start()
            # listener.join()

            if now and not self.before:
            # if FLAG:
                self.current_face_index = (self.current_face_index + 1) % len(self.faces_images)
                cv2.putText(img, f'page up', (40, 50), cv2.FONT_HERSHEY_COMPLEX, 1, (255, 0, 0), 3)  # 在图像上显示帧率
                FLAG = False
            
            self.before = now
        # # 创建并启动两个线程来处理图像处理和手部关键点处理
        # image_thread = threading.Thread(target=StarChFace.process_image(self, frame))
        # hand_thread = threading.Thread(target=StarChFace.process_hand(self, frame))
        # image_thread.start()
        # hand_thread.start()

        # # 等待两个线程执行完毕
        # image_thread.join()
        # hand_thread.join()
        return av.VideoFrame.from_ndarray(img, format="bgr24")

class AnimalFace:
    def capture_image():
        camera_image = st.camera_input("")
        if camera_image:
            image = Image.open(camera_image)
            # 这里可以添加代码将image转换为OpenCV格式进行处理，以及执行动物脸部替换的逻辑
            # 示例：将PIL图像转换为OpenCV格式
            image_cv = np.array(image)[:, :, ::-1].copy()
            # 在此处添加你的面部变换代码，如FA.get_two_triangles等
            # ...
            # 处理后，如果需要，可以将图像转回PIL格式展示
            return image_cv
        return None

def main_bg(main_bg):
    main_bg_ext = "png"
    st.markdown(
        f"""
         <style>
         .stApp {{
             background: url(data:image/{main_bg_ext};base64,{base64.b64encode(open(main_bg, "rb").read()).decode()});
             background-size: cover
         }}
         </style>
         """,
        unsafe_allow_html=True
    )

if page == '明星换脸':
    st.title('明星换脸')
    main_bg('./pics/bac.png')
    ctx = webrtc_streamer(
        key="example",
        video_processor_factory=StarChFace,
        rtc_configuration={
            "iceServers": [{"urls": ["stun:stun.l.google.com:19302"]}]
        }
    )

elif page == '动物变脸':
    st.title('动物变脸')
    st.markdown(
        """
        <style>
        body {
            background-image: url('https://www.baidu.com/img/bdlogo.png');
            background-size: cover;
        }
        </style>
        """,
        unsafe_allow_html=True
    )
    main_bg('./pics/background.png')
    animal = st.radio('', ('猫🐈', '熊猫🐼', '猩猩🦧'))
    uploaded_file = st.file_uploader("选择一张图片", type="png")

    if animal:
        if uploaded_file is not None:
            file_bytes = np.asarray(bytearray(uploaded_file.read()), dtype=np.uint8)
            img = cv2.imdecode(file_bytes, cv2.IMREAD_COLOR)
            img = img[0:400, 0:400]
            if animal == "猫🐈":
                image, image2, img1_triangles, img2_triangles = FA.get_two_triangles(img, "images\\cat.jpg", "temp.png", "cat.png", np.load("images\\cat_landmarks.npy"))
                FA.write_videos(img1_triangles,img2_triangles,image,image2,"outputs\\temp.mp4")
                video_file = open('outputs\\temp.mp4', 'rb')
                video_bytes = video_file.read()
                st.video(video_bytes)

            elif animal == "熊猫🐼":
                image, image2, img1_triangles, img2_triangles = FA.get_two_triangles(img, "images\\panda.jpg", "temp.png", "panda.png", np.load("images\\panda_landmarks.npy"))
                FA.write_videos(img1_triangles,img2_triangles,image,image2,"outputs\\temp.mp4")
                video_file = open('outputs\\temp.mp4', 'rb')
                video_bytes = video_file.read()
                st.video(video_bytes)

            elif animal == "猩猩🦧":
                image, image2, img1_triangles, img2_triangles = FA.get_two_triangles(img, "images\\gorilla.jpg", "temp.png", "gorilla.png", np.load("images\\gorilla_landmarks.npy"))
                FA.write_videos(img1_triangles,img2_triangles,image,image2,"outputs\\temp.mp4")
                video_file = open('outputs\\temp.mp4', 'rb')
                video_bytes = video_file.read()

                st.video(video_bytes)
