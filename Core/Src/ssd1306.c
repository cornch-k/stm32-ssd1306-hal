#include "ssd1306.h"
#include "i2c.h"

extern I2C_HandleTypeDef hi2c1;


static uint8_t SSD1306_Buffer[8][128];

static void SSD1306_WriteCommand(uint8_t cmd)
{
    uint8_t data[2];
    data[0] = 0x00;
    data[1] = cmd;

    HAL_I2C_Master_Transmit(&hi2c1, SSD1306_I2C_ADDR, data, 2, SSD1306_TIMEOUT);
}

static void SSD1306_WriteData(uint8_t data)
{
    uint8_t buf[2];
    buf[0] = 0x40;
    buf[1] = data;
    
    HAL_I2C_Master_Transmit(&hi2c1, SSD1306_I2C_ADDR, buf, 2, SSD1306_TIMEOUT);
}


void SSD1306_Init(void)
{
    HAL_Delay(100);
    
    SSD1306_WriteCommand(0xA8);
    SSD1306_WriteCommand(0x3F);

    SSD1306_WriteCommand(0xD3);
    SSD1306_WriteCommand(0x00);

    SSD1306_WriteCommand(0x40);

    SSD1306_WriteCommand(0xA0);
    // SSD1306_WriteCommand(0xA1);

    SSD1306_WriteCommand(0xC0);

    SSD1306_WriteCommand(0xDA);
    SSD1306_WriteCommand(0x12);

    SSD1306_WriteCommand(0x81);
    SSD1306_WriteCommand(0x7F);

    SSD1306_WriteCommand(0xA4);
    
    SSD1306_WriteCommand(0xA6);
    
    SSD1306_WriteCommand(0xD5);
    SSD1306_WriteCommand(0x80);
    
    SSD1306_WriteCommand(0x8D);
    SSD1306_WriteCommand(0x14);
    
    SSD1306_WriteCommand(0xAF);
    
}

void SSD1306_UpdateScreen(void)
{
for (uint8_t i = 0; i < 8; i++) {

        SSD1306_WriteCommand(0xB0 + i); 
        SSD1306_WriteCommand(0x00);
        SSD1306_WriteCommand(0x10);

        HAL_I2C_Mem_Write(&hi2c1, SSD1306_I2C_ADDR, 0x40, 1, &SSD1306_Buffer[i][0], 128, SSD1306_TIMEOUT);
    }
}

void SSD1306_Fill(uint8_t color)
{
    memset(SSD1306_Buffer, (color==1) ? 0xff : 0x00, sizeof(SSD1306_Buffer));
}

void SSD1306_DrawPixel(uint8_t x, uint8_t y, uint8_t color)
{
    if(y > 63 || x > 127){
        return;
    }
    (color == 1) ? (SSD1306_Buffer[y >> 3][x] |= (1 << (y % 8))) : (SSD1306_Buffer[y >> 3][x] &= ~(1 << (y % 8)));
}

void SSD1306_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color)
{

}

void SSD1306_DrawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color)
{
    
}