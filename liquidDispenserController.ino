#include <UTFT.h>
#include <URTouch.h>
#define pass  "12345"

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t GroteskBold32x64[];
extern uint8_t GroteskBold24x48[];
extern uint8_t UbuntuBold[];


UTFT myGLCD(ITDB50,38,39,40,41);
URTouch myTouch(6, 5, 4, 3, 2);

const int led = 13;
const int motor1 = 8;
const int motor2 = 9;
const int motor3 = 10;
int currentPage;
int x, y;
int numDigits;
String passcode;
bool reset;
unsigned long lastTouch;
int shotCount = 3;
int deltaT = 0;
void setup() {
  // put your setup code here, to run once:
  myGLCD.InitLCD();
  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_HI);
  pinMode(led, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  drawPasscodeScreen();
  passcode = "";
  reset = true;
  numDigits = 0;
  currentPage = 0;
  lastTouch = 0;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((millis() - lastTouch) > 60000) {
    myGLCD.clrScr();
    currentPage = 2;
  }
  
  if (currentPage == 0) {
    if (reset) {
    passcode = "";
    numDigits = 0;
    }

  
    if (myTouch.dataAvailable()) {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      lastTouch = millis();


      if((x >= 100) && (x <= 242) && (y >= 120) && (y <= 220)) {
        buttonAnimation(100, 120, 242, 220, "1", 146, 150);
        reset = false;
        passcode += "1";
        numDigits++;
        drawAst();
      }
      if((x >= 252) && (x <= 394) && (y >= 120) && (y <= 220)) {
        buttonAnimation(252, 120, 394, 220, "2", 308, 150);
        reset = false;
        passcode += "2";
        numDigits++;
        drawAst();
      }
      if((x >= 404) && (x <= 546) && (y >= 120) && (y <= 220)) {
        buttonAnimation(404, 120, 546, 220, "3", 460, 150);
        reset = false;
        passcode += "3";
        numDigits++;
        drawAst();
      }
      if((x >= 556) && (x <= 698) && (y >= 120) && (y <= 220)) {
        buttonAnimation(556, 120, 698, 220, "0", 612, 150);
        reset = false;
        passcode += "0";
        numDigits++;
        drawAst();
      }

      if((x >= 100) && (x <= 242) && (y >= 230) && (y <= 330)) {
        buttonAnimation(100, 230, 242, 330, "4", 151, 260);
        reset = false;
        passcode += "4";
        numDigits++;
        drawAst();
      }
      if((x >= 252) && (x <= 394) && (y >= 230) && (y <= 330)) {
        buttonAnimation(252, 230, 394, 330, "5", 308, 260);
        reset = false;
        passcode += "5";
        numDigits++;
        drawAst();
      }
      if((x >= 404) && (x <= 546) && (y >= 230) && (y <= 330)) {
        buttonAnimation(404, 230, 546, 330, "6", 460, 260);
        reset = false;
        passcode += "6";
        numDigits++;
        drawAst();
      }

      if((x >= 100) && (x <= 242) && (y >= 340) && (y <= 440)) {
        buttonAnimation(100, 340, 242, 440, "7", 151, 370);
        reset = false;
        passcode += "7";
        numDigits++;
        drawAst();
      }
      if((x >= 252) && (x <= 394) && (y >= 340) && (y <= 440)) {
        buttonAnimation(252, 340, 394, 440, "8", 308, 370);
        reset = false;
        passcode += "8";
        numDigits++;
        drawAst();
      }
      if((x >= 404) && (x <= 546) && (y >= 340) && (y <= 440)) {
        buttonAnimation(404, 340, 546, 440, "9", 460, 370);
        reset = false;
        passcode += "9";
        numDigits++;
        drawAst();
      }

      if((x >= 556) && (x <= 698) && (y >= 230) && (y <= 440)) {
        myGLCD.setColor(128, 0, 0);
        myGLCD.fillRoundRect(556, 230,698, 440);
        delay(300);
        myGLCD.setColor(255,0,0);
        myGLCD.fillRoundRect(556, 230,698, 440);
        myGLCD.setColor(0, 0, 0);
        myGLCD.setFont(BigFont);
        myGLCD.setBackColor(255, 0, 0);
        myGLCD.print("Enter",587, 325);
        checkPasscode();
      }

   

   
    
  
    } 
  }

  if (currentPage == 1) {
    if(myTouch.dataAvailable()) {
      myTouch.read();
      x = myTouch.getX();
      y = myTouch.getY();
      lastTouch = millis();

      if((x >= 50) && (x <= 270) && (y >= 240) && (y <= 460)) {
        fireMotor(50, 240, 270, 460, motor1, "LEFT", 113, 332);
      }
      if((x >= 290) && (x <= 510) && (y >= 240) && (y <= 460)) {
        fireMotor(290, 240, 510, 460, motor2, "CENTER", 327, 332);
      }
      if((x >= 530) && (x <= 750) && (y >= 240) && (y <= 460)) {
        fireMotor(530, 240, 750, 460, motor3, "RIGHT", 582, 332);
      }

      if ((x >= 50) && (x <= 270) && (y >= 106) && (y <= 220)) {
        shotCount = 1;
        drawButtons();
      }
      if((x >= 290) && (x <= 510) && (y >= 106) && (y <= 220)) {
        shotCount = 2;
       drawButtons();

      }
      if((x >= 530) && (x <= 750) && (y >= 106) && (y <= 220)) {
        shotCount =3;
        drawButtons();
      }
      
      
    }


    
  }

  if (currentPage == 2) {
    if(myTouch.dataAvailable()) {
      myTouch.read();
      currentPage = 0;
      lastTouch = millis();
      drawPasscodeScreen();
    }
    
  }
 

}

void drawPasscodeScreen() {
  //upper text
  myGLCD.fillScr(0, 0, 0);
  myGLCD.setFont(BigFont);
  myGLCD.setColor(255, 255, 255);
  myGLCD.print("Please Enter Passcode", CENTER, 20);

  //pads
  myGLCD.fillRoundRect(100,120,242,220);
  myGLCD.fillRoundRect(252,120,394,220);
  myGLCD.fillRoundRect(404,120,546,220);
  myGLCD.fillRoundRect(556,120,698,220);

  myGLCD.fillRoundRect(100,230,242,330);
  myGLCD.fillRoundRect(252,230,394,330);
  myGLCD.fillRoundRect(404,230,546,330);
  

  myGLCD.fillRoundRect(100,340,242,440);
  myGLCD.fillRoundRect(252,340,394,440);
  myGLCD.fillRoundRect(404,340,546,440);

  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRoundRect(556, 230,698, 440);

  
  //numbers
  myGLCD.setColor(0, 0, 0);
  myGLCD.setBackColor(255, 255, 255);
  myGLCD.setFont(SevenSegNumFont);
  
  myGLCD.print("1", 146, 150);
  myGLCD.print("2", 308, 150);
  myGLCD.print("3", 460, 150);
  myGLCD.print("0", 612, 150);

  myGLCD.print("4", 151, 260);
  myGLCD.print("5", 308, 260);
  myGLCD.print("6", 460, 260);

  myGLCD.print("7", 151, 370);
  myGLCD.print("8", 308, 370);
  myGLCD.print("9", 460, 370);

  //enter
  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(255, 0, 0);
  myGLCD.print("Enter",587, 325);
 
 //lower text
 myGLCD.setBackColor(0, 0, 0);
 myGLCD.setColor(255, 255, 255);
 myGLCD.print("See Kyle Wengryn or Mason Favro for code", CENTER, 460);

 


}


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



void drawAst() {
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.setFont(BigFont);

  if (numDigits == 1) {
    myGLCD.print("*", CENTER, 65);
  }
  if (numDigits == 2) {
    myGLCD.print("*  *", CENTER, 65);
  }
  if (numDigits == 3) {
    myGLCD.print("*  *  *", CENTER, 65);
  }
  if (numDigits == 4) {
    myGLCD.print("*  *  *  *", CENTER, 65);
  }
  if (numDigits == 5) {
    myGLCD.print("*  *  *  *  *", CENTER, 65);
  }
  

}

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
    myGLCD.setFont(BigFont);
    
      myGLCD.setBackColor(255, 0, 0);
      myGLCD.setColor(0, 0, 0);
      myGLCD.print("                                       ", CENTER, 49);
      myGLCD.print("                                       ", CENTER, 65);
      myGLCD.print("                                       ", CENTER, 81);
      myGLCD.print("-Access Denied-", CENTER, 65);
      delay(1000);
      myGLCD.setBackColor(0, 0, 0);
      myGLCD.print("                                       ", CENTER, 49);
      myGLCD.print("                                       ", CENTER, 65);
      myGLCD.print("                                       ", CENTER, 81);
      reset = true;
    
  }


}

void drawHomeScreen() {
  myGLCD.clrScr();
  drawDirections();

  myGLCD.setColor(220, 220, 220);
  myGLCD.fillRoundRect(50, 240, 270, 460);
  myGLCD.fillRoundRect(290, 240, 510, 460);
  myGLCD.fillRoundRect(530, 240, 750, 460);

  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(50, 240, 270, 460);
  myGLCD.drawRoundRect(290, 240, 510, 460);
  myGLCD.drawRoundRect(530, 240, 750, 460);

  myGLCD.setFont(GroteskBold24x48);
  myGLCD.setColor(0, 0, 0);
  myGLCD.print("LEFT", 113, 332);
  myGLCD.print("CENTER", 327, 332);
  myGLCD.print("RIGHT", 582, 332);

  drawButtons(); 


  

  
  
 
}

void fireMotor(int x1, int y1, int x2, int y2, int motor, String label,int x3,int y3) {
  if (shotCount == 1) {
    deltaT = 2500;
  }
  if (shotCount == 2) {
    deltaT = 4700;
  }
  
  if (shotCount == 3) {
    while(myTouch.dataAvailable()) {
      myTouch.read();
      digitalWrite(motor, HIGH);
      myGLCD.setColor(140, 140, 140);
      myGLCD.fillRoundRect(x1, y1, x2, y2);
    }
  } else {
    unsigned long currTime = millis();
    while(millis() - currTime < deltaT) {
      digitalWrite(motor, HIGH);
      myGLCD.setColor(140, 140, 140);
      myGLCD.fillRoundRect(x1, y1, x2, y2);
    }
  }

    digitalWrite(motor, LOW);
    myGLCD.setColor(220, 220, 220);
    myGLCD.fillRoundRect(x1, y1, x2, y2);
    myGLCD.setColor(0, 0, 0);
    myGLCD.drawRoundRect(x1, y1, x2, y2);
    myGLCD.setFont(GroteskBold24x48);
    myGLCD.print(label, x3, y3);

  
}

void drawDirections() {

myGLCD.setFont(UbuntuBold);
  myGLCD.setBackColor(VGA_TRANSPARENT);
  myGLCD.setColor(115, 194, 251);
  myGLCD.fillRoundRect(50, 20, 750, 86);
  myGLCD.setColor(0, 0, 0);
  
  if (shotCount == 3) { 
   myGLCD.print("Press and hold to pour", CENTER, 40);
  } else {
   myGLCD.print("Tap to pour", CENTER, 40);
  }
  
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(50, 20, 750, 86);

}

void drawButtons() {
  drawDirections();
  if (shotCount == 1) {
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRoundRect(50, 106, 270, 220);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(290, 106, 510, 220);
  myGLCD.fillRoundRect(530, 106, 750, 220);
 
 
  } else if (shotCount == 2) {
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(50, 106, 270, 220);
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRoundRect(290, 106, 510, 220);
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(530, 106, 750, 220);
 
 
  } else {
  myGLCD.setColor(255, 255, 255);
  myGLCD.fillRoundRect(50, 106, 270, 220);
  myGLCD.fillRoundRect(290, 106, 510, 220);
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRoundRect(530, 106, 750, 220);
  }

  myGLCD.setFont(BigFont);
  myGLCD.setColor(0, 0 ,0);
  myGLCD.print("1 second", 112, 155);
  myGLCD.print("2 seconds",344 , 155);
  myGLCD.print("manual",600, 155);

}
