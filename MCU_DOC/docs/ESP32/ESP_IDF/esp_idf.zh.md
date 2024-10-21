# 乐鑫物联网开发框架 (ESP-IDF)

!!! info
    **ESP-IDF（乐鑫物联网开发框架）** 是乐鑫科技为ESP32系列芯片提供的官方开发框架。它为开发者提供了一整套工具和库，帮助创建基于ESP32设备的稳健应用。ESP-IDF支持FreeRTOS、Wi-Fi、蓝牙以及多种外设接口。该框架兼容GCC工具链，支持C和C++等多种编程语言，包含网络、安全、功耗管理和驱动开发等组件，非常适合广泛的物联网应用开发。

## 安装

!!! note
    在使用方式上，有三种使用ESP-IDF的方式：

    - ESP-IDF命令提示符：这是使用ESP-IDF的默认方式。它是一个命令行界面，提供了ESP-IDF开发所需的工具和实用程序。

    - ESP-IDF集成开发环境：这是一个提供ESP-IDF开发图形界面的集成开发环境。它包括ESP-IDF命令提示符、文本编辑器和项目管理器等工具。

    - IDE插件：这些插件将ESP-IDF与流行的IDE（如Visual Studio Code和Eclipse）集成。它们提供代码补全、语法高亮和调试支持等功能。这是使用ESP-IDF最流行的方式。

<div class="grid cards" markdown>

-   :fontawesome-brands-bilibili:{ .lg .middle } __【乐鑫教程】｜使用一键安装工具快速搭建 ESP-IDF 开发环境 (Windows) 🎯🏆✅__

    ---

    [:octicons-arrow-right-24: <a href="https://www.bilibili.com/video/BV1to4y177ko/?spm_id_from=333.999.0.0&vd_source=5a427660f0337fedc22d4803661d493f" target="_blank"> 传送门 </a>](#)

-   :fontawesome-brands-bilibili:{ .lg .middle } __【乐鑫教程】｜使用 VS Code 快速搭建 ESP-IDF 开发环境 (Windows、Linux、MacOS) 🎯🏆✅__

    ---

    Recommended.

    [:octicons-arrow-right-24: <a href="https://www.bilibili.com/video/BV1V24y1T75n/?spm_id_from=333.999.0.0&vd_source=5a427660f0337fedc22d4803661d493f" target="_blank"> 传送门 </a>](#)

</div>

## 官方指南

### 在线文档

<div class="grid cards" markdown>

-   :simple-espressif:{ .lg .middle } __ESP-IDF 编程指南 🎯🏆__

    ---

    [:octicons-arrow-right-24: <a href="https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/index.html" target="_blank"> 传送门 </a>](#)

</div>  

### 视频教程

<div class="grid cards" markdown>

-   :fontawesome-brands-bilibili:{ .lg .middle } __【乐鑫教程】| 乐鑫物联网开发框架 ESP-IDF 开发入门 🎯🏆✅__

    ---

    [:octicons-arrow-right-24: <a href="https://www.bilibili.com/video/BV1tY4y1L7HV/?spm_id_from=333.999.0.0&vd_source=5a427660f0337fedc22d4803661d493f" target="_blank"> 传送门 </a>](#)

-   :fontawesome-brands-bilibili:{ .lg .middle } __【乐鑫教程】| 乐鑫 AIoT 开发资源与应用讲解 🎯🏆✅__

    ---

    [:octicons-arrow-right-24: <a href="https://www.bilibili.com/video/BV1uY411N7ns/?spm_id_from=333.999.0.0&vd_source=5a427660f0337fedc22d4803661d493f" target="_blank"> 传送门 </a>](#)

-   :fontawesome-brands-bilibili:{ .lg .middle } __【乐鑫教程】| 基于乐鑫 ESP32-S3 的 AIoT 编程实战 🎯🏆✅__

    ---

    [:octicons-arrow-right-24: <a href="https://www.bilibili.com/video/BV1Jr4y1E79s/?spm_id_from=333.999.0.0&vd_source=5a427660f0337fedc22d4803661d493f" target="_blank"> 传送门 </a>](#)

</div>

<iframe src="http://www.cuishuaiwen.com:7500/DEV/ESP32/OFFICIAL/briefing.pdf" width="100%" height="600px"></iframe> 

## 第三方教程

<div class="grid cards" markdown>

-   :fontawesome-brands-bilibili:{ .lg .middle } __孤独的二进制 ESP-IDF 教程 🎯🏆__

    ---

    [:octicons-arrow-right-24: <a href="https://www.bilibili.com/video/BV1hM411k7zz/?spm_id_from=333.999.0.0" target="_blank"> 传送门 </a>](#)

-   :fontawesome-brands-bilibili:{ .lg .middle } __【2024最新版 ESP32教程（基于ESP-IDF）】ESP32入门级开发课程 更新中 中文字幕 🎯🏆__

    ---

    [:octicons-arrow-right-24: <a href="https://www.bilibili.com/video/BV1eRg7exEcT/?spm_id_from=333.788.recommend_more_video.0&vd_source=5a427660f0337fedc22d4803661d493f" target="_blank"> 传送门 </a>](#)

</div>

## FREERTOS

由于ESP-IDF是基于FreeRTOS的，因此学习FreeRTOS对于理解ESP-IDF非常重要。

<div class="grid cards" markdown>

-   :fontawesome-brands-bilibili:{ .lg .middle } __ESP32_freeRTOS教程 🎯🏆__

    ---

    [:octicons-arrow-right-24: <a href="https://www.bilibili.com/video/BV1Nb4y1q7xz/?spm_id_from=333.337.search-card.all.click&vd_source=5a427660f0337fedc22d4803661d493f" target="_blank"> 传送门 </a>](#)

-   :fontawesome-brands-bilibili:{ .lg .middle } __孤独的二进制 FREERTOS 教程__

    ---

    基于ArduinoIDE

    [:octicons-arrow-right-24: <a href="https://www.bilibili.com/video/BV1q54y1Z7ca/?spm_id_from=333.999.0.0&vd_source=5a427660f0337fedc22d4803661d493f" target="_blank"> 传送门 </a>](#)


</div>