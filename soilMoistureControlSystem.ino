//soil moisture control system
#include <LowPower.h>

#define baudRate 9600
#define scanTime 1
#define refreshTime 100

#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8
#define DIG4 9
#define DIG3 10
#define DIG2 11
#define DIG1 12
#define digButton 15
#define pump 16


int moistureSensor = A0;

int num1 = 0;
int num2 = 0;
int num3 = 0;
int num4 = 0;
int moisture = 0;
int cnt = 0;
/*MOISTURE VALUE
* value of air of the moisture sensor is 450~380
* dry soil is 300
* half-dry is 250
* half-wet is 220
* full-wet soil is 190
* (water is 195)
* control strategy: 
*  400~305 start watering, 250 stop watering. (due to moisture transfer delayed)
*/
void setup()
{
  //Serial.begin(baudRate);         //Serial
  
  //O/P:
  //--1.four-digits seven segment display: D2~D12
  //--2.water pump: D16
  //I/P:
  //--1.soil moisture sensor: A0
  //--2.7-segment display button: D15
  for(int i = 2; i < 14; i++) {
    pinMode(i,OUTPUT);
  }
  pinMode(digButton, INPUT_PULLUP); //display button
  pinMode(pump, OUTPUT);
  pinMode(moistureSensor, INPUT);   //moisture Sensor
    
  //turn off all seven segment LED
  digitalWrite(DIG1, HIGH);
  digitalWrite(DIG2, HIGH);
  digitalWrite(DIG3, HIGH);
  digitalWrite(DIG4, HIGH);
}
void loop()
{
  for(int i=0;i<500;i++){
  //read moisture
    if(cnt>refreshTime){
      moisture = analogRead(moistureSensor);
      if (moisture != 0){
        num2 = moisture/100%10;
        num3 = moisture/10%10;
        num4 = moisture%10;
      }
      else{
        num1 = 10;
        num2 = 10;
        num3 = 10;
        num4 = 10;
      }
      cnt = 0;
    }

    //display moisture on seven segment
    if(digitalRead(digButton) == LOW){
    digitalWrite(DIG2, LOW);
    displayNumber(num2);
    delay(scanTime);
    digitalWrite(DIG2, HIGH);

    digitalWrite(DIG3, LOW);
    displayNumber(num3);
    delay(scanTime);
    digitalWrite(DIG3, HIGH);

    digitalWrite(DIG4, LOW);
    displayNumber(num4);
    delay(scanTime);
    digitalWrite(DIG4, HIGH);
    }
    else{
      delay(scanTime);
    }

  cnt++;
  }

  //Serial.print("moisture: ");Serial.println(moisture);  //Serial
  if(moisture < 400 && moisture > 305){                   //too dry, need watering
    digitalWrite(pump, HIGH);
    digitalWrite(13, HIGH);
  }
  else if(moisture < 250 || moisture > 440){              //wet enough, stop watering
    digitalWrite(pump, LOW);
    digitalWrite(13, LOW);
  }
  delay(1);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);         //low power mode, save energy
  
}

void displayNumber(int number) {
  switch (number) {
    case 0: zero(); break;
    case 1: one(); break;
    case 2: two(); break;
    case 3: three(); break;
    case 4: four(); break;
    case 5: five(); break;
    case 6: six(); break;
    case 7: seven(); break;
    case 8: eight(); break;
    case 9: nine(); break;
    case 10: none(); break;
  }
}
void zero(){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}
void one(){
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}
void two(){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}
void three(){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}
void four(){
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
void five(){
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
void six(){
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
void seven(){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}
void eight(){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
void nine(){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
void none(){
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}
