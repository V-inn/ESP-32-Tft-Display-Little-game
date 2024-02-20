# Introduction to the project

This project revolves around the use of a 3.5 Inch ILI9486 Tft_Display i bought while i was on vacation,
so out of boredom and to practice my programming on mcu a little, i decided to try and make something
out of the display.

Firstly i bought the display because it was the cheapest at it's size, and also as it was an Arduino Uno
shield, which sounded a good idea at first, but later proved me wrong. The issue with it being an Arduino
Uno shield is that it was directly placed on top of all pins, without room to add any other features besides
the fact it was a touch screen - Which sadly i couldn't use because it arrived broken on purchase... But i got a
refund and got to keep it! - So first of all i decided to crudely make a board to attach both my an ESP32 Wroom 32
for greater processing power and memory capacity, this was done using [Bodmer's TFT_eSPI library](https://github.com/Bodmer/TFT_eSPI)
I have never soldered before, so it was kind of a shot in the dark, but surprisingly enough it worked first try
(I was very proud), i also attached 3 buttons for the sake of being able to do something.
