import cv2
import os

# 文件夹路径
video_folder = '../video/learn'
output_folder = './learn_output'

# 每0.5秒提取一帧，假设帧率为30fps，则每隔15帧提取一次
frame_interval = 15  # 假设帧率为30fps

# 创建输出文件夹如果它不存在
if not os.path.exists(output_folder):
    os.makedirs(output_folder)

# 遍历视频文件夹中的所有文件
for filename in os.listdir(video_folder):
    if filename.endswith('.mp4'):  # 根据实际情况修改视频文件后缀
        video_path = os.path.join(video_folder, filename)
        cap = cv2.VideoCapture(video_path)
        
        count = 0
        frame_number = 1
        while(cap.isOpened()):
            ret, frame = cap.read()
            if not ret:
                break
            
            count += 1
            if count % frame_interval == 0:
                # 保存帧到输出文件夹
                output_path = os.path.join(output_folder, f"{os.path.splitext(filename)[0]}_{frame_number:04d}.png")
                cv2.imwrite(output_path, frame)
                frame_number += 1
        
        cap.release()

print("所有帧已经按要求提取完成。")