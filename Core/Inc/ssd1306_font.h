#ifndef SSD1306_FONT_H
#define SSD1306_FONT_H

#include "ssd1306.h"
#include <stdint.h>
#include <stdbool.h>

void SSD1306_SetCursor(uint8_t x, uint8_t y);
void SSD1306_GetCursor(uint8_t *x, uint8_t *y);
uint8_t SSD1306_WriteChar(uint32_t codepoint, uint8_t color);
void SSD1306_WriteString(const char *str, uint8_t color);
void SSD1306_WriteStringAt(uint8_t x, uint8_t y, const char *str, uint8_t color);

#endif
