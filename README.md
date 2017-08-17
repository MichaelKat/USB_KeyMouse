# USB_KeyMouse
Emulates USB Mouse and Mini Keyboard using Arduino.

This code allows an Arduino Leonardo, Micro, or Pro Micro to emulate a USB Mouse or Mini Keyboard using 7 buttons.
Perfect for navigating through media playing systems on devices with USB ports (i.e. Kodi on a Raspberry Pi 3).
   
Author: Michael Katilevsky

10 August 2017


Setup Information:
  
Arduino Pins:      Keyboard Function:    Mouse Function:               Other Function:
     2         =     Esc Key               Scroll Wheel Button           Change from Keyboard to Mouse and vice-versa when pressed for a second or more
     3         =     Left Arrow            Mouse movement to the left
     4         =     Spacebar              Right Button
     5         =     Up Arrow              Mouse movement upwards
     6         =     Enter                 Left Button
     7         =     Down Arrow            Mouse movement downwards
     8         =     Right Arrow           Mouse movement to the right


Possible Setup (button positioning and corresponding Arduino pins):

[2] [5]
[3] [6] [8]
[4] [7]
