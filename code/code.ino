#include <SoftwareSerial.h>
#include "LED.h"
String red = "", green = "", blue = "";
SoftwareSerial blt(8,7);

LED Red(6);
LED Green(9);
LED Blue(10);

void setup()
{ 
    blt.begin(9600);
    Serial.begin(115200);
    pinMode(IND, OUTPUT);
    
    Red.setTime(5000,5000);
    Green.setTime(5000,5000);
    Blue.setTime(5000,5000);
    
    // Red.pulse(true);
    // Red.watchExternalLight(true,127);
    // Red.routeBass(true);
    Red.routeUser(true);
    // Red.setUserBrightness(255);
    // Serial.println(Red.getActiveChannels());
    
    // Green.pulse(true);
    // Green.watchExternalLight(true,200);
    // Green.routeMid(true);
    Green.routeUser(true);
    // Green.setUserBrightness(255);
    // Serial.println(Green.getActiveChannels());
    
    // Blue.pulse(true);
    // Blue.watchExternalLight(true,127);
    // Blue.routeTreble(true);
    Blue.routeUser(true);
    // Blue.setUserBrightness(255);
    // Serial.println(Blue.getActiveChannels());
    
}

String rxBuff;

void loop()
{
    /*
    if((1<<3) & redControl)
    red.setBrightness(X)
    if((1<<6) & redControl || (1<<5) & redControl)
    red.update();
    */
    Red.update();
    Green.update();
    Blue.update();
    int i;
    String rx = "", red = "", green = "", blue = "";
    while(blt.available())
    {
        char c = blt.read();
        /*Serial.print(c);
        Serial.print("\t");
        Serial.print(char(c));
        Serial.print("\t");
        Serial.println(uint8_t(c));*/
        rx += c;
        delay(2);
    }
    if(rx != "")
    {
        Serial.println(rx);
        uint8_t n = rx.length();
        for(uint8_t i = 0; i < n; i++)
        {
            if(rx.charAt(i) == 'R')
            {
                for(uint8_t j = i+1; j < n; j++)
                {
                    if(isDigit(rx.charAt(j)))
                        red += rx.charAt(j);
                    else
                        break;
                }
            }
            else if(rx.charAt(i) == 'G')
            {
                for(uint8_t j = i+1; j < n; j++)
                {
                    if(isDigit(rx.charAt(j)))
                        green += rx.charAt(j);
                    else
                        break;
                }
            }
            else if(rx.charAt(i) == 'B')
            {
                for(uint8_t j = i+1; j < n; j++)
                {
                    if(isDigit(rx.charAt(j)))
                        blue += rx.charAt(j);
                    else
                        break;
                }
            }
        }
        n = rx.indexOf('~');
        if(rx.charAt(n+1) == 'F')
            Red.flash(true);
        else if(rx.charAt(n+1) == 'P')
            Red.pulse(true);
        else
        {
            Red.flash(false);
            Red.pulse(false);
        }
        if(rx.charAt(n+2) == 'F')
            Green.flash(true);
        else if(rx.charAt(n+2) == 'P')
            Green.pulse(true);
        else
        {
            Green.flash(false);
            Green.pulse(false);
        }
        if(rx.charAt(n+3) == 'F')
            Blue.flash(true);
        else if(rx.charAt(n+3) == 'P')
            Blue.pulse(true);
        else
        {
            Blue.flash(false);
            Blue.pulse(false);
        }
        Serial.print(red);
        Serial.print("\t");
        Serial.print(green);
        Serial.print("\t");
        Serial.println(blue);
        if(!red.toInt())
            Red.routeUser(false);
        else
        {
            Red.routeUser(true);
            Red.setUserBrightness(red.toInt());
        }
        if(!green.toInt())
            Green.routeUser(false);
        else
        {
            Green.routeUser(true);
            Green.setUserBrightness(green.toInt());
        }
        if(!blue.toInt())
            Blue.routeUser(false);
        else
        {
            Blue.routeUser(true);
            Blue.setUserBrightness(blue.toInt());
        }
        blt.write("#1~");
    }

    /*
    if(rx.length() == 1)
    rxBuff = rx;
    if(rx != "")
    {
        rx = rxBuff + rx;
        //Serial.print("Raw:");
        //Serial.println(rx);
        for(i = rx.length() - 2; i >= 0; i--)
        {
            char c = rx.charAt(i);
            if(c == ')')
            {
                rx = rx.substring(i+1,(rx.length() - 1));
                break;
                //Serial.println(rx);
            }
        }
        Serial.println(rx);
        getVars(rx);
        redControl = rx[0];
        greenControl = rx[1];
        blueControl = rx[2];
        redControl = rx[3];
        greenControl = rx[4];
        blueControl = rx[5];
    }*/
}

void getVars(String rx)
{
  // Assume we got 3 bytes here, each for red, green and blue
  // B M T uint8_t
  /*
  Incoming Message: 6 bytes
  
      #X.X.X.R.G.B~
  
  X = Status Byte of respective colour
  */
  Serial.println("Updating...");
  String findRed = "" , findGreen = "" , findBlue = "";
  boolean fred = false, fgreen = false, fblue = false;
  char c;
  uint8_t length = rx.length();
  for(int i = 0; i < length; i++)
  {
    c = rx.charAt(i);
    if(isDigit(c) && !fred)
    {
        findRed += c;
        continue;
    }
    else if(!fred)
    {
        fred = true;
        continue;
    }
    if(isDigit(c) && !fgreen)
    {
        findGreen += c;
        continue;
    }
    else if(!fgreen)
    {
        fgreen = true;
        continue;
    }
    if(isDigit(c) && !fblue)
    {
        findBlue += c;
        continue;
    }
    else if (!fblue)
    {
        fblue = true;
        continue;
    }
    }
    //Serial.println(findRed);
    //Serial.println(findGreen);
    //Serial.println(findBlue);
    //red = findRed.toInt();
    //green = findGreen.toInt();
    //blue = findBlue.toInt();
}