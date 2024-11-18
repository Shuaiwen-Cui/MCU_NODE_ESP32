# 项目框架

## 介绍

!!! note "项目框架"
    在完成项目初始化之后，我们还需要对生成的项目进行重新组织和整理，以使得其更好地支撑我们的项目开发。本节将介绍如何对项目进行重新组织和整理。

## 项目框架

在本项目中，项目代码组织结构如下：

```shell
project-name/
├── CMakeLists.txt          # 项目顶层构建文件
├── partitions-16MiB.csv    # 分区表
├── sdkconfig               # 当前配置文件
├── sdkconfig.old           # 旧配置文件
├── main/                   # 主应用程序代码
│   ├── CMakeLists.txt      # Main目录的构建文件
│   ├── main.c              # 主入口文件
│   └── app/                # 应用逻辑代码
│       ├── app.c           # 应用层逻辑
│       ├── app.h           # 应用接口定义
│       └── ...
├── components/             # 外设模块目录
│   ├── CMakeLists.txt      # 组件目录构建文件
│   ├── led/                # LED 模块
│   │   ├── led.c
│   │   ├── led.h
│   │   └── ...
│   ├── rgb/                # RGB 模块
│   │   ├── rgb.c
│   │   ├── rgb.h
│   │   └── ...
│   ├── sensor/             # 传感器模块
│   │   ├── sensor.c
│   │   ├── sensor.h
│   │   └── ...
│   └── ...                 # 其他外设模块
├── tinyshm/                # TinySHM 框架代码
│   ├── CMakeLists.txt      # TinySHM 的构建文件
│   ├── data_processing/    # 数据处理模块
│   │   ├── data_proc.c
│   │   ├── data_proc.h
│   │   └── ...
│   ├── fault_detection/    # 故障检测模块
│   │   ├── fault_detect.c
│   │   ├── fault_detect.h
│   │   └── ...
│   ├── sensor_integration/ # 传感器集成模块
│   │   ├── sensor_integ.c
│   │   ├── sensor_integ.h
│   │   └── ...
│   └── ...                 # 其他模块
├── build/                  # 构建目录（自动生成）
│   └── ...                 # 编译过程中生成的文件
└── README.md               # 项目简介文档
project-name/
├── CMakeLists.txt          # 项目顶层构建文件
├── partitions-16MiB.csv    # 分区表
├── sdkconfig               # 当前配置文件
├── sdkconfig.old           # 旧配置文件
├── main/                   # 主应用程序代码
│   ├── CMakeLists.txt      # Main目录的构建文件
│   ├── main.c              # 主入口文件
│   └── app/                # 应用逻辑代码
│       ├── app.c           # 应用层逻辑
│       ├── app.h           # 应用接口定义
│       └── ...
├── components/             # 外设模块目录
│   ├── CMakeLists.txt      # 组件目录构建文件
│   ├── led/                # LED 模块
│   │   ├── led.c
│   │   ├── led.h
│   │   └── ...
│   ├── rgb/                # RGB 模块
│   │   ├── rgb.c
│   │   ├── rgb.h
│   │   └── ...
│   ├── sensor/             # 传感器模块
│   │   ├── sensor.c
│   │   ├── sensor.h
│   │   └── ...
│   └── ...                 # 其他外设模块
├── tinyshm/                # TinySHM 框架代码
│   ├── CMakeLists.txt      # TinySHM 的构建文件
│   ├── data_processing/    # 数据处理模块
│   │   ├── data_proc.c
│   │   ├── data_proc.h
│   │   └── ...
│   ├── fault_detection/    # 故障检测模块
│   │   ├── fault_detect.c
│   │   ├── fault_detect.h
│   │   └── ...
│   ├── sensor_integration/ # 传感器集成模块
│   │   ├── sensor_integ.c
│   │   ├── sensor_integ.h
│   │   └── ...
│   └── ...                 # 其他模块
├── build/                  # 构建目录（自动生成）
│   └── ...                 # 编译过程中生成的文件
└── README.md               # 项目简介文档

```

!!! note
    - main 文件夹下是主程序代码，包括在子文件夹app中的应用逻辑代码。
    - components 文件夹下是板级支持包，包括各外设驱动，面向底层。
    - tinyshm 文件夹下是 TinySHM 框架代码， 包括给类面向结构健康监测边缘计算的各模块，面向顶层。
    - build 文件夹是编译生成的文件夹，存放编译生成的文件。 

!!! tip "重要提示"
    每次增加新的模块，一定要记得在对应CMakelists.txt文件中添加新的模块路径，否则编译时会出现找不到文件的错误。除了模块（source and include）需要添加路径外，依赖（requirement）也需要在对应的CMakelists.txt文件中添加。比如，如果使用了GPIO相关功能，则需要添加driver，如果使用了定时器，则需要添加esp_timer。