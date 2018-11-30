#include <LiquidCrystal.h>
#include <Keypad.h>
#include <SoftwareSerial.h>
#include <String.h>
//#include <Password.h>
#include <SPI.h>

int data = 0, i=0,l;
int check = -1;
int tag[13] = {36, 48, 48, 48, 53, 55, 54, 52, 48, 52, 50, 10, 13};
String pw="1234", st;
int newtag[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0};
//String final="###";

//Password password = Password("1234");
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
  int z=0;
  //int h=0;
  //l=pw.length();
  while(1){
 // lcd.clear();
 // lcd.print("  (y)");
 // delay(2000);
  char key = keypad.getKey();
  //lcd.clear();
  //lcd.print("Enter the password");
  //lcd.clear();
  if(key)
  {
    st=st+key;
    //lcd.clear();
    lcd.print(key);
    delay(1000);
    z++;
  }
  //st=st+key;
  lcd.clear();
  //lcd.setCursor(0,1);
  //lcd.print(z);
  //delay(1000);
  //for(i=0;i<4;i++)
  //{lcd.print(st[i]);
  //delay(1000);}
  if(z==4)
  {break;}
  }
  lcd.clear();
  //lcd.print("st=");
//  for(i=0;i<4;i++){
//  lcd.print(st);
//  delay(2000);}
  //String s=st[l-3]+st[l-2]+st[l-1];
  //if(z==4)
  //{
    if(st==pw)
    {
      lcd.clear();
      lcd.print("     WELCOME");
      lcd.setCursor(0,1);
      lcd.print("        TO TRC");
      delay(1500);
      lcd.clear();
      lcd.print("You may access"); 
      lcd.setCursor(0,1);
      lcd.print("the inventory");
      //Serial.println("now the motors are opened");
      //digitalWrite( ,HIGH);
    }
    if(st!=pw)
    {
      lcd.clear();
      lcd.print("You are so dead");
    }
  //}
}
  
void readtag()
{
 int f=-1;
 lcd.clear();
 lcd.print("Swipe your card"); 
 lcd.setCursor(0,1);
 lcd.print("please");
 //while(!rfid.available()){}
 while(1)
 {
   check = -1;
   if(rfid.available()>0)
   {
   //if (rfid.available()>0)
  // {}
     //read the tag
    // delay(100); //time delay for serial communication
     int f=1;
     //lcd.clear();
     //lcd.print(check);
     //delay(2000);
    // lcd.clear();
    // lcd.print("data");
    // delay(1000);
     for (int i=0; i<13; i++)
     {
       newtag[i]=rfid.read();
       lcd.clear();
      // lcd.print(newtag[i]);
       //delay(1500);
     }
     rfid.flush(); //stops multiple reads
     lcd.clear();
  //   lcd.print("newtag=");
    // delay(1000);
     //lcd.clear();
    // for(int lm=0;lm<13;lm++)
    // {
    //  lcd.clear();
    //  lcd.print(newtag[i]);
   //   delay(1500);
   //  }
     //lcd.clear();
     //lcd.print("checking the tag");
     //delay(1000);
     check=checktag();
     //lcd.clear();
     //lcd.print(check);
     delay(2000);
     if (check== 1)
     {
       lcd.clear();
       lcd.print("Card is accepted");
       delay(1000);
       lcd.clear();
       lcd.print("Enter the password");
       delay(1500);
       //l=pw.length();
       //while(i<l)
       //{
         keyboard();
       //}
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
   if(f==1)
   break;
 }
}

void setup()
{
  lcd.begin(16,2);
  rfid.begin(9600);
  //ask for the swipe
  lcd.clear();
  lcd.print("TRC WELCOMES");
  lcd.setCursor(5,1);
  lcd.print("YOU");
  delay(2000);
//  lcd.clear();
//  lcd.print("Swipe yours card"); 
//  lcd.setCursor(0,1);
//  lcd.print("please");
  //delay(1500);
  //while(1)
 // {
    readtag();
  //}
}

void loop(){}
