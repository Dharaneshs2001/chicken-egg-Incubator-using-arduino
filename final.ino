#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

DHT dht(4,DHT11);//sensor-orange
LiquidCrystal_I2C lcd(0x27,16,2);

unsigned long int ms,sec1,min1,hr1,day,sec2,min2,hr2,a=1000,b=60,c=24,d,e=1,f=0;
float h,t;

void setup()

{
  dht.begin();
  pinMode(A2,OUTPUT);//switch-white-output
  pinMode(A3,INPUT);//switch-white-input
  pinMode(3,OUTPUT);//motor-green
  pinMode(5,OUTPUT);//bulb-yellow
  pinMode(6,OUTPUT);//humidifier-brown
  analogWrite(A2,f);
  d=analogRead(A3);
  lcd.init();
  lcd.backlight(); 
  
}


void loop()

{
 
ms=millis();
sec1=ms/a;
min1=sec1/b;
hr1=min1/b;
day=hr1/c;
sec2=sec1%b;
min2=min1%b;
hr2=hr1%c;

if(day<10)
{
lcd.setCursor(0,0);
lcd.print("0");
lcd.setCursor(1,0);
lcd.print(day);
}
else
{
  lcd.setCursor(0,0);
  lcd.print(day);
}

lcd.setCursor(2,0);
lcd.print(":");

if(hr2<10)
{
lcd.setCursor(3,0);
lcd.print("0");
lcd.setCursor(4,0);
lcd.print(hr2);
}
else
{
  lcd.setCursor(3,0);
  lcd.print(hr2);
}
lcd.setCursor(5,0);
lcd.print(":");

if(min2<10)
{
lcd.setCursor(6,0);
lcd.print("0");
lcd.setCursor(7,0);
lcd.print(min2);
}
else
{
  lcd.setCursor(6,0);
  lcd.print(min2);
}
lcd.setCursor(8,0);
lcd.print(":");

if(sec2<10)
{
lcd.setCursor(9,0);
lcd.print("0");
lcd.setCursor(10,0);
lcd.print(sec2);
}
else
{
  lcd.setCursor(9,0);
  lcd.print(sec2);
}

t=dht.readTemperature();
h=dht.readHumidity();
lcd.setCursor(0,1);
lcd.print("T=");
lcd.setCursor(2,1);
lcd.print(t);
lcd.setCursor(8,1);
lcd.print("H=");
lcd.setCursor(10,1);
lcd.print(h);

  if(d!=f)  //1-18days
  
  {
    lcd.setCursor(12,0);
    lcd.print("M=18");
    
    if(t<=37.30)
    {
      digitalWrite(5,HIGH);
    }
    else if(t>=37.70)
    {
      digitalWrite(5,LOW);
    }
     if(h<=60.00)
    {
      digitalWrite(6,HIGH);
    }
    else if(h>=65.00)
    {
      digitalWrite(6,LOW);
    }
    if(min2==f&&e!=min1)
    {
      digitalWrite(3,HIGH);
      delay(3550);
      digitalWrite(3,LOW);
      e=min1;
    }
    
  }

  else if(d==f) //18-21days
  {

    lcd.setCursor(12,0);
    lcd.print("M=21");
    
    if(t<=37.10)
    {
      digitalWrite(5,HIGH);
    }
    else if(t>=37.50)
    {
      digitalWrite(5,LOW);
    }
     if(h<=65.00)
    {
      digitalWrite(6,HIGH);
    }
    else if(h>=70.00)
    {
      digitalWrite(6,LOW);
    }
  }

}
