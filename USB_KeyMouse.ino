// **********************************************************
//   USBController.ino
//
//   This code allows an Arduino Leonardo, Micro, or Pro Micro to emulate a USB Mouse or Mini Keyboard using 7 buttons.
//   Perfect for navigating through media playing systems on devices with USB ports (i.e. Kodi on a Raspberry Pi 3).
//   
//   Author: Michael Katilevsky
//
//   10 August 2017
//
//
//   Setup Information:
//   
//   Arduino Pins:      Keyboard Function:    Mouse Function:               Other Function:
//        2         =     Esc Key               Scroll Wheel Button           Change from Keyboard to Mouse and vice-versa when pressed for a second or more
//        3         =     Left Arrow            Mouse movement to the left
//        4         =     Spacebar              Right Button
//        5         =     Up Arrow              Mouse movement upwards
//        6         =     Enter                 Left Button
//        7         =     Down Arrow            Mouse movement downwards
//        8         =     Right Arrow           Mouse movement to the right
//
//
//    Possible Setup (button positioning and corresponding Arduino pins):
//
//    [2] [5]
//    [3] [6] [8]
//    [4] [7]
//
// **********************************************************



#include <Mouse.h>

#include <Keyboard.h>


byte keys[] = {177, 216, 32, 218, 176, 217, 215};   // Decimal values sent by the Arduino board to emulate keys. Full reference: https://www.arduino.cc/en/Reference/KeyboardModifiers
                                                    // 177 = Esc,  216 = Left Arrow,  32 = Spacebar,  218 = Up Arrow,  176 = Enter,  217 = Down Arrow,  215 = Right Arrow

int mouseX[] = {-1, 0, 0, 0, 0, 1};   // X-axis displacement per button press

int mouseY[] = {0, 0, -1, 0, 1, 0};   // Y-axis displacement per button press

boolean isKeyboard;  // Allows the device to emulate a keyboard or a mouse interchangeably

boolean middleMouse; // is true when the "scroll" button is clicked, false when clicked again

int startChangeTime;

int endChangeTime;


void setup() {
  // put your setup code here, to run once:
  
  isKeyboard = true;
  
  for(int a = 2; a < 9; a++)   // Sets pins 2 through 8 included as inputs to read the 7 buttons' states (active LOW)
  {
    pinMode(a, INPUT_PULLUP);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  Keyboard.begin();  // Starts emulating a keyboard

  delay(1000);

  // Checks that no button is pressed before proceeding:
  while(digitalRead(2) == LOW || digitalRead(3) == LOW || digitalRead(4) == LOW || digitalRead(5) == LOW || digitalRead(6) == LOW || digitalRead(7) == LOW || digitalRead(8) == LOW);

  while(isKeyboard)
  {
    for(int a = 2; a < 9; a++)
    {
     if(digitalRead(a) == LOW)
     {
      if(a == 2)  // Esc is pressed and held
      {
        startChangeTime = millis();  // Registers time at which Esc was pressed
        
        while(digitalRead(a) == LOW)
        {
          endChangeTime = millis();  // // Registers time at which Esc was released
        }

        if(endChangeTime - startChangeTime >= 1000)  
        {
          isKeyboard = false;  // If Esc was held for a second or more, the device starts emulating a mouse instead
        }

        else
        {
          Keyboard.write(keys[a-2]); // Sends the Esc decimal value if Esc was pressed for less than a second
        }
      }

      else
      {
        Keyboard.write(keys[a-2]);  // Sends the decimal value of the corresponding pressed button
      }
      
      delay(210);
     }
    }
  }


 
  middleMouse = false;

  Mouse.begin();  // Starts emulating a mouse

  delay(1000);

  // Checks that no button is pressed before proceeding:
  while(digitalRead(2) == LOW || digitalRead(3) == LOW || digitalRead(4) == LOW || digitalRead(5) == LOW || digitalRead(6) == LOW || digitalRead(7) == LOW || digitalRead(8) == LOW);

  while(!isKeyboard)
  {
    for(int a = 2; a < 9; a++)
    {
     if(digitalRead(a) == LOW)
     {
      if(a == 4)
      {
         Mouse.click(MOUSE_RIGHT);  // Right click
         delay(210);
      }

      else if(a==6)
      {
        Mouse.click();  // Left click
        delay(210);
      }
      
      else if(a == 2)  // Scroll Wheel is pressed and held
      {
        startChangeTime = millis();  // Registers time at which the wheel was pressed
        
        while(digitalRead(a) == LOW)
        {
          endChangeTime = millis();  // Registers time at which the wheel was released
        }

        if(endChangeTime - startChangeTime >= 1000)
        {
          isKeyboard = true;   // If the wheel was held for a second or more, the device starts emulating a keyboard instead
        }

        else
        {
          if(!middleMouse)
          {
            Mouse.press(MOUSE_MIDDLE);  // If the wheel was pressed for less than a second, it toggles automatic / smooth scrolling on
          }

          else
          {
            Mouse.release(MOUSE_MIDDLE);  // If the wheel was pressed for less than a second, it toggles automatic / smooth scrolling off
          }
        }
        
        delay(210);
      }

      else
      {
        Mouse.move(mouseX[a-3], mouseY[a-3]);  // Smoothly moves the mouse on-screen with small, frequent steps; allows maximum precision.
      }
      
     }
    }
  }
 
}




