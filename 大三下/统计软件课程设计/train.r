library(keras)
library(tidyverse)
library(magrittr)

# 读取所有图片路径
train_images <- list.files(file.path(getwd(), "train"), pattern = "\\.png$", full.names = TRUE)
test_images <- list.files(file.path(getwd(), "test"), pattern = "\\.png$", full.names = TRUE)

# 提取标签和路径
train_labels <- sapply(strsplit(train_images, "([_\\.])"), function(x) x[1])
test_labels <- sapply(strsplit(test_images, "([_\\.])"), function(x) x[1])

train_data <- data.frame(image_path = train_images, label = train_labels)
test_data <- data.frame(image_path = test_images, label = test_labels)

# 将标签转换为因子以便分类
train_data$label <- as.factor(train_data$label)
test_data$label <- as.factor(test_data$label)

# 创建数据生成器
# 创建一个ImageDataGenerator对象
train_datagen <- image_data_generator(rescale = 1/255)

# 使用flow_from_directory方法从目录加载数据
train_generator <- train_datagen %>% flow_images_from_directory(
  directory = file.path(getwd(), "train"),
  target_size = c(150, 150),
  batch_size = 32,
  class_mode = "categorical"
)

test_datagen <- image_data_generator(rescale = 1/255)

test_generator <- test_datagen %>% flow_images_from_directory(
  directory = file.path(getwd(), "test"),
  target_size = c(150, 150),
  batch_size = 32,
  class_mode = "categorical"
)

# 定义模型
model <- keras_model_sequential() %>%
  layer_conv_2d(filters = 32, kernel_size = c(3, 3), activation = "relu", input_shape = c(150, 150, 3)) %>%
  layer_max_pooling_2d(pool_size = c(2, 2)) %>%
  layer_conv_2d(filters = 64, kernel_size = c(3, 3), activation = "relu") %>%
  layer_max_pooling_2d(pool_size = c(2, 2)) %>%
  layer_flatten() %>%
  layer_dense(units = 128, activation = "relu") %>%
  layer_dropout(rate = 0.5) %>%
  layer_dense(units = 2, activation = "softmax")

# 编译模型
model %>% compile(
  loss = "categorical_crossentropy",
  optimizer = optimizer_rmsprop(lr = 2e-5),
  metrics = c("accuracy")
)
summary(model)

# 使用 fit 方法来训练模型
history <- model %>% fit(
  x = train_generator,
  steps_per_epoch = ceiling(train_generator$n / 32),
  epochs = 1,
  validation_data = test_generator,
  validation_steps = ceiling(test_generator$n / 32)
)

# 模型评估
scores <- model %>% evaluate(
  x = test_generator,
  steps = ceiling(test_generator$n / 32)
)
print(paste0("Test loss: ", scores))
print(paste0("Test accuracy: ", scores))

save_model_hdf5(model, "learn_food_model1.h5")
