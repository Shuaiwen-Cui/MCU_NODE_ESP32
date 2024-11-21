# 项目框架

## 介绍

!!! note "项目框架"
    在完成项目初始化之后，我们还需要对生成的项目进行重新组织和整理，以使得其更好地支撑我们的项目开发。本节将介绍如何对项目进行重新组织和整理。

## 项目框架

在本项目中，项目代码组织结构如下：

```shell
project-name/
├── CMakeLists.txt          # 项目的顶层构建文件
├── partitions-16MiB.csv    # 分区表
├── sdkconfig               # 当前配置文件
├── sdkconfig.old           # 旧的配置文件，用作参考
├── main/                   # 主应用程序代码
│   ├── CMakeLists.txt      # main目录的构建文件
│   ├── main.c              # 应用程序入口点
│   └── app/                # 应用程序逻辑
│       ├── app.c           # 应用层实现
│       ├── app.h           # 应用接口的头文件
│       └── ...             # 其他文件
├── components/             # 外围模块
│   ├── CMakeLists.txt      # components目录的构建文件
│   ├── setup/              # setup模块
│   │   ├── setup.h         # setup模块的头文件
│   │   └── setup.c         # setup模块的实现
│   ├── component1/         # component1模块
│   │   ├── component1.h    # component1的头文件
│   │   ├── component1.c    # component1的实现
│   │   └── ...
│   └── ...                 # 其他外围模块
├── tinyshm/                # tinyshm框架
│   ├── CMakeLists.txt      # tinyshm目录的构建文件
│   ├── config/             # 配置模块
│   │   ├── config.h        # 配置模块的头文件
│   │   └── config.c        # 配置模块的实现
│   ├── componentA/         # componentA模块
│   │   ├── componentA.h    # componentA的头文件
│   │   ├── componentA.c    # componentA的实现
│   │   └── ...
│   └── ...                 # 其他模块
├── build/                  # 构建目录（自动生成）
│   └── ...                 # 构建过程中生成的文件
└── README.md               # 项目文档
```

!!! note
    - main 文件夹下是主程序代码，包括在子文件夹app中的应用逻辑代码。
    - components 文件夹下是板级支持包，包括各外设驱动，面向底层。
    - tinyshm 文件夹下是 TinySHM 框架代码， 包括给类面向结构健康监测边缘计算的各模块，面向顶层。
    - build 文件夹是编译生成的文件夹，存放编译生成的文件。 

!!! tip "重要提示"
    每次增加新的模块，一定要记得在对应CMakelists.txt文件中添加新的模块路径，否则编译时会出现找不到文件的错误。除了模块（source and include）需要添加路径外，依赖（requirement）也需要在对应的CMakelists.txt文件中添加。比如，如果使用了GPIO相关功能，则需要添加driver，如果使用了定时器，则需要添加esp_timer。