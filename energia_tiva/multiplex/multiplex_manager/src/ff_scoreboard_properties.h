// number of microseconds to wait before refreshing all matrices
// microseconds. 4ms = <62.5Hz/display, 25% duty cycle
#define REFRESH_WAIT 400 

// Enable serial/UART print statements
#define DEBUG true
// Enable even more statements
#define VERBOSE false

#define PIXELS_PER_MATRIX 22
#define MATRICES_PER_DISPLAY 4

const int pixelPin[PIXELS_PER_MATRIX] = {28, 27, 26, 25, 2, 10, 8, 5, 31, 32, 33, 34, 35, 36, 37, 39, 38, 40, 11, 12, 13, 17};
const int matrixPin[MATRICES_PER_DISPLAY] = {14, 15, 18, 19};
extern int matrixValue[MATRICES_PER_DISPLAY] = {12, 12, 12, 12}; // set time by reading serial
// TODO set to {10, 10, 10, 10} for final, so matrix is blank on failed initial read
const int numberIndexInString[MATRICES_PER_DISPLAY] = {1, 2, 4, 5}; // W, X, Y, Z in "+WX:YZ"

// ref: https://cdn.discordapp.com/attachments/882335631102079006/896048973012402226/image0.jpg
// (B00010011 << 16) + (B01100100 << 8) + B11010110;
#define GLYPH_ZERO  0x1364d6
// (B00010100 << 16) + (B00010010 << 8) + B00100100;
#define GLYPH_ONE   0x141224
// (B00111010 << 16) + (B10010000 << 8) + B01010110;
#define GLYPH_TWO   0x3a9056
// (B00010011 << 16) + (B00010000 << 8) + B01010110;
#define GLYPH_THREE 0x131056
// (B00100001 << 16) + (B11100101 << 8) + B01101000;
#define GLYPH_FOUR  0x21c568
// (B00010011 << 16) + (B00100011 << 8) + B10011111;
#define GLYPH_FIVE  0x13239f
// (B00010011 << 16) + (B01011100 << 8) + B10010110;
#define GLYPH_SIX   0x135c96
// (B00001010 << 16) + (B10010000 << 8) + B01001111;
#define GLYPH_SEVEN 0x0a904f
// (B00010011 << 16) + (B01011000 << 8) + B11010110;
#define GLYPH_EIGHT 0x1358d6
// (B00010001 << 16) + (B00111000 << 8) + B11010110;
#define GLYPH_NINE  0x1138d6
// (B00000000 << 16) + (B00000000 << 8) + B00000000;
#define GLYPH_ALL_OFF 0x000000
// (B00111111 << 16) + (B11111111 << 8) + B11111111;
#define GLYPH_ALL_ON  0x3fffff
/////////
#define GLYPH_S
#define GLYPH_E
#define GLYPH_T
#define GLYPH_EX_PT
// add 'S', 'E', 'T', '!', set glyphs_count = 16
// if adding/removing glyphs, be sure to update GLYPHS_COUNT
// Number of glyphs encoded for display on any given matrix
#define GLYPHS_COUNT 12

const uint32_t glyphs[GLYPHS_COUNT] = {GLYPH_ZERO, GLYPH_ONE, GLYPH_TWO, GLYPH_THREE, GLYPH_FOUR, GLYPH_FIVE, GLYPH_SIX, GLYPH_SEVEN, GLYPH_EIGHT, GLYPH_NINE, GLYPH_ALL_OFF, GLYPH_ALL_ON}; // ess, eee, tee);
