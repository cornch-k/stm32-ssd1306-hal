#include "ssd1306_font.h"
#include "font_ascii.h"
#include "font_hangul.h"

static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

void SSD1306_SetCursor(uint8_t x, uint8_t y)
{
    cursor_x = x;
    cursor_y = y;
}

void SSD1306_GetCursor(uint8_t *x, uint8_t *y)
{
    if (x) *x = cursor_x;
    if (y) *y = cursor_y;
}

static void SSD1306_DrawGlyph(const uint8_t *data, uint8_t x, uint8_t y, 
                               uint8_t width, uint8_t color)
{
    for (uint8_t row = 0; row < FONT_ASCII_HEIGHT; row++) {
        uint8_t byte_hi = data[row * 2];
        uint8_t byte_lo = data[row * 2 + 1];
        
        for (uint8_t col = 0; col < width; col++) {
            uint8_t pixel;
            if (col < 8) {
                pixel = (byte_hi >> (7 - col)) & 1;
            } else {
                pixel = (byte_lo >> (7 - (col - 8))) & 1;
            }
            
            if (pixel) {
                SSD1306_DrawPixel(x + col, y + row, color);
            }
        }
    }
}

static uint32_t utf8_decode(const char *str, uint8_t *bytes_consumed)
{
    uint8_t c = (uint8_t)str[0];
    
    if (c == 0) {
        *bytes_consumed = 0;
        return 0;
    }
    
    if ((c & 0x80) == 0) {
        *bytes_consumed = 1;
        return c;
    }
    
    if ((c & 0xE0) == 0xC0) {
        *bytes_consumed = 2;
        return ((c & 0x1F) << 6) | ((uint8_t)str[1] & 0x3F);
    }
    
    if ((c & 0xF0) == 0xE0) {
        *bytes_consumed = 3;
        return ((c & 0x0F) << 12) | 
               (((uint8_t)str[1] & 0x3F) << 6) | 
               ((uint8_t)str[2] & 0x3F);
    }
    
    if ((c & 0xF8) == 0xF0) {
        *bytes_consumed = 4;
        return ((c & 0x07) << 18) | 
               (((uint8_t)str[1] & 0x3F) << 12) | 
               (((uint8_t)str[2] & 0x3F) << 6) | 
               ((uint8_t)str[3] & 0x3F);
    }
    
    *bytes_consumed = 1;
    return 0xFFFFFFFF;
}

uint8_t SSD1306_WriteChar(uint32_t codepoint, uint8_t color)
{
    const uint8_t *data = NULL;
    uint8_t char_width = 0;
    
    /* ASCII */
    if (codepoint >= FONT_ASCII_START && codepoint <= FONT_ASCII_END) {
        uint8_t idx = codepoint - FONT_ASCII_START;
        data = font_ascii_data[idx];
        char_width = font_ascii_width[idx];
    }
    /* 한글 */
    else if (codepoint >= FONT_HANGUL_START && codepoint <= FONT_HANGUL_END) {
        uint16_t idx = codepoint - FONT_HANGUL_START;
        data = font_hangul_data[idx];
        char_width = FONT_HANGUL_WIDTH;
    }
    else {
        /* 지원하지 않는 문자는 네모 표시 대신 빈 칸 */
        return 0;
    }
    
    if (cursor_x + char_width > SSD1306_WIDTH) {
        return 0;
    }
    if (cursor_y + FONT_ASCII_HEIGHT > SSD1306_HEIGHT) {
        return 0;
    }
    
    SSD1306_DrawGlyph(data, cursor_x, cursor_y, char_width, color);
    cursor_x += char_width;
    
    return char_width;
}


void SSD1306_WriteString(const char *str, uint8_t color)
{
    while (*str) {
        if (*str == '\n') {
            cursor_x = 0;
            cursor_y += FONT_ASCII_HEIGHT;
            str++;
            continue;
        }

        uint8_t bytes;
        uint32_t codepoint = utf8_decode(str, &bytes);
        
        if (bytes == 0 || codepoint == 0xFFFFFFFF) {
            str++;
            continue;
        }

        uint8_t char_width = 0;
        if (codepoint >= FONT_ASCII_START && codepoint <= FONT_ASCII_END) {
            char_width = font_ascii_width[codepoint - FONT_ASCII_START];
        } else if (codepoint >= FONT_HANGUL_START && codepoint <= FONT_HANGUL_END) {
            char_width = FONT_HANGUL_WIDTH;
        }
        
        if (char_width > 0 && cursor_x + char_width > SSD1306_WIDTH) {
            cursor_x = 0;
            cursor_y += FONT_ASCII_HEIGHT;
        }
        
        if (cursor_y + FONT_ASCII_HEIGHT > SSD1306_HEIGHT) {
            break;
        }
        
        SSD1306_WriteChar(codepoint, color);
        str += bytes;
    }
}


void SSD1306_WriteStringAt(uint8_t x, uint8_t y, const char *str, uint8_t color)
{
    SSD1306_SetCursor(x, y);
    SSD1306_WriteString(str, color);
}
