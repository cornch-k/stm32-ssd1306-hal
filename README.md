# STM32F4 SSD1306 OLED Driver (I2C)

## 📝 Introduction

이 프로젝트는 **STM32F411RE (Nucleo-64)** 보드에서 **SSD1306 OLED 디스플레이**를 제어하기 위한 I2C 드라이버입니다.
STM32 HAL 라이브러리를 기반으로 작성되었으며, Frame Buffer 방식을 사용하여 그래픽을 처리합니다.

## 🛠 Hardware Environment

- **MCU**: STM32F411RE (Nucleo-64 Board)
- **Display**: 0.96" SSD1306 OLED (128 \* 64)
- **Interface**: I2C (Fast Mode)

## 🔌 Pin Map

| Pin Function | STM32 Pin | Nucleo Header | Description    |
| :----------- | :-------- | :------------ | :------------- |
| **I2C1_SCL** | **PB8**   | **SCL / D15** | I2C Clock Line |
| **I2C1_SDA** | **PB9**   | **SDA / D14** | I2C Data Line  |
| **VCC**      | 3.3V      | 3V3           | Power Supply   |
| **GND**      | GND       | GND           | Ground         |

## 💻 Software Stack

- **IDE/Tool**: VSCode & STM32CubeMX
- **Library**: STM32 HAL Driver
- **Language**: C

## 🚀 Key Features

- **Initialization**: SSD1306의 내부 Charge Pump 및 Memory Mode 설정 초기화
- **Screen Buffer**: 1KB (128 \* 64 / 8 bytes) 프레임 버퍼 사용
- **Drawing Functions**:
  - `SSD1306_DrawPixel(x, y, color)`: 특정 좌표에 픽셀 점등
  - `SSD1306_Fill(color)`: 화면 전체 채우기/지우기
  - `SSD1306_UpdateScreen()`: 버퍼 내용을 디스플레이로 전송 (I2C Write)

## ✅ To-Do: Driver Implementation Status

현재 구현된 기능과 향후 구현 예정인 기능 목록입니다.

- [x] **Low-Level Interface**
  - [x] `SSD1306_WriteCommand()`: I2C 커맨드 전송
  - [x] `SSD1306_WriteData()`: I2C 데이터 전송
- [x] **Core Functions**
  - [x] `SSD1306_Init()`: 디스플레이 초기화 시퀀스
  - [x] `SSD1306_UpdateScreen()`: 프레임 버퍼(GDDRAM) 전송
  - [x] `SSD1306_Fill()`: 화면 클리어 및 채우기
- [x] **Graphic Primitives**
  - [x] `SSD1306_DrawPixel()`: 좌표 기반 픽셀 제어
  - [x] `SSD1306_DrawLine()`: 선 그리기
  - [x] `SSD1306_DrawRect()`: 사각형 그리기
- [x] **Typography**
  - [x] `SSD1306_SetCursor()`: 텍스트 커서 위치 설정
  - [x] `SSD1306_WriteChar()`: 폰트(ASCII, 한글 지원) 출력
  - [x] `SSD1306_WriteString()`: 문자열 출력

## 🖥️ Picture

한글과 영어 혼용이 가능합니다. 만약 한 줄 내에 모두 표기가 불가할 경우, 다음 줄에 나머지 내용이 표기됩니다.
![OLED Hello World Display](result/IMG_2036.jpg)

## 📝 Example

```c
/* Includes */
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "stdbool.h"
#include "ssd1306.h"
#include "ssd1306_font.h"

int main(void)
{
  /* MCU Configuration */
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init(); // I2C Init

  SSD1306_Init();

  while (1)
  {
    /* Clear Screen Buffer */
    SSD1306_Fill(0);

    /* Draw a Pixel at center */
    SSD1306_DrawPixel(64, 32, 1);

    /* Set Text Cursor */
    SSD1306_SetCursor(0, 0);

    /* Draw a text */
    SSD1306_WriteString("Hello, World!\n", 1);
    SSD1306_WriteString("다람쥐 헌 쳇바퀴에 타고파\n", 1);

    /* Update Display */
    SSD1306_UpdateScreen();

    HAL_Delay(1000);
  }
}
```
