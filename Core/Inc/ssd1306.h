#ifndef SSD1306_H
#define SSD1306_H

#include "stm32f4xx_hal.h"
#include "string.h"
#include "stdbool.h"

#define SSD1306_I2C_ADDR 0x78
#define SSD1306_TIMEOUT 100
#define SSD1306_HEIGHT 64
#define SSD1306_WIDTH 128

void SSD1306_Init(void);
void SSD1306_UpdateScreen(void);

void SSD1306_Fill(uint8_t color);
void SSD1306_DrawPixel(uint8_t x, uint8_t y, uint8_t color);
void SSD1306_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
void SSD1306_DrawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);

// 구현예정
// void SSD1306_WriteChar(char ch, uint8_t x, uint8_t y);
// void SSD1306_WriteString(char* str, uint8_t x, uint8_t y);

#endif