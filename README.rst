# ILI9341 Display Driver with LVGL on Zephyr RTOS (NCS 2.9.0)

This repository demonstrates how to interface the ILI9341 display controller using the LVGL graphics library on Zephyr RTOS with Nordic Connect SDK (NCS) version **2.9.0**. The display communication is based on the **MIPI DBI (Display Bus Interface)** standard over SPI.

---

## 📷 Overview

- ✅ Zephyr-based project for embedded GUIs  
- ✅ MIPI DBI Type-C (SPI-based) interface  
- ✅ ILI9341 TFT LCD driver  
- ✅ LVGL for UI rendering  
- ✅ RTT-based shell for real-time debugging  
- ✅ Tested with NCS 2.9.0

---

## 🧠 What is MIPI DBI?

**MIPI DBI (Display Bus Interface)** is a part of the MIPI Display Serial Interface standards. It's commonly used to connect display controllers (like ILI9341) to microcontrollers.

- **DBI Type C Option 3**: SPI-based serial interface (what ILI9341 uses)
- Allows low-pin-count connection between MCU and display
- Ideal for small, embedded displays with low refresh rate requirements

In this project, Zephyr’s `display` and `mipi_dbi` subsystems manage the communication with the display via SPI using a framebuffer model.

---

## 🧱 Hardware Requirements

- **MCU/SoC**: Nordic nRF52, nRF53, or any Zephyr-compatible board with SPI
- **Display**: ILI9341 (320x240, SPI interface)
- **Optional**: SEGGER RTT viewer (for shell/logs)

---

## 🛠️ Software Requirements

- **nRF Connect SDK**: Version **2.9.0**
- **Zephyr RTOS**: Integrated into NCS
- **West**: Build tool for Zephyr-based projects
- **LVGL**: Integrated through Zephyr’s module system

---

## 🔧 Configuration Highlights (`prj.conf`)

```ini
CONFIG_DISPLAY=y
CONFIG_ILI9341=y
CONFIG_LVGL=y
CONFIG_LV_USE_LABEL=y
CONFIG_LV_USE_BTN=y
CONFIG_LV_FONT_MONTSERRAT_14=y
CONFIG_USE_SEGGER_RTT=y
CONFIG_SHELL=y
