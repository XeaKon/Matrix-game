#include "LedControl.h" //  need the library
#include <LiquidCrystal.h>
#include <EEPROM.h>
LedControl lc = LedControl(12, 11, 10, 1); //DIN, CLK, LOAD, No. DRIVER
 
// pin 12 is connected to the MAX7219 pin 1
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219


const int axis=A0;
const int ayis=A1;
const int sw=A2;

const int d4=5;//lcd
const int d5=4;
const int d6=3;
const int d7=2;
const int rs=7;
const int enable=6;
LiquidCrystal lcd(rs,enable,d4,d5,d6,d7);


int xVal=0;
int yVal=0;
int swVal=0;
int xchanged=0;
int ychanged=0;
int count=0;
const int ssize=8;
int left=-3;//limita ofsetului la stanga, pt mijloc
int right=2;//limita ofsetului la dreapta


int swState=0;
int lastswState=0;
unsigned int lastDebounceTime=0;
unsigned int debounceDelay=50;
int ok=0;


int k=0;
int poset=0;//ofsetul pt masina
int past=0;
int present=0;
int track=0;//ofsetul pt peretii traseului
int i=0;
int j=0;
int er=0;
int interval=350;
int noOfTrack=1;
int highscore=0;
int pnoOfTrack=1;
int hs=0;
 
void setup()
{
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 2); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  pinMode(sw,INPUT_PULLUP);
  lcd.begin(16,2);
  Serial.begin(9600);
  
}
void loop()
{
//  for (int row = 0; row < 8; row++)
//  {
//  for (int col = 0; col < 8; col++)
//  {
//    lc.setLed(0, col, row, true); // turns on LED at col, row
//    delay(25);
//  }
//  }
//  for (int row = 0; row < 8; row++)
//  {
//  for (int col = 0; col < 8; col++)
//  {
//    lc.setLed(0, col, row, false); // turns off LED at col, row
//    delay(25);
//  }
//  }


xVal=analogRead(axis);
yVal=analogRead(ayis);     //1024-analogRead(ayis);
swVal=digitalRead(sw);

//if(er==0)
{
if(yVal<300&&ychanged==0)
{
   count--;
   poset=1;
   if(count<left)
    {
      count=left; poset=0;
    }
     ychanged=1;
}
else
{
  if(yVal>700&&ychanged==0)
  {
    count++;
    poset=-1;
    if(count>right)
  {
     count=right; poset=0;}
     ychanged=1;
  }
  else
  {
    if(yVal>=300&&yVal<=700)
   ychanged=0; 
  }
}


if(er==0)
{
  if(ychanged==1&&poset!=0)
   {
    lc.setLed(0, 3+count+poset, 7, false);//stingera ledurilor anterioare
    lc.setLed(0, 4+count+poset, 7, false);
    lc.setLed(0, 5+count+poset, 7, false);
    lc.setLed(0, 4+count+poset, 6, false);
    lc.setLed(0, 4+count+poset, 5, false);
    lc.setLed(0, 3+count+poset, 5, false);
    lc.setLed(0, 5+count+poset, 5, false);
    lc.setLed(0, 4+count+poset, 4, false);
   }



lc.setLed(0, 3+count, 7, true);//masina
lc.setLed(0, 4+count, 7, true);
lc.setLed(0, 5+count, 7, true);
lc.setLed(0, 4+count, 6, true);
lc.setLed(0, 4+count, 5, true);
lc.setLed(0, 3+count, 5, true);
lc.setLed(0, 5+count, 5, true);
lc.setLed(0, 4+count, 4, true);

}

  if(er==0)
  {
   switch(noOfTrack)//forma traseului ,track inca nu are utilitate
   {

   case 0:   
//    for(int i=0;i<8;i++)
//{
//  lc.setLed(0, 0, i, true);
//  lc.setLed(0, 7, i, true);
//  //lc.setLed(0, 1, i, true);
//  
//  }

  
if(millis()-past>=interval&&i<8)
  {
   lc.setLed(0, 2, i, true);//2 la stanga
   lc.setLed(0, 1, i, true);
   highscore++;
  if(i==4&&count>-1)
  {
    left+=3;

  }
  else
  {
    if(i==4&&(count<=-1))
    er=1;
  }
  
  past=millis();
  i++;
  }




 if(millis()-past>=interval&&i>=13)
  {
   
  lc.setLed(0, 2, i-13, false);
  lc.setLed(0, 1, i-13, false);
  highscore++;
   past=millis();
   i++;
  }

  
   if(i>=21)//13+8
    {
        i=0;
        left-=3;

    
       while(pnoOfTrack==noOfTrack)
          noOfTrack=random(noOfTrack+1,noOfTrack+3);//pt 1 si 2
          
      pnoOfTrack=noOfTrack;
      
            if(interval>100)
              interval-=50;
    }
    else
    {
     if(millis()-past>=interval&&i>7&&i<13)
     {
      i++; 
      highscore++;
      past=millis();
     }
    }
   
   
   
   break;

    
   case 1: {

//for(int i=0;i<8;i++)
//{
//  lc.setLed(0, 0, i, true);
//  lc.setLed(0, 7, i, true);
//  //lc.setLed(0, 1, i, true);
//  
//  }
  
  if(millis()-past>=interval&&i<8)
  {
   lc.setLed(0, 6, i, true);//stanga si dreapta
  lc.setLed(0, 1, i, true);
  highscore++;
  if(i==4&&count>-2&&count<1)
  {
    left+=2;
    right-=2;
  }
  else
  {
    if(i==4&&(count<=-2||count>=1))
    er=1;
  }
  
  past=millis();
  i++;
  }
 
//pana aici am copiat

 


   if(millis()-past>=interval&&i>=13)
  {
   
  lc.setLed(0, 6, i-13, false);
  lc.setLed(0, 1, i-13, false);
  highscore++;
   past=millis();
   i++;
  }

  
   if(i>=21)//13+8
    {i=0;
        left-=2;
    right+=2;
   
     while(pnoOfTrack==noOfTrack)
      noOfTrack=random(noOfTrack-1,noOfTrack+2)%4;
   pnoOfTrack=noOfTrack;
          if(interval>100)
         interval-=50;
    }
    else
    {
     if(millis()-past>=interval&&i>7&&i<13)
     {i++; 
     highscore++;
     past=millis();
     }
     }


 } break;


 

   case 2:    

//    for(int i=0;i<8;i++)
//{
//  lc.setLed(0, 0, i, true);
//  lc.setLed(0, 7, i, true);
//  //lc.setLed(0, 1, i, true);
//  
//  }

  
if(millis()-past>=interval&&i<8)
  {
   lc.setLed(0, 6, i, true);
  lc.setLed(0, 5, i, true);
  highscore++;
  if(i==4&&count<0)
  {
    right-=3;

  }
  else
  {
    if(i==4&&(count>=0))
    er=1;
  }
  
  past=millis();
  i++;
  }




 if(millis()-past>=interval&&i>=13)
  {
   
  lc.setLed(0, 6, i-13, false);
  lc.setLed(0, 5, i-13, false);
  highscore++;
   past=millis();
   i++;
  }

  
   if(i>=21)//13+8
    {i=0;
        right+=3;

    
    
     while(pnoOfTrack==noOfTrack)
      noOfTrack=random(noOfTrack-1,noOfTrack+2)%4;
      
       pnoOfTrack=noOfTrack;
       if(interval>100)
         interval-=50;
    }
    else
    {
     if(millis()-past>=interval&&i>7&&i<13)
     {
      i++; 
      highscore++;
      past=millis();
     }
    }
      
   
   break;

   case 3: 
   

//    for(int i=0;i<8;i++)
//{
//  lc.setLed(0, 0, i, true);
//  lc.setLed(0, 7, i, true);
//  //lc.setLed(0, 1, i, true);
//  
//  }

  
if(millis()-past>=interval&&i<8)
  {
   lc.setLed(0, 0, i, true);
  lc.setLed(0, 1, i, true);
  lc.setLed(0, 2, i, true);
  lc.setLed(0, 3, i, true);
  
  highscore++;
  if(i==4&&count>=1)
  {
    left+=4;

  }
  else
  {
    if(i==4&&(count<1))
    er=1;
  }
  
  past=millis();
  i++;
  }




 if(millis()-past>=interval&&i>=13)
  {
   
  lc.setLed(0, 0, i-13, false);
  lc.setLed(0, 1, i-13, false);
  lc.setLed(0, 2, i-13, false);
  lc.setLed(0, 3, i-13, false);
  highscore++;
   past=millis();
   i++;
  }

  
   if(i>=21)//13+8
    {
        i=0;
        left-=4;

    
    
     while(pnoOfTrack==noOfTrack)
      noOfTrack=random(noOfTrack-1,noOfTrack+1)%4;
      
       pnoOfTrack=noOfTrack;
   
       if(interval>100)
         interval-=50;
    }
    else
    {
     if(millis()-past>=interval&&i>7&&i<13)
     {
      i++; 
      highscore++;
      past=millis();
     }
    }
      
      
   
   
   break;


   case 4: 

  
  
if(millis()-past>=interval&&i<8)
  {
   lc.setLed(0, 4, i, true);
  lc.setLed(0, 5, i, true);
  lc.setLed(0, 6, i, true);
  lc.setLed(0, 7, i, true);
  
  highscore++;
  if(i==4&&count>=1)
  {
    left+=4;

  }
  else
  {
    if(i==4&&(count<1))
    er=1;
  }
  
  past=millis();
  i++;
  }




 if(millis()-past>=interval&&i>=13)
  {
   
  lc.setLed(0, 0, i-13, false);
  lc.setLed(0, 1, i-13, false);
  lc.setLed(0, 2, i-13, false);
  lc.setLed(0, 3, i-13, false);
  highscore++;
   past=millis();
   i++;
  }

  
   if(i>=21)//13+8
    {
        i=0;
        left-=4;

    
    
     while(pnoOfTrack==noOfTrack)
      noOfTrack=random(noOfTrack-1,noOfTrack+1)%4;
      
      pnoOfTrack=noOfTrack;
       if(interval>100)
         interval-=50;
    }
    else
    {
     if(millis()-past>=interval&&i>7&&i<13)
     {
      i++; 
      highscore++;
      past=millis();
     }
    }
      
   
   break;


   
   
   
   break;

   
   
   default: er=1; break;
 }
  }



lcd.setCursor(0,0); 
lcd.print("The Score: ");

lcd.setCursor(10,0); 
lcd.print(highscore);

  

if(er==1)
{
     for (int row = 0; row < ssize; row++)
  {
    for (int col = 0; col < ssize; col++)
    {
      lc.setLed(0, col, row, true); // turns on LED at col, row
      delay(50);
    }
  }
  er=2;
}

if(er==2)
{
  lc.clearDisplay(0);
  

   for(int i2=0;i2<ssize;i2++)
   {
        lc.setLed(0, i2, i2, true);
        lc.setLed(0, ssize-i2, i2, true);
   }
   if(highscore>hs)
      {
         lcd.clear();
         lcd.setCursor(0,0); lcd.print("NEW HS: ");
         lcd.setCursor(7,0); 
         lcd.print(highscore);
      }
   lcd.setCursor(0,1); lcd.print("GAME OVER! ");
}

int reading=swVal;


  if(reading!=lastswState)
{
  lastDebounceTime=millis();
  }

  if(millis()-lastDebounceTime>debounceDelay)
  {
    if(reading!=swState)
   {
    swState=reading;
    if(swState==LOW) //era high
    {
      ok=(ok+1)%2;
    }
   }
   
  }

  lastswState=reading;
   if(ok==1)
   {
        er=0;
        lcd.clear();
      lc.clearDisplay(0);
      i=0;
      ok=0;
      interval=350;
      noOfTrack=1;
      pnoOfTrack=1;
      if(highscore>hs)
      {
        hs=highscore;
      }
      highscore=0;
   }
   
}



 
 Serial.print("Switch:  ");
  Serial.print(swVal);
  Serial.print("  |  ");
  Serial.print("X-axis: ");
  Serial.print(xVal);
  Serial.print("  |  ");
  Serial.print("Y-axis: ");
  Serial.print(yVal);
  Serial.print("  |  ");
  Serial.print("noOfTrack: ");
  Serial.print(noOfTrack);
  Serial.print("  |  ");
  Serial.print("highscore: ");
  Serial.print(highscore);
  Serial.println("  |  ");

  

}
