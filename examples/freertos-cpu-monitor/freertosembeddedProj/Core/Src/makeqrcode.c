#include "stdbool.h"
#include "stdint.h"
#include "qrcodegen.h"
#include "ssd1306.h"

static uint8_t qr0[qrcodegen_BUFFER_LEN_MAX];
static uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];



void createQR(void){
    bool myProfile = qrcodegen_encodeText(
        "https://github.com/cornch-k",
        tempBuffer,
        qr0,
        qrcodegen_Ecc_MEDIUM,
        qrcodegen_VERSION_MIN,
        qrcodegen_VERSION_MAX,
        qrcodegen_Mask_AUTO,
        true
    );

    if(!myProfile) return;
}

void renderQR(uint8_t startX, uint8_t startY){
    int size = qrcodegen_getSize(qr0);
    int scale = 2;
    for(int y = 0; y < size; y++){
        for(int x = 0; x < size; x++){
            if(qrcodegen_getModule(qr0, x, y)){
                for(int dy = 0; dy < scale; dy++){
                    for(int dx = 0; dx < scale; dx++){
                        SSD1306_DrawPixel(startX+(x*scale), startY+(y*scale), 1);
                    }
                }
            }
            else {
                for(int dy = 0; dy < scale; dy++){
                    for(int dx = 0; dx < scale; dx++){
                        SSD1306_DrawPixel(startX+(x*scale), startY+(y*scale), 0);
                    }
                }
            }
        }
    }
    SSD1306_UpdateScreen();
}