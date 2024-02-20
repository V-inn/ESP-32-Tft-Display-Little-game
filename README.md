# A bit about the project

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

![IMG_20240220_142714](https://github.com/V-inn/ESP-32-Tft-Display-Little-game/assets/93566073/86f6e8c2-d8f4-443a-887e-a051fab0dbe4)

Luckily I made the TFT screen detachable because, for some reason i was running into issues when uploading code
to the esp32 whilst it was connected, but solved after removing and attaching it later.

Along with that, I've also soldered the esp32 facing the opposite direction I originally planned by accident, which
did end up making things a bit messier and harder.

Another issue i ran into was the unnability to just attach the top female pin headers directly to the fenolite board, due
to the very awkward spacing of the TFT shield being offset my a milimiter on one of it's pin headers.

![LittleGame top view image](https://github.com/V-inn/ESP-32-Tft-Display-Little-game/assets/93566073/b934b822-6729-4dc6-8378-1e0d292ed957)

![LittleGame bottom view image](https://github.com/V-inn/ESP-32-Tft-Display-Little-game/assets/93566073/a7543934-ba2f-4079-a1f7-6cdeae39ad69)

As off now, I haven't written a lot of code regarding the actual game other than a very crude movement system, not only because i'm completely
out of ideas, but also because my vacation is over, so now I've got school, work and also my scholarship which leaves me with pretty much no time.

![LittleGameplay](https://github.com/V-inn/ESP-32-Tft-Display-Little-game/assets/93566073/70871734-aa48-4f06-9b2c-47f2a7728c9a)


### But a huge thanks from me for checking out my project!
