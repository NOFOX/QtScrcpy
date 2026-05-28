# QtScrcpy 

[![Financial Contributors to Open Collective](https://opencollective.com/QtScrcpy/all/badge.svg?label=financial+contributors)](https://opencollective.com/QtScrcpy)
![Windows](https://github.com/barry-ran/QtScrcpy/workflows/Windows/badge.svg)
![MacOS](https://github.com/barry-ran/QtScrcpy/workflows/MacOS/badge.svg)
![Ubuntu](https://github.com/barry-ran/QtScrcpy/workflows/Ubuntu/badge.svg)

![license](https://img.shields.io/badge/license-Apache2.0-blue.svg)
![release](https://img.shields.io/github/v/release/barry-ran/QtScrcpy.svg)
![star](https://img.shields.io/github/stars/barry-ran/QtScrcpy.svg)

[中文用户？点我查看中文介绍](README_zh.md)

QtScrcpy supports displaying and controlling Android devices via USB or over network. It does NOT require root privileges.

It supports three major platforms: GNU/Linux, Windows and macOS.

## New Feature: 8x3 Phone Wall Matrix
The latest version introduces a professional **Phone Wall** interface designed for multi-device management:

- **Fixed 8x3 Grid**: Manage up to 24 devices simultaneously in a clean, high-performance grid.
- **Real-time Preview**: Each slot shows a live video preview of the connected device.
- **Double-Click to Expand**: Instantly expand any preview to a large, high-resolution overlay for detailed control.
- **Apple-Style Floating Toolbar**: Modern, translucent floating UI for quick device actions.
- **Smooth Restore**: One-click restore from large view back to its original slot without layout disruption.
- **Modern UI**: Sleek dark theme with frameless window design.

![phonewall](docs/image/phonewall_preview.png)

## Key Features

 - **Lightness**: Displays only the device screen or a high-performance grid.
 - **Performance**: Supports 30~60 fps with OpenGL YUV rendering.
 - **Multi-Device Matrix**: Professional 24-slot grid for massive device management.
 - **Low Latency**: Optimized for 35~70ms latency.
 - **Non-intrusiveness**: Nothing installed on the device.

## Build Requirements
- Qt 6.x (Recommended) or Qt 5.15+
- CMake 3.16+
- FFmpeg 4.x+

## How to Run
1. Connect your Android devices via USB.
2. Enable USB Debugging on each device.
3. Run `QtScrcpy.exe`.
4. Devices will automatically appear in the **Phone Wall** slots.
5. **Double-click** any slot to expand for full control.
6. Use the **Restore** button on the floating toolbar to return to the grid.

## Thanks
QtScrcpy is based on [Genymobile](https://github.com/Genymobile)'s [scrcpy](https://github.com/Genymobile/scrcpy) project.

The difference between QtScrcpy and the original scrcpy:
- **UI**: Modern Qt-based GUI vs SDL.
- **Rendering**: OpenGL YUV rendering for high efficiency.
- **Multi-Device**: Native support for massive phone walls.
- **Keymap**: Support for custom keyboard and mouse mapping.

## Learn
Telegram Group: https://t.me/+EnQNmb47C_liYmRl
Course introduction: [CSDN Blog](https://blog.csdn.net/rankun1/article/details/87970523)
