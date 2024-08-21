# 架构

## 硬件架构

主控 + 感知 + 通信 + 交互

## 软件架构

物理层 -> 驱动层 -> 中间件层 -> 应用层 

## 开发工具链

| 工具链 | 描述 | 优势 | 劣势 |
| --- | --- | --- | --- |
| ESP_IDF | Espressif IoT Development Framework | 功能丰富，文档完善 | 学习曲线陡 |
| MICROPYTHON | Python for microcontrollers | 易学，开发迅速 | 资源有限 |
| ARDUINO | 开源电子平台 | 易用，社区庞大 | 资源有限 |

!!! note
    对于快速原型设计，我们使用 MICROPYTHON；对于高性能应用，我们使用 ESP_IDF。
