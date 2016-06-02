#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>         // Include Adafruit NeoPixel library

#define PIN            3               // LED on digital pin 6
#define NUMLEDS        1               // Use total of 1 LED
 
int VIBR = 4;
int TOUCHE = 5;

// Create 'leds' object to drive LEDs
Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUMLEDS, PIN, NEO_GRB + NEO_KHZ800);

int time = 0;
bool canLight = true;

void setup() {
  Serial.begin(115200);

  pinMode(VIBR, OUTPUT);  
  pinMode(TOUCHE, INPUT);

  leds.begin();                       // Initialize 'leds' object

  //Make sure LED is off to demonstrate start of sketch
  leds.setPixelColor(0, leds.Color(0, 0, 0));  // Turn off LED
  leds.show();                        // Set new value
}

void loop() {
  
  // while there is data coming in, read it
  // and send to the hardware serial port:
  if (Serial.read() > 0) {
    gotEmotionAndFeedBack();  
  }

  if(digitalRead(TOUCHE) == HIGH && canLight)
  {
    if(time>=0 && time<200000){
      time=time+1;
    }else{
      sendEmotionAndFeedBack();
      time = 0;
      canLight = false;
    }
  }else if(digitalRead(TOUCHE) == LOW){
    canLight = true;
    time = 0;
  }
}

void sendEmotionAndFeedBack() {
  Serial.write("A");  // J'envoie l'emotion
  showColorWithRGB(20,20,255);
  digitalWrite(VIBR, HIGH);
  delay(300);
  digitalWrite(VIBR, LOW);
  powerOffLed();   
}

void gotEmotionAndFeedBack() {
  showColorWithRGB(235,20,20);
  digitalWrite(VIBR, HIGH);
  delay(200);
  powerOffLed(); 
  digitalWrite(VIBR, LOW);
  delay(200);
  showColorWithRGB(235,20,20);
  digitalWrite(VIBR, HIGH);
  delay(200);
  powerOffLed(); 
  digitalWrite(VIBR, LOW);
  delay(1000);
  showColorWithRGB(235,20,20);
  digitalWrite(VIBR, HIGH);
  delay(200);
  powerOffLed(); 
  digitalWrite(VIBR, LOW);
  delay(200);
  showColorWithRGB(235,20,20);
  digitalWrite(VIBR, HIGH);
  delay(200);
  powerOffLed(); 
  digitalWrite(VIBR, LOW);
  delay(1000);
}

void showColorWithRGB(int redVal, int grnVal, int bluVal) {
  // Write current values to LED pins
  leds.setPixelColor(0, leds.Color(redVal, grnVal, bluVal));
  leds.show(); 
}

void powerOffLed() {
  leds.setPixelColor(0, leds.Color(0, 0, 0));  // Turn off LED
  leds.show();                        // Set new value
}


