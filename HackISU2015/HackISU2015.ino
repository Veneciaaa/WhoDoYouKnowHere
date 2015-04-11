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

// initialize the library with the numbers of the interface pins
//RS, E, D4, D5, D6, D7
LiquidCrystal lcd(4,6, 10, 11, 12, 13);
const int solenoidPin = 8;
int count;

void setup() {
  // set up the LCD's number of columns and rows: 
  pinMode(solenoidPin, OUTPUT);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Who Do You Know?");
  delay(1000);
  count = 0;
}

void loop() {
  /*soleunoid
  digitalWrite(8, HIGH);
  delay(10000);
  digitalWrite(8, LOW);
  delay(1000);
  */
  count++;
 if (checkAccess()){
  lcd.clear();
  lcd.print("You're in!");
  //lcd.print(count);
  digitalWrite(solenoidPin, HIGH); //open solenoid
  
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
 else{
   digitalWrite(solenoidPin, LOW);
   lcd.clear();
   lcd.print("Who Do You Know?");
   delay(3000);
}
  // delay at the end of the full loop:
  delay(500);

}

boolean checkAccess(){
  //needs to be if camera scans the correct QR code
  
  if (count%5== 0)
    return true; 
    
   else
     return false;
}
