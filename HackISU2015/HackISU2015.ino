/*
  LiquidCrystal Library - scrollDisplayLeft() and scrollDisplayRight()

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe 
 modified 22 Nov 2010
 by Tom Igoe

 */

// include the library code:
#include <LiquidCrystal.h>

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server(74,125,232,128);

IPAddress ip(192, 168, 1 , 6);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

// initialize the library with the numbers of the interface pins
//RS, E, D4, D5, D6, D7
LiquidCrystal lcd(4,6, 10, 11, 12, 13);
const int solenoidPin = 8;
const int buttonPin = 3;
int count;


void setup() {
  pinMode(solenoidPin, OUTPUT);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Who Do You Know?");
  delay(2000);
  count = 0;
  
  //set up button
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
  digitalWrite(2, HIGH);
  
}

void loop() {
 //check if button is pressed first
 if (buttonPressed()){
   
  lcd.clear();
  lcd.print("Scan in a sec.");
  delay(5000); //until accessGranted() is implemented
  if(accessGranted()){
    //welcome message & open door --> warning message: door will close soon --> close door
    lcd.clear();
    lcd.print("Come and party!!!");
    digitalWrite(solenoidPin, HIGH); //unlock door
    delay(10000); //leave the door unlocked for a bit
    
    lcd.clear();
    lcd.print("Locking door...");
    delay(10000);
    digitalWrite(solenoidPin, LOW); //lock door
    
    lcd.clear();
    lcd.print("Door is locked!");
    delay(10000);
   }
   else{ //QR code denied
      lcd.clear();
      lcd.print("Sorry rando!");
      delay(15000);
   }
  } 
  
 else{ //button wasn't pressed
   lcd.clear();
   lcd.print("Press the button!");

  }
  
  // delay at the end of the full loop:
  delay(1000);
}


boolean buttonPressed(){
  if(digitalRead(buttonPin) == HIGH){
    return true;
  }
  else
    return false;
}

//turn on server -> turn on webcam -> scan qr code 
//get authentication
//returns true if QR code scanned is correct
boolean accessGranted(){
  return true;
}

void scrollMessage(){
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft(); 
    // wait a bit:
    delay(150);
    }

    // scroll 29 positions (string length + display length) to the right
    // to move it offscreen right:
     for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
      // scroll one position right:
      lcd.scrollDisplayRight(); 
      // wait a bit:
      delay(150);
    }
  
    // scroll 16 positions (display length + string length) to the left
    // to move it back to center:
    for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft(); 
    // wait a bit:
    delay(150);
   }
}
