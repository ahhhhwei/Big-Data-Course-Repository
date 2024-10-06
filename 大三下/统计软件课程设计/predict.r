# # 加载必要的库
# library(keras)
# library(tidyverse)
# library(magrittr)

# # 加载模型
# model <- load_model_hdf5("learn_food_model.h5")

# # 图片路径
# image_path <- file.path(getwd(), "train\\food\\food10_0409.png")  # 假设图片在当前工作目录下

# # 加载图片，并调整大小为模型所需的输入尺寸 (150, 150)
# img <- image_load(image_path, target_size = c(150, 150))

# # 预处理图片 - 归一化
# img_array <- image_to_array(img) / 255  # 归一化到 [0, 1]

# # 扩展维度以匹配模型的输入形状 (batch_size, height, width, channels)
# img_batch <- array_reshape(img_array, c(1, dim(img_array)))

# # 使用模型进行预测
# prediction <- predict(model, img_batch)

# # 获取类别标签
# labels <- c("learn", "food")  # 这里应该替换为实际的类别标签
# predicted_class <- labels[max.col(prediction, ties.method = "first")]

# print(paste0("Predicted class is: ", predicted_class))



# 1.清空视频帧文件夹

# 指定文件夹路径
folder_path <- "output"

# 删除文件夹中的所有文件
unlink(file.path(folder_path, "*"), recursive = TRUE)

# 2.视频分帧

# 设置视频文件路径和输出目录
video_path <- "video/predict/predict2.mp4"
output_dir <- "output"

# 创建输出目录（如果不存在的话）
if (!dir.exists(output_dir)) {
  dir.create(output_dir)
}

# 设置命令以每秒提取1帧
command <- sprintf(
  'ffmpeg -i "%s" -vf fps=1 "%s/frame_%%04d.png"',
  video_path, output_dir
)

# 执行命令
system(command)

# 3.预测视频标签

library(keras)
library(tidyverse)
library(magrittr)

# 加载模型
model <- load_model_hdf5("learn_food_model.h5")

# 提取帧
frames_path <- "output"  # 替换为你的帧目录
frames_list <- list.files(frames_path, full.names = TRUE)

food <- 0
learn <- 0

# 处理每一帧
for (frame in frames_list) {
  # 加载图片，并调整大小
  img <- image_load(frame, target_size = c(150, 150))
  
  # 预处理图片
  img_array <- image_to_array(img) / 255
  img_batch <- array_reshape(img_array, c(1, dim(img_array)))
  
  # 预测
  prediction <- predict(model, img_batch)
  
  # 获取类别标签
  labels <- c("food", "learn")
  predicted_class <- labels[max.col(prediction, ties.method = "first")]
  
  print(predicted_class)
  print(prediction)
  if (predicted_class == "food") {
    food = food + 1
  } else {
    learn = learn + 1
  }
}

print(food)
print(learn)
if (food > learn){
  print("Final video class is: food")
} else {
  print("Final video class is: learn")
}
