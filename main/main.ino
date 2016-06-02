#include <SoftwareSerial.h>
 
 // RX, TX
SoftwareSerial BLE_Shield(10, 11); 
int VIBR = 2;
int TOUCHE = 4;
int time = 0;

bool canLight = true;

// Output
int redPin = 5;   // Red LED,   connected to digital pin 9
int grnPin = 6;  // Green LED, connected to digital pin 10
int bluPin = 7;  // Blue LED,  connected to digital pin 11

void setup() {
  BLE_Shield.begin(9600);
  Serial.begin(9600);

  pinMode(redPin, OUTPUT);
  pinMode(grnPin, OUTPUT);
  pinMode(bluPin, OUTPUT);
  pinMode(VIBR, OUTPUT);
  
  pinMode(TOUCHE, INPUT);
  
}

// the loop routine runs over and over again forever:
void loop() {
  
  BLE_Shield.listen();
  // while there is data coming in, read it
  // and send to the hardware serial port:
  if (BLE_Shield.available() > 0) {
    Serial.write(BLE_Shield.read());

    gotEmotionAndFeedBack();  
  }

  if(digitalRead(TOUCHE) == HIGH && canLight)
  {
    if(time>=0 && time<200000){
      //Serial.println(time);
      time=time+1;
    }else{
      BLE_Shield.write("A");
      //Serial.println("Sent");
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
  analogWrite(redPin, redVal);   
  analogWrite(grnPin, grnVal);      
  analogWrite(bluPin, bluVal); 
}

void powerOffLed() {
  showColorWithRGB(0,0,0);
}


