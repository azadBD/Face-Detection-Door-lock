#include <IRremote.h>
#include <Keypad.h>
int IRpin = 5;
int lock=0,f=0,l=0,p=0,m=0;
int BReceived=0;
IRrecv irrecv(IRpin);
decode_results results;

char* password = "4169";  // change the password here, just pick any 3 numbers
int counter = 0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10,11,12,13}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
}  
void loop() 

{   // Below is Remote Program become start
  if (irrecv.decode(&results)) 
    {
     Serial.println(results.value); // Print the Serial 'results.value'
      delay(10);
   
      if((results.value==16773645)&&(lock==0))
        {
          digitalWrite(2, HIGH);
          lock=1;
        }
      else if((results.value==16773645)&&(lock==1))
        {
          digitalWrite(2, LOW);
          lock=0;
        }

      else if((results.value==16763445)&&(f==0))
        {
          digitalWrite(3, HIGH);
          f=1;
        }
      else if((results.value==16763445)&&(f==1))
        {
          digitalWrite(3, LOW);
          f=0;
        }
      else if((results.value==16755285)&&(l==0))
        {
          digitalWrite(4, HIGH);
          l=1;
        }
      else if((results.value==16755285)&&(l==1))
        {
          digitalWrite(4, LOW);
          l=0;
        }
      else if((results.value==16720095)&&((f==0)||(l==0)))
      {
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      f=1;
      l=1;
      }
      
      else if((results.value==16720095)&&((f==1)||(l==1)))
      {
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      f=0;
      l=0;
      }

      else if((results.value==16730805)&&((f==0)||(l==0)))
      {
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      f=1;
      l=1;
      }
      
      else if((results.value==16730805)&&((f==1)||(l==1)))
      {
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      f=0;
      l=0;
      }
      
     irrecv.resume();   // Receive the next value
    }

    

 // Below is Bluetooth Program become start

   if(Serial.available()>0)
 { 
    BReceived = Serial.read();
    
 }

if ((lock == 0) && (BReceived == '1'))
  {
    digitalWrite(2,HIGH);
    lock=1;
    BReceived=0;  
  }
if ((lock == 1) && (BReceived == '1'))
  {
    digitalWrite(2,LOW);
    lock=0;
    BReceived=0;  
  }
if ((f == 0) && (BReceived == '2'))
  {
    digitalWrite(3,HIGH);
    f=1;
    BReceived=0;  
  }
if ((f == 1) && (BReceived == '2'))
  {
    digitalWrite(3,LOW);
    f=0;
    BReceived=0;  
  }
if ((l == 0) && (BReceived == '3'))
  {
    digitalWrite(4,HIGH);
    l=1;
    BReceived=0;  
  }
if ((l == 1) && (BReceived == '3'))
  {
    digitalWrite(4,LOW);
    l=0;
    BReceived=0;  
  }
if ((BReceived == '4')&&((f==0)||(l==0)))
  {
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    f=1;
    l=1;
    BReceived=0;  
  }
if ((BReceived == '4')&&((f==1)||(l==1)))
  {
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    f=0;
    l=0;
    BReceived=0;  
  }

// Below is Keypad Program become start

char key = keypad.getKey();
if (key)
  {
    Serial.println(key);
  } 
if (key == '*' || key == '#')
{
counter = 0;
digitalWrite(2, HIGH);
}
if (key == password[counter])
{
counter ++;
}
if (counter == 4)
{
digitalWrite(2, LOW);
}

    
}    
