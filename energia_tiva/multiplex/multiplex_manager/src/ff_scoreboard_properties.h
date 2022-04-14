// number of microseconds to wait before refreshing all matrices
// microseconds. 4ms = <62.5Hz/display, 25% duty cycle
#define REFRESH_WAIT 400

// Enable serial/UART print statements
#define DEBUG true
// Enable even more statements
#define VERBOSE false

#define PIXELS_PER_MATRIX 22
#define MATRICES_PER_DISPLAY 4

// Breadboard-compatible pins. should rewire breadboard to match PCB though
//const int pixelPin[PIXELS_PER_MATRIX] = {28, 27, 26, 25, 2, 10, 8, 5, 31, 32, 33, 34, 35, 36, 37, 39, 38, 40, 11, 12, 13, 17}; //breadboard // transpose 27-28 & 38-39
const int pixelPin[PIXELS_PER_MATRIX] = {
	27, 28, 26, 25, 2, 10, 
	8, // PA7: Special consideration, SSI0
	5, 31, 
	32, // PD7: Special consideration, GPIO
	33, 34, 35, 36, 37, 
	38, // PC3: Special consideration, JTAG/SWD
	39, 40, 
	11, // PA2: Special consideration, SSI0
	12, // PA3: Special consideration, SSI0
	13, // PA4: Special consideration, SSI0
	17  // PF0: Special consideration, GPIO 
};

/*const int matrixPin[MATRICES_PER_DISPLAY] = { // Breadboard
	14, 15, 18, 
	19  // PB2: Special consideration, I2C0
};*/
const int matrixPin[MATRICES_PER_DISPLAY] = {
	18, 
	19,  // PB2: Special consideration, I2C0
	14, 15
};


/* Special considerations for pixel pins and matrix pins:
https://web.archive.org/web/20220324051024/https://www.ti.com/lit/ds/spms376e/spms376e.pdf, p.650
To configure pins 8, 32, 38, 11, 12, 13, 17, and 19, (PA7, PD7, PC3, PA2, PA3, PA4, PF0, PB2)
the following must be done:
All listed (above) pins should be reconfigured as outputs (GPIO) with 2mA drive.

*/

int glyphIndex[MATRICES_PER_DISPLAY] = {34, 34, 34, 34}; // set time by reading serial
//int glyphIndex[MATRICES_PER_DISPLAY] = {11, 11, 11, 11}; // set time by reading serial
//int glyphIndex[MATRICES_PER_DISPLAY] = {0, 1, 1, 0}; // set time by reading serial
const int numberIndexInString[MATRICES_PER_DISPLAY] = {1, 2, 4, 5}; // W, X, Y, Z in "+WX:YZ"

// ref: https://cdn.discordapp.com/attachments/882335631102079006/896048973012402226/image0.jpg
// (B00010011 << 16) + (B01100100 << 8) + B11010110;
#define GLYPH_ZERO 0x1364D6
// (B00010100 << 16) + (B00010010 << 8) + B00100100;
#define GLYPH_ONE 0x141224
// (B00111010 << 16) + (B10010000 << 8) + B01010110;
#define GLYPH_TWO   0x3a9056
// (B00010011 << 16) + (B00010000 << 8) + B01010110;
#define GLYPH_THREE 0x131056
// (B00100001 << 16) + (B11100101 << 8) + B01101000;
#define GLYPH_FOUR 0x21E568
// (B00010011 << 16) + (B00100011 << 8) + B10011111;
#define GLYPH_FIVE 0x13239F
// (B00010011 << 16) + (B01011100 << 8) + B10010110;
#define GLYPH_SIX 0x135C96
// (B00001010 << 16) + (B10010000 << 8) + B01001111;
#define GLYPH_SEVEN 0xA904F
// (B00010011 << 16) + (B01011000 << 8) + B11010110;
#define GLYPH_EIGHT 0x1358D6
// (B00010001 << 16) + (B00111000 << 8) + B11010110;
#define GLYPH_NINE 0x1138D6
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
//#define GLYPHS_COUNT 12
#define GLYPHS_COUNT 35

//const uint32_t glyphs[GLYPHS_COUNT] = {GLYPH_ZERO, GLYPH_ONE, GLYPH_TWO, GLYPH_THREE, GLYPH_FOUR, GLYPH_FIVE, GLYPH_SIX, GLYPH_SEVEN, GLYPH_EIGHT, GLYPH_NINE, GLYPH_ALL_OFF, GLYPH_ALL_ON}; // ess, eee, tee);
const uint32_t glyphs[GLYPHS_COUNT] = {GLYPH_ZERO, GLYPH_ONE, GLYPH_TWO, GLYPH_THREE, GLYPH_FOUR, GLYPH_FIVE, GLYPH_SIX, GLYPH_SEVEN, GLYPH_EIGHT, GLYPH_NINE, GLYPH_ALL_ON, GLYPH_ALL_OFF, 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000, 0x10000, 0x20000, 0x40000, 0x80000, 0x100000, 0x200000, 0x0}; // ess, eee, tee);
