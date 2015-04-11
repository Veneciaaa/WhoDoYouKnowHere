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
int count;


void setup() {
  Serial.begin(9600);
  
   Ethernet.begin(mac, ip);
   delay(1000);
  Serial.println("connecting...");
  
   if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: www.google.com");
    client.println("Connection: close");
    client.println();
  }
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }

  
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
  
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
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
