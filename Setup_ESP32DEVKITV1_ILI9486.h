#define TFT_PARALLEL_8_BIT
#define ILI9486_DRIVER 

// ESP32 pins used for the parallel interface TFT
   #define TFT_RST  19     // Reset pin
   #define TFT_CS   18     // Chip select control pin
   #define TFT_DC   17     // Data Command control pin - must use a pin in the range 0-31
   #define TFT_WR   16     // Write strobe control pin - must use a pin in the range 0-31
   #define TFT_RD   4
   #define TFT_D0   23     // Must use pins in the range 0-31 for the data bus
   #define TFT_D1   22     // so a single register write sets/clears all bits
   #define TFT_D2   25
   #define TFT_D3   26
   #define TFT_D4   27
   #define TFT_D5   14
   #define TFT_D6   12
   #define TFT_D7   13
   #define LOAD_GLCD      // Font 1.    Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
   #define LOAD_FONT2     // Font 2.    Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
   #define LOAD_FONT4     // Font 4.    Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
   #define LOAD_FONT6     // Font 6.    Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 
   #define LOAD_FONT7     // Font 7.    7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 
   #define LOAD_FONT8     // Font 8.    Large 75 pixel font needs ~3256 bytes in FLASH, only characters 
   #define LOAD_GFXFF     // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom 
   #define SMOOTH_FONT

   #define SPI_FREQUENCY  27000000
   #define SPI_READ_FREQUENCY  20000000
   #define SPI_TOUCH_FREQUENCY  2500000