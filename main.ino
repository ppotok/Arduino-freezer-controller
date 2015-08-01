#include <OneWire.h>
#include <DallasTemperature.h>


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

/* Uncomment this block to use hardware SPI
#define OLED_DC     6
#define OLED_CS     7
#define OLED_RESET  8
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
*/

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

unsigned long previousMillis = 0;
const long interval = 1000;    
float temp,settemp=0;

int relay=5;
String state;

void setup()   {
  pinMode(relay, OUTPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC);
 
  sensors.begin();

}


void loop() {
  if(millis() - previousMillis >= interval) {
    // save the last time you blinked the LED 
    previousMillis = millis();  

     settemp=analogRead(A0);
     settemp=map(settemp, 0, 1023, -10, 20); //map function
 sensors.requestTemperatures();
 temp=sensors.getTempCByIndex(0);
 if(temp<=settemp-1){
  state="OFF";
 }
 if(temp>=settemp+1){
  state="ON";
 }
  }
  if(state=="ON"){
    digitalWrite(relay,HIGH); // turn on relay
  }
  if(state=="OFF"){
    digitalWrite(relay,LOW); // turn off relay
  }
  display.clearDisplay();
  // text display tests
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Temp:---- Set:");
  display.setTextSize(2);
  display.println();
  display.print(temp);
  display.print("/");
  display.println(settemp);
  display.setTextSize(1);
  display.setCursor(80,50);
  display.println(state);
   display.display();
}
