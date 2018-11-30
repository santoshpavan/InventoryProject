#include <LiquidCrystal.h>
#include <Keypad.h>
#include <SoftwareSerial.h>
#include <String.h>
#include <SPI.h>

int data = 0, i=0,l;
int check = -1;
int tag[13] = {36, 48, 48, 48, 53, 55, 54, 52, 48, 52, 50, 10, 13};
String pw="1234", st;
int newtag[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0};


LiquidCrystal lcd(3);
SoftwareSerial rfid(2, 11); // RX and TX

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'7','8','9'},
  {'4','5','6'},
  {'1','2','3'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {10, 9, 7, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 6, 5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

boolean comparetag(int aa[13], int bb[13])
{
  boolean f= false;
  int j = 0;
  for (int k = 0 ; k < 13 ; k++)
  {
    if (aa[k] == bb[k])
    j++;
  }
  if (j == 13)
  f = true;
  return f;
}


int checktag() 
{
  check= 0; 
  // if it is 1 we have a match, zero is a read but no match,
  // -1 is no read attempt made
  if(comparetag(newtag, tag) == true)
  check=1;
  return check;
}

void keyboard()
{
  lcd.clear();
  int z=0;  //to know how many inputs to be taken
  l=pw.length();  //getting the length of password to know the number of inputs
  while(1)
  {
    char key = keypad.getKey(); //getting input from keyboard
    if(key)
    {
      st=st+key; //appending to string st
      lcd.print("*");
      z++;
    }
    if(z==l) //if the thing is done
    break;
  }
  
  lcd.clear();
  
  if(st==pw)
  {
    lcd.clear();
    lcd.print("  WELCOME");
    lcd.setCursor(0,1);
    lcd.print("    TO TRC");
    delay(1500);
    lcd.clear();
    lcd.print("You may access"); 
    lcd.setCursor(0,1);
    lcd.print("the inventory");
  }
  
  else
  {
    lcd.clear();
    lcd.print("Accessing failed");
    lcd.setCursor(0,1);
    lcd.print("INTRUDER!!!");
  }
}
  
void readtag()
{
 int f=-1;
 lcd.clear();
 lcd.print("Swipe your card"); 
 lcd.setCursor(0,1);
 lcd.print("please");
 while(1)
 {
   check = -1;
   if(rfid.available()>0)
   {
     delay(100); //time delay for serial communication
     int f=1;
     for (int i=0; i<13; i++)
     {
       newtag[i]=rfid.read();
       lcd.clear();
     }
     rfid.flush(); //stops multiple reads
     lcd.clear();
     check=checktag();
     delay(2000);
     if (check== 1)
     {
       lcd.clear();
       lcd.print("Card is accepted");
       delay(1000);
       lcd.clear();
       lcd.print("Enter password");
       delay(1500);
       keyboard();
     }
     if (check==0)
     {
       lcd.clear();
       lcd.print("Access Denied");
     }
     if (check==-1)
     {
       lcd.clear();
       lcd.print("Try again");
     }
   }
   if(f==1)  //after the deed is done
   break;
 }
}

void setup()
{
  lcd.begin(16,2);
  rfid.begin(9600);
  lcd.clear();
  lcd.print("TRC WELCOMES");
  lcd.setCursor(5,1);
  lcd.print("YOU");
  delay(2000);
  readtag();
}

void loop(){}
