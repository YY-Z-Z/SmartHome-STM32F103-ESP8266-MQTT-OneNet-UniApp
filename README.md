# 🏠 SmartHome-STM32F103-ESP8266-MQTT-OneNet-UniApp
**基于STM32F103的双架构智能家居控制项目（SPL标准库 / HAL库 双实现）**

## 📌 项目简介
本项目基于**STM32F103C8T6**微控制器，通过ESP8266 WiFi模块接入OneNet物联网平台，实现了一套完整的**智能家居数据采集、远程控制、状态反馈**系统。
项目同时提供**SPL标准库**与**HAL库**两套独立完整实现，兼顾底层开发学习价值与现代嵌入式开发效率。

## ✨ 项目核心亮点
- ✅ **双库双实现**：同时支持 SPL 标准库 + HAL 库，一套业务逻辑，两套底层实现，深度对比学习
- ✅ **完整物联网链路**：STM32 + ESP8266 + MQTT + OneNet + UniApp 全栈打通
- ✅ **模块化分步开发**：从基础外设到联网通信，按阶段拆分工程，循序渐进、极易上手
- ✅ **最终整合代码**：两个库均提供完整版 Final Code，直接烧录即可运行全套功能
- ✅ **配套齐全**：包含完整开发笔记、串口调试工具
- ✅ **实用智能家居功能**：温湿度采集、OLED本地显示、LED远程控制、按键交互、数据上传云端

## 📁 项目目录结构
```plaintext
SmartHome-STM32F103-ESP8266-MQTT-OneNet-UniApp/
├── STM32_HAL/                  # HAL库实现（CubeMX + VSCode 开发）
│   ├── 1_Led/                  # LED基础实验
│   ├── 2_Printf/               # 串口重定向
│   ├── 3_Key/                  # 按键检测
│   ├── 4_Dht11/                # 温湿度采集
│   ├── 5_Connect_Wifi/         # ESP8266 连WiFi
│   ├── 6_Connect_Wifi_2/       # WiFi 增强连接
│   ├── 7_Mqtt_Server/          # MQTT 服务器连接
│   ├── 8_Pub_Sub/              # 发布/订阅
│   ├── 9_Set_Reply/            # 指令应答与状态同步
│   ├── 10_OLED/                # OLED 屏幕驱动
│   ├── Final_Code/             # HAL 最终整合代码
│   └── TEST/                   # 测试工程
├── STM32_SPL/                  # SPL标准库实现
│   ├── 01_搭建工程/
│   ├── 02_点亮LED/
│   ├── 03_按键控制LED/
│   ├── 04_驱动温湿度传感器/
│   ├── 05_连接wifi/
│   ├── 06_连接MQTT服务器/
│   ├── 07_设备登录/
│   ├── 08_数据上传服务器/
│   ├── 09_下发命令控制LED/
│   ├── 10_APP/
│   ├── 11_OLED屏幕显示初始化过程信息/
│   ├── 12_OLED屏幕显示传感器数值/
│   ├── source/
│   └── SPL_FinallyCode/        # SPL 最终整合代码
├── Note_SmartHome.html         # 开发笔记
└── XCOM V2.6.exe               # 专用串口调试助手
```

## 🛠️ 硬件平台
- 主控：STM32F103C8T6
- WiFi模块：ESP8266-01S
- 传感器：DHT11 温湿度
- 显示：0.96寸 I2C OLED
- 外设：LED、按键

## 🧰 开发环境
- HAL 库：STM32CubeMX + VSCode 
- SPL 库：Keil MDK5
- 调试：XCOM 串口助手
- 云平台：OneNet

## 🚀 快速使用
1. 选择开发库：`STM32_HAL` 或 `STM32_SPL`
2. 按序号工程分步学习、调试
3. 配置 OneNet 平台信息（产品ID、设备ID、鉴权信息）
4. 直接烧录 `Final_Code` / `SPL_FinallyCode` 运行完整功能
5. 使用配套笔记与串口工具辅助调试

---

## 📝 说明
- 本项目两套代码**功能完全一致**，仅底层驱动实现不同，便于对比学习
