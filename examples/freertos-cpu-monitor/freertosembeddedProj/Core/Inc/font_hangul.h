#ifndef FONT_HANGUL_H
#define FONT_HANGUL_H

#include <stdint.h>

#define FONT_HANGUL_WIDTH  12
#define FONT_HANGUL_HEIGHT 12
#define FONT_HANGUL_START  0xAC00
#define FONT_HANGUL_END    0xD7A3
#define FONT_HANGUL_COUNT  11172

extern const uint8_t font_hangul_data[FONT_HANGUL_COUNT][24];

#endif /* FONT_HANGUL_H */
