# 加载必要的库
library(tidyverse)
library(imager)
library(caret)

# 获取所有图片路径
image_paths <- list.files("video_output/learn_output", full.names = TRUE)

# 获取标签信息
labels <- sapply(strsplit(image_paths, "/"), function(x) x[length(x)-1])

# 创建数据框用于存储路径和标签
df <- data.frame(path = image_paths, label = labels, stringsAsFactors = FALSE)

# 对标签进行因子编码
df$label <- as.factor(df$label)

# 划分训练集和测试集
set.seed(123) # 设置种子确保结果可复现
train_index <- createDataPartition(df$label, p = 0.8, list = FALSE)
train_set <- df[train_index, ]
test_set <- df[-train_index, ]

# 显示划分后的数据集大小
print(paste0("训练集大小: ", nrow(train_set)))
print(paste0("测试集大小: ", nrow(test_set)))

# 假定你的训练集和测试集文件夹已经创建好
train_dir <- "train/learn"
test_dir <- "test/learn"

# 创建函数以移动文件
move_files <- function(set, dest_dir) {
  for (i in 1:nrow(set)) {
    # 文件移动
    file.rename(set$path[i], file.path(dest_dir, basename(set$path[i])))
  }
}

# 移动训练集和测试集文件
move_files(train_set, train_dir)
move_files(test_set, test_dir)