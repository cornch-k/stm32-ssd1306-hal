#ifndef FONT_ASCII_H
#define FONT_ASCII_H

#include <stdint.h>

#define FONT_ASCII_HEIGHT 12
#define FONT_ASCII_START 0x20
#define FONT_ASCII_END   0x7E
#define FONT_ASCII_COUNT 95

extern const uint8_t font_ascii_width[FONT_ASCII_COUNT];
extern const uint8_t font_ascii_data[FONT_ASCII_COUNT][24];

#endif /* FONT_ASCII_H */
