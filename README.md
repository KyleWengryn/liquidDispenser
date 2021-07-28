# Table of contents
1. [Background](#introduction)
2. [Hardware](#Hardware)
3. [Software](#Software)

# Background <a name="introduction"></a>
<img src="/images/IMG_4447.jpg" alt="tap" width="200"/>

This is a personal project I designed and created in the beginning of 2020. It is an arduino powered dispenser with an LCD touch screen and three different tanks. It is powered via a converted 9v power supply from a traditional wall outlet in the United States. Three separate relay switches are connected to a separate 9v power source and are controlled through the arduino outputs. The relays are then connected to three liquid pumps respectively that drive the flow of liquid from the tanks to the spouts. All hardware and plumbing can be found online and are relatively inexpensive. 

# Hardware <a name="Hardware"></a>
### Arduino Mega
<img src="https://m.media-amazon.com/images/I/61n4c0x7zIL._AC_SL1000_.jpg" alt="drawing" width="200"/>

[Arduino Mega 2560 REV3](https://www.amazon.com/ARDUINO-MEGA-2560-REV3-A000067/dp/B0046AMGW0/ref=sr_1_1_sspa?dchild=1&keywords=arduino+mega&qid=1627484898&sr=8-1-spons&psc=1&smid=AA57DDZKZUZDL&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExNTNURFFKVTJFNTAmZW5jcnlwdGVkSWQ9QTA0NTgzMTExTlJIV0E3R0ZXSlA2JmVuY3J5cHRlZEFkSWQ9QTEwMDkxNTIzRUY2OTJKVzY4WVpWJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==)

This device was chosen due to the ample amount of inputs and outputs as the LCD screen takes up a significant portion of the board. It is also easily able to obtain on amazon as indicated by the link above.

### 5 inch LCD Touch Screen + Expansion Shield
This product was chosen due to its size and compatability with the arduino mega board. It is not too overpowered and the resolution is just enough for its purpose.

<img src="https://ae01.alicdn.com/kf/HTB1pX_xd8Kw3KVjSZFOq6yrDVXaZ/diymore-5-0-5-0-inch-TFT-LCD-Display-Module-SSD1963-with-Touch-Panel-SD-Card.jpg_q50.jpg" alt="tap" width="200"/>

[5 Inch LCD Touch Screen](https://www.aliexpress.com/i/33045125561.html)

In order for the LCD screen to work with arduino, it needs a shield expansion board to be placed directly in between the screen and the arduino itself. The purpose of the board is to streamline connections which also reduces the chance of shorting the screen due to poor connections.

<img src="https://m.media-amazon.com/images/I/61I02Qi7feL._AC_SL1024_.jpg" alt="drawing" width="200"/>

[Shield Expansion Board](https://www.amazon.com/gp/product/B01MRQ2G8R/ref=ppx_yo_dt_b_asin_title_o03_s01?ie=UTF8&psc=1)

### Relay Switches
These are basic relay switches which have power and signal inputs that are used to control the motors. When the signal line is turned on, the respective motor is turned on.

<img src="https://m.media-amazon.com/images/I/71aGbUlrehL._AC_SL1001_.jpg" alt="drawing" width="200"/>

[Relay Switches](https://www.amazon.com/gp/product/B079FJSYGY/ref=ppx_yo_dt_b_asin_title_o03_s02?ie=UTF8&psc=1)

### Pumps
The pumps used in the design are technical air pumps. When turned on, it pushes air into the tank which moves the liquid out another hose and through the spout. This design was chosen due to its simplicity and low cost.

<img src="https://m.media-amazon.com/images/I/61zt7u5kzDL._AC_SL1500_.jpg" alt="drawing" width="200"/>

[Pumps](https://www.amazon.com/gp/product/B07JZ6H4FY/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1)

### Power Supply Materials
Simple 9v converter for arduino

<img src="https://m.media-amazon.com/images/I/31cMIPPiSpL._AC_.jpg" alt="drawing" width="200"/>

[9v Power Converter](https://www.amazon.com/gp/product/B018OLREG4/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)

A 9v battery connecting wires to power relay switches

<img src="https://m.media-amazon.com/images/I/61BCAptAOdL._AC_SL1500_.jpg" alt="drawing" width="200"/>

[9v Battery Adaptor](https://www.amazon.com/gp/product/B018OLREG4/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)



# Software <a name="Software"></a>
The code was written in Arduino's custom IDE and compiler. It can be downloaded at the link below
[Arduino IDE](https://www.arduino.cc/en/software)

### Setting up the Touch LCD Screen
There are two header files needed to be able to use both the screen and its touch capabilities. Documentation for the UTFT and URTouch librariers are included in repository folders for each one.

```c++
#include <UTFT.h>
#include <URTouch.h>
```

Next, the hardware needs to be initialized. The pins listed are the pins that align with the expansion shield connections as stated in the hardware section

```c++
UTFT myGLCD(ITDB50,38,39,40,41);
URTouch myTouch(6, 5, 4, 3, 2);
myGLCD.InitLCD();
myTouch.InitTouch(LANDSCAPE);
myTouch.setPrecision(PREC_HI);
```

Retrieving touch information. Data comes in the form of x and y coordinates. These coordinates can then be checked to see if they overlap with the location of a 'button' on the screen.

```c++
if (myTouch.dataAvailable()) {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      lastTouch = millis();
}
```

Drawing a button on the screen. It is essentially just a rectangle on the screen with coordinates that can be compared to touch coordinates

```c++
myGLCD.setColor(255, 0, 0);
myGLCD.fillRoundRect(100,120,242,220);
```

Simply touching the button and seeing results does not feel naturual. I added a simple button animation so the user can easily confirm if a touch was registered

```c++
void buttonAnimation(int x1, int y1,int x2,int y2, String num,int x3, int y3) {
        myGLCD.setColor(169, 169, 169);
        myGLCD.fillRoundRect(x1,y1,x2,y2);
        delay(300);
        myGLCD.setColor(255, 255, 255);
        myGLCD.fillRoundRect(x1,y1,x2,y2);

        myGLCD.setColor(0, 0, 0);
        myGLCD.setBackColor(255, 255, 255);
        myGLCD.setFont(SevenSegNumFont);
  
        myGLCD.print(num, x3, y3);
}
```

### Setting up Relay Switches
The relays take in a digital ouput which determines when to send power to the motor. I first initialized constant values for the pins and then set the pin mode.

```c++
const int motor1 = 8;
const int motor2 = 9;
const int motor3 = 10;

pinMode(motor1, OUTPUT);
pinMode(motor2, OUTPUT);
pinMode(motor3, OUTPUT);
```

### Firing the Motors
Sending a HIGH ouput to the relay will turn the motor on. Below is an example of a pour determined by pressing and holding the button. The digitalWrite() function is used to send a HIGH signal to the relay.

```c++
while(myTouch.dataAvailable()) {
      myTouch.read();
      digitalWrite(motor, HIGH);
      myGLCD.setColor(140, 140, 140);
      myGLCD.fillRoundRect(x1, y1, x2, y2);
    }
digitalWrite(motor, LOW);
```

### Bonus Feature: Including Passcode
The first menu that appears when powering on the device is a passcode screen. Each number has specific coordinates and a passcode string is concatenated for each press.

```c++
if((x >= 100) && (x <= 242) && (y >= 120) && (y <= 220)) {
        buttonAnimation(100, 120, 242, 220, "1", 146, 150);
        reset = false;
        passcode += "1";
        numDigits++;
        drawAst();
      }
```

When the user hits "enter" the passcode is then checked with the passcode initialized in the global variables and access is either granted or denied with a couple of animations

```c++
void checkPasscode() {
  if (passcode.length() == 5 && passcode == pass) {
     myGLCD.setFont(BigFont);
     myGLCD.setColor(255, 255, 255);
     myGLCD.setBackColor(0, 150, 51);
     myGLCD.print("                                       ", CENTER, 49);
     myGLCD.print("                                       ", CENTER, 65);
     myGLCD.print("                                       ", CENTER, 81);
     myGLCD.print("-Access Granted-", CENTER, 65);
     delay(1000);
     currentPage = 1;
     drawHomeScreen();
  } else {
```

### Bonus Feature: Screen timer
Every time the screen is touched, the time of the touch is recorded.

```c++
lastTouch = millis();
```
At the beginning of the infinite loop, the time of last touch is compared to 60 seconds. If no one has touched it within 60 seconds, then the screen shuts off until it is tapped again.

```c+=
if ((millis() - lastTouch) > 60000) {
    myGLCD.clrScr();
    currentPage = 2;
  }
```






