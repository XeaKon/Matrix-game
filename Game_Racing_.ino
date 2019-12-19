#include "LedControl.h" //  need the library
LedControl lc = LedControl(12, 11, 10, 1); //DIN, CLK, LOAD, No. DRIVER
 
// pin 12 is connected to the MAX7219 pin 1
// pin 11 is connected to the CLK pin 13
// pin 10 is connected to LOAD pin 12
// 1 as we are only using 1 MAX7219


const int axis=A0;
const int ayis=A1;
const int sw=A2;

int xVal=0;
int yVal=0;
int swVal=0;
int xchanged=0;
int ychanged=0;
int count=0;
const int ssize=8;
int left=-2;//limita ofsetului la stanga, pt mijloc
int right=1;//limita ofsetului la dreapta


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

 
void setup()
{
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 2); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
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
 {count=left; poset=0;}
 ychanged=1;
}
else
{
  if(yVal>700&&ychanged==0)
  {
    count++;
    poset=-1;
    if(count>right)
 {count=right; poset=0;}
     ychanged=1;
  }
  else
  {if(yVal>=300&&yVal<=700)
   ychanged=0; 
  }
}


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


  if(er==0)
  {
   switch(noOfTrack)//forma traseului ,track inca nu are utilitate
   {

   case 0:   
    for(int i=0;i<8;i++)
{
  lc.setLed(0, 0, i, true);
  lc.setLed(0, 7, i, true);
  //lc.setLed(0, 1, i, true);
  
  }

  
if(millis()-past>=interval&&i<8)
  {
   lc.setLed(0, 2+track, i, true);
  lc.setLed(0, 1+track, i, true);
  if(i==4&&count>-1)
  {
    left+=2;

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
   
  lc.setLed(0, 2+track, i-13, false);
  lc.setLed(0, 1+track, i-13, false);
   past=millis();
   i++;
  }

  
   if(i>=21)//13+8
    {i=0;
        left-=2;

    
    if(noOfTrack!=0)
      noOfTrack=random(noOfTrack-1,noOfTrack+2)%2;
    else
     {noOfTrack=1;}
     
    }
    else
    {
     if(millis()-past>=interval&&i>7&&i<13)
     {i++; 
     past=millis();
     }
     }
   
   
   
   break;

    
   case 1: {

for(int i=0;i<8;i++)
{
  lc.setLed(0, 0, i, true);
  lc.setLed(0, 7, i, true);
  //lc.setLed(0, 1, i, true);
  
  }
  
  if(millis()-past>=interval&&i<8)
  {
   lc.setLed(0, 6-track, i, true);
  lc.setLed(0, 1+track, i, true);
  if(i==4&&count>-2&&count<1)
  {
    left++;
    right--;
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
   
  lc.setLed(0, 6-track, i-13, false);
  lc.setLed(0, 1+track, i-13, false);
   past=millis();
   i++;
  }

  
   if(i>=21)//13+8
    {i=0;
        left--;
    right++;
    if(noOfTrack!=0)
      noOfTrack=random(noOfTrack-1,noOfTrack+2)%2;
    else
     {noOfTrack=1;}
    }
    else
    {
     if(millis()-past>=interval&&i>7&&i<13)
     {i++; 
     past=millis();
     }
     }


 } break;

   case 2:    
   
   
   break;
   
   default: er=1; break;
 }
  }

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
}


}//sf er if
//else
//{
//   for (int row = 0; row < 8; row++)
//  {
//  for (int col = 0; col < 8; col++)
//  {
//    lc.setLed(0, col, row, true); // turns on LED at col, row
//    delay(25);
//  }
//  }
//
//  }
// 
// }


 
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
  Serial.print("count: ");
  Serial.print(count);
  Serial.println("  |  ");

  
}
