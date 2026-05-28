# QtScrcpy

![Windows](https://github.com/barry-ran/QtScrcpy/workflows/Windows/badge.svg)
![MacOS](https://github.com/barry-ran/QtScrcpy/workflows/MacOS/badge.svg)
![Ubuntu](https://github.com/barry-ran/QtScrcpy/workflows/Ubuntu/badge.svg)

![license](https://img.shields.io/badge/license-Apache2.0-blue.svg)
![release](https://img.shields.io/github/v/release/barry-ran/QtScrcpy.svg)
![star](https://img.shields.io/github/stars/barry-ran/QtScrcpy.svg)

[Speaks English? Click me for English introduction.](README.md)

QtScrcpy 可以通过 USB / 网络连接Android设备，并进行显示和控制。无需root权限。

同时支持 GNU/Linux ，Windows 和 MacOS 三大主流桌面平台。

## 新特性：8x3 专业手机墙矩阵
最新版本引入了全新的 **手机墙 (Phone Wall)** 界面，专为大规模多设备管理设计：

- **固定 8x3 网格**：支持同时管理多达 24 台设备，界面整齐高效。
- **实时预览**：每个槽位（Slot）直接显示手机屏幕的实时缩小版预览。
- **双击展开**：双击任意预览位，手机屏幕立即以大尺寸 Overlay 形式弹出到主窗口中心。
- **类苹果风格悬浮工具栏**：现代化半透明悬浮 UI，支持快速控制。
- **一键还原**：点击工具栏顶部的红色还原按钮，画面平滑缩回原位，不影响 8x3 布局。
- **极简 UI 设计**：采用无边框窗口设计，深色主题，视觉更加专业。

![phonewall](docs/image/phonewall_preview.png)

## 核心特性

 - **精致**：仅显示设备屏幕或高性能设备矩阵。
 - **高性能**：支持 30~60fps，采用 OpenGL YUV 高效渲染。
 - **大规模管理**：专业 24 槽位网格，满足批量操作需求。
 - **低延迟**：优化至 35~70ms 延迟。
 - **非侵入性**：不在设备上安装任何软件。

## 编译要求
- Qt 6.x (推荐) 或 Qt 5.15+
- CMake 3.16+
- FFmpeg 4.x+

## 运行说明
1. 通过 USB 连接 Android 设备。
2. 确保已开启 USB 调试。
3. 运行 `QtScrcpy.exe`。
4. 设备将自动出现在 **手机墙** 的槽位中。
5. **双击** 任意槽位可展开进行详细控制。
6. 使用悬浮工具栏上的 **还原** 按钮返回网格预览。

## 感谢
本项目基于 [Genymobile](https://github.com/Genymobile) 的 [scrcpy](https://github.com/Genymobile/scrcpy) 项目进行重构。

QtScrcpy 与原版 Scrcpy 的区别：
- **界面**：基于 Qt 的现代化图形界面 vs SDL。
- **渲染**：采用 OpenGL YUV 渲染，效率更高。
- **多设备支持**：原生支持大规模手机墙矩阵。
- **按键映射**：支持自定义键鼠映射脚本。

## 学习交流
QQ群号：901736468
课程介绍：[CSDN 博客](https://blog.csdn.net/rankun1/article/details/87970523)
