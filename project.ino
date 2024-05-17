#include <LiquidCrystal.h>
#include <stdio.h>

LiquidCrystal lcd(6, 7, 5, 4, 3, 2);


int swi       = 9;
int swe       = 10;
int swd       = 11;
int relay     = 8;

int buzzer    = 13;



char pwds='f';

char keypads='x';
 int ii=0;
 
float tempc=0,weight=0;
float vout=0;

int sti=0;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void serialFlush()
{
  while(Serial.available() > 0) 
  {
    char t = Serial.read();
  }
} 


char cntt=0;
char pd=0,pwd[5];

void keypad()
{
    while(1)
        {
       if(digitalRead(swi) == LOW)
         {delay(700);
        while(digitalRead(swi) == LOW);
             cntt++;
           if(cntt >= 9)
             {
            cntt=9;
             } 

         //clcd(0xc0+pd);  conv1(cntt);
         lcd.setCursor(pd,1);convertk(cntt);
       }
       if(digitalRead(swd) == LOW)
         {delay(700);
        while(digitalRead(swd) == LOW);
             cntt--;
           if(cntt <= 0)
             {
            cntt=0;
           }
         //clcd(0xc0+pd);  conv1(cntt);
         lcd.setCursor(pd,1);convertk(cntt);
       }

      if(digitalRead(swe) == LOW)
         {delay(700);
        while(digitalRead(swe) == LOW);
       
         pwd[pd] = (cntt+48);
         pd++;      
          
         //clcd(0xc0+pd);
          lcd.setCursor(pd,1);
           
            cntt=0;
         if(pd == 4)
           {pd=0;
            break;
           }
       } 
      } 
}



void beep()
{
  digitalWrite(buzzer,LOW);delay(3000);digitalWrite(buzzer,HIGH);
}
 
void setup() 
{
  Serial.begin(9600);//serialEvent();

  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(swi, INPUT);
  pinMode(swe, INPUT);
  pinMode(swd, INPUT);

  digitalWrite(buzzer, HIGH);
  digitalWrite(relay, LOW);
  digitalWrite(swi, HIGH);
  digitalWrite(swe, HIGH);
  digitalWrite(swd, HIGH);

  
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("    Smart Door");
  lcd.setCursor(0,1);
  lcd.print("   lock System");
     delay(3000);
  lcd.clear();
  serialEvent();
}

int otp_n=0;
void loop() 
{
  lcd.clear();
  if(digitalRead(swe) == LOW)
    {delay(1000);
     lcd.clear();lcd.print("Release Enter");
     while(digitalRead(swe) == LOW);
      delay(500);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.write("Enter Password:");
      lcd.setCursor(0,1);
      keypad();delay(1000);
         
      if(strcmp(pwd,"1234") == 0)
        {
         lcd.clear();lcd.print("Correct Pwd");
         lcd.setCursor(0,1);lcd.print("Lock Accessed");
         digitalWrite(relay, HIGH);delay(3000);digitalWrite(relay, LOW);delay(500);     
        }
      else
        {
         lcd.clear();lcd.print("Wrong Pwd");
         beep();   
        }
     lcd.clear();
    }

  if(stringComplete)
    {
      if(inputString[1] == '0' || inputString[1] == '1' || inputString[1] == '2' || inputString[1] == '3')
        {
             lcd.clear();lcd.print("Face Detected");
             lcd.setCursor(0,1);lcd.print("Lock Accessed");
             digitalWrite(relay, HIGH);delay(3000);digitalWrite(relay, LOW);delay(500);
        }
      inputString = "";
      stringComplete = false;
      delay(1000);
      serialFlush();delay(100);
      lcd.clear();
    }
}

void serialEvent() 
{
  while (Serial.available()) 
        {         
         char inChar = (char)Serial.read();
          if(inChar == '*')
            {sti=1;
            }
          if(sti == 1)
            {
                inputString += inChar;
            }
          if(inChar == '#')
            {sti=0;
              stringComplete = true;      
            }
        }
}


void converts(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
   Serial.write(a);
   Serial.write(c);
   Serial.write(e); 
   Serial.write(g);
   Serial.write(h);
}

void convertl(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
   lcd.write(a);
   lcd.write(c);
   lcd.write(e); 
   lcd.write(g);
   lcd.write(h);
}

void convertk(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
  // lcd.write(a);
  // lcd.write(c);
  // lcd.write(e); 
  // lcd.write(g);
   lcd.write(h);
}
