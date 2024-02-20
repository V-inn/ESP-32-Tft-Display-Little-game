

// TFT_eSPI library:
// https://github.com/Bodmer/TFT_eSPI

//Huge thanks to Bodmer for TFT_eSPI and TJpg_Decoder libraries

//----------------------------------------------------------------------------------------------------

#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

// JPEG decoder library
#include <TJpg_Decoder.h>

//AdvTone for buzzer volume control

#include <AdvTone.h>

// Includes the sketch header file that contains the image stored as an array of bytes
// More than one image array could be stored in each header file.

#include "Tiles.h"
#include "PlayerSprites.h"
#include "PossibleMaps.h"

const byte Button1 = 34;
const byte Button2 = 35;
const byte Button3 = 32;
const byte BuzzerPin = 2;

AdvTone buzzer = AdvTone(BuzzerPin, 0);



//----------------------------------------------------------------------------------------------------
// Player and map

  const int baseTileSize = 40;

  //Width and height are swapped due to landscape orientation not being default;
  const int tftHeight = tft.width();
  const int tftWidth = tft.height();

  int currentMap = 0;

  byte playerPositionXY[2] = {0,0};

  const uint8_t *playerSprites[] = {PlayerUp, PlayerRight, PlayerDown, PlayerLeft};

  const int playerSpriteSizes[4] = {
    sizeof(PlayerUp),
    sizeof(PlayerRight),
    sizeof(PlayerDown),
    sizeof(PlayerLeft)
  };

  byte lookDirection, lastDirection = 0; //0 Up, 1 Right, 2 Down, 3 Left
  bool selectButtonPress, tempButtonState = false;

  void renderMap(){
    Serial.println(tftHeight);
    Serial.println(tftWidth);
    for(int i = 0; i < tftHeight; i += baseTileSize){
      for(int j = 0; j < tftWidth; j += baseTileSize){
        if(maps[currentMap][i/baseTileSize][j/baseTileSize] == 0){
          Serial.println("I: " + String(i) + " | J: " + String(j));
          TJpgDec.drawJpg(j, i, GroundTile, sizeof(GroundTile));
        }else{
          // TJpgDec.drawJpg(j, i, WallTile, sizeof(Walltile));
        }
      }
    }
  }

  void renderPlayer(byte direction, byte currentXY[2]){
    int X = currentXY[0]*baseTileSize;
    int Y = currentXY[1]*baseTileSize;

    TJpgDec.drawJpg(X, Y, playerSprites[direction], playerSpriteSizes[direction]);
  }

  void movePlayer(byte direction, byte currentXY[2]){
    int X = currentXY[0]*baseTileSize;
    int Y = currentXY[1]*baseTileSize;

    byte XY = (direction + 1) % 2;

    Serial.println("currentXY[" + String(XY) + "] | Direction: " + String(direction));

    if(direction == 0){
      if(currentXY[XY] == 0){
        return;
      }else{
        TJpgDec.drawJpg(X, Y, GroundTile, sizeof(GroundTile));
        currentXY[XY] -= 1;
        renderPlayer(direction, currentXY);
      }
    }else if(direction == 1){
      if(currentXY[XY] == 11){
        return;
      }else{
        TJpgDec.drawJpg(X, Y, GroundTile, sizeof(GroundTile));
        currentXY[XY] += 1;
        renderPlayer(direction, currentXY);
      }
    }else if(direction == 2){
      if(currentXY[XY] == 7){
        return;
      }else{
        TJpgDec.drawJpg(X, Y, GroundTile, sizeof(GroundTile));
        currentXY[XY] += 1;
        renderPlayer(direction, currentXY);
      }
    }else if(direction == 3){
      if(currentXY[XY] == 0){
        return;
      }else{
        TJpgDec.drawJpg(X, Y, GroundTile, sizeof(GroundTile));
        currentXY[XY] -= 1;
        renderPlayer(direction, currentXY);
      }
    }
  }

//----------------------------------------------------------------------------------------------------

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap){
   // Stop further decoding as image is running off bottom of screen
  if ( y >= tft.height() ) return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
  tft.pushImage(x, y, w, h, bitmap);

  // This might work instead if you adapt the sketch to use the Adafruit_GFX library
  // tft.drawRGBBitmap(x, y, bitmap, w, h);

  // Return 1 to decode next block
  return 1;
}

//----------------------------------------------------------------------------------------------------
// Button Handling Functions
  bool debounce(unsigned long& lastTime, unsigned long time){
    uint8_t threshold = 70;

    if(time - lastTime >= threshold){
      lastTime = time;
      return true;
    }else{
      return false;
    }
  }

  void buttonOnHold(byte Button){
    bool buttonState = digitalRead(Button);
    while(buttonState){
      buttonState = digitalRead(Button);
      delay(1);
    }
  }

  void buttonCheck(void* parameters){
    unsigned long lastExecute = millis();
    unsigned long currentExecute = millis();

    while(1){
      currentExecute = millis();

      if(debounce(lastExecute, currentExecute)){
        if(digitalRead(Button1) == HIGH){
          runOnButtonPress(Button1);
        }else if(digitalRead(Button2) == HIGH){
          runOnButtonPress(Button2);
        }else if(digitalRead(Button3) == HIGH){
          runOnButtonPress(Button3);
        }
      }
    }
  }

  void runOnButtonPress(byte Button){
    if(Button == Button1){

      if(lookDirection > 0){
        lookDirection -= 1;
      }else{
        lookDirection = 3;
      }

    }else if(Button == Button2){

      if(lookDirection < 3){
        lookDirection += 1;
      }else{
        lookDirection = 0;
      }

    }else if(Button == Button3){
      selectButtonPress = true;
    }

    buttonOnHold(Button);

    selectButtonPress = false;
  }

  bool hasButtonStateChanged(){
    if(selectButtonPress == false){
      tempButtonState = false;
    }

    if(lookDirection != lastDirection){
      lastDirection = lookDirection;
      return true;

    }else if(selectButtonPress == true && selectButtonPress != tempButtonState){
      tempButtonState = true;
      return true;

    }else{
      return false;
    }
  }

//####################################################################################################
// Setup
//####################################################################################################
void setup() {
  Serial.begin(115200);

  //----------------------------------------------------------------------------------------------------
  //Initialize Display
  tft.begin();
  tft.setRotation(1);  // Landscape
  tft.fillScreen(TFT_BLACK);

  pinMode(Button1, INPUT);
  pinMode(Button2, INPUT);
  pinMode(Button3, INPUT);

  //----------------------------------------------------------------------------------------------------

  // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
  TJpgDec.setJpgScale(1);

  // The byte order can be swapped (set true for TFT_eSPI)
  TJpgDec.setSwapBytes(true);

  // The decoder must be given the exact name of the rendering function above
  TJpgDec.setCallback(tft_output);
  //----------------------------------------------------------------------------------------------------

  delay(200);

  renderMap();

  byte temp[2] = {0,0};
  renderPlayer(lookDirection, temp);

  //----------------------------------------------------------------------------------------------------

  // Draw the image, top left at 0,0
  //TJpgDec.drawJpg(0, 0, Background1, sizeof(Background1));

  tft.setTextFont(2);
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(40, 240);
  tft.print("Test123456");

  xTaskCreatePinnedToCore(buttonCheck, "buttonCheck", 1000, NULL, 0, NULL, 0);

  while(!hasButtonStateChanged()){delay(1);}
}

// Main loop
//####################################################################################################
void loop() {
  if(hasButtonStateChanged()){
    if(selectButtonPress == true){
      movePlayer(lookDirection, playerPositionXY);
    }else{
      renderPlayer(lookDirection, playerPositionXY);
    }

    buzzer.tone(1000, 20, 100);
  }
}

//----------------------------------------------------------------------------------------------------
