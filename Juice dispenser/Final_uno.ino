int data; //Initialized variable to store recieved data
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#include <HX711.h>
HX711 scale;
uint8_t dataPin = 10;
uint8_t clockPin = 11;
float weight =0;
float fill=0;

int en1 =3;
int p1=9;
int en2 =5;
int p2=8;
int en3 =6;
int p3=7;
int Speed=100;


void setup() {
  //Serial Begin at 9600 Baud 
  Serial.begin(9600);
  initialise(); 
  pinMode(12,INPUT);
  
  pinMode(en1,OUTPUT);
  pinMode(p1,OUTPUT);
  
  
  pinMode(en2,OUTPUT);
  pinMode(p2,OUTPUT);

  
  pinMode(en3,OUTPUT);
  pinMode(p3,OUTPUT);
  
  
  loadcell();
  
  }

void loop() {
  weight =scale.get_units(3);
  display.setTextSize(1);
  display.setCursor(17,0);
  display.print("WATER  : OFF ");
  display.print(weight);
  display.setCursor(17,8);
  display.print("JUICE1 : OFF");
  display.setCursor(17,16);
  display.print("JUICE2 : OFF");
  display.setCursor(0,24);
  display.print("PLACE A CUP & COMMAND");
  display.display();

  if (Serial.available()) {
   
  data = Serial.read(); //Read the serial data and store it
 while(true){
   weight =scale.get_units(3);
   if(weight > 60){
    display.setCursor(0,24);
     display.setTextColor(BLACK);
     display.print("PLACE A CUP & COMMAND");
     display.setCursor(17,24);
     display.setTextColor(WHITE);
     display.print("FILLING : ");
     display.display();
    break;
  }
}
  switch (data){
    case 1:
    while(weight<350){
    
     weight =scale.get_units(3);
     fill=(((weight-90)*100)/260);
     analogWrite(en1, 200);
     digitalWrite(p1,HIGH);
     display.setTextSize(1);
     display.setCursor(17,0);
     display.print("WATER  : ON ");
     display.print(weight);
     display.setCursor(17,8);
     display.print("JUICE1 : OFF");
     display.setCursor(17,16);
     display.print("JUICE2 : OFF");
     display.setCursor(17,24);
     display.print("FILLING : ");
     display.print(fill);
     display.print(" %");
     display.display();  
     display.clearDisplay();
      
    }
    digitalWrite(p1,LOW);
    display.clearDisplay(); 
    display.setTextSize(2);
    display.setCursor(10,0);
    display.print("TAKE YOUR");
    display.setCursor(0,16);
    display.print("   WATER");
    display.display(); 
    delay(3000);
     break;
     
    case 2:
     while(weight<350){
     weight =scale.get_units(3);
     fill=(((weight-90)*100)/260);
     analogWrite(en2, Speed);
     digitalWrite(p2,HIGH);
     display.setTextSize(1);
     display.setCursor(17,0);
     display.print("WATER  : OFF ");
     display.print(weight);
     display.setCursor(17,8);
     display.print("JUICE1 : ON");
     display.setCursor(17,16);
     display.print("JUICE2 : OFF");
     display.setCursor(17,24);
     display.print("FILLING : ");
     display.print(fill);
     display.print(" %");
     display.display();  
     display.clearDisplay();  
    }
    digitalWrite(p2,LOW);
    display.clearDisplay(); 
    display.setTextSize(2);
    display.setCursor(10,0);
    display.print("TAKE YOUR");
    display.setCursor(0,16);
    display.print("  JUICE1");
    display.display(); 
    delay(3000);
     break;
     
    case 3:
     while(weight<350){
     weight =scale.get_units(3);
     fill=(((weight-90)*100)/260);
     analogWrite(en3, Speed);
     digitalWrite(p3,HIGH);
     display.setTextSize(1);
     display.setCursor(17,0);
     display.print("WATER  : OFF ");
     display.print(weight);
     display.setCursor(17,8);
     display.print("JUICE1 : OFF");
     display.setCursor(17,16);
     display.print("JUICE2 : ON");
     display.setCursor(17,24);
     display.print("FILLING : ");
     display.print(fill);
     display.print(" %");
     display.display();  
     display.clearDisplay();  
    }
    digitalWrite(p3,LOW);
    display.clearDisplay(); 
    display.setTextSize(2);
    display.setCursor(10,0);
    display.print("TAKE YOUR");
    display.setCursor(0,16);
    display.print("  JUICE2");
    display.display(); 
    delay(3000);
     break;
     
    case 4:
     while(weight<350){
     weight =scale.get_units(3);
     fill=(((weight-90)*100)/260);
     analogWrite(en2, 70);
     digitalWrite(p2,HIGH);
     analogWrite(en3, 70);
     digitalWrite(p3,HIGH);
     display.setTextSize(1);
     display.setCursor(17,0);
     display.print("WATER  : OFF ");
     display.print(weight);
     display.setCursor(17,8);
     display.print("JUICE1 : ON");
     display.setCursor(17,16);
     display.print("JUICE2 : ON");
     display.setCursor(17,24);
     display.print("FILLING : ");
     display.print(fill);
     display.print(" %");
     display.display();  
     display.clearDisplay();  
    }
    digitalWrite(p2,LOW);
    digitalWrite(p3,LOW);
    display.clearDisplay(); 
    display.setTextSize(2);
    display.setCursor(10,0);
    display.print("TAKE YOUR");
    display.setCursor(0,16);
    display.print("    MIX");
    display.display(); 
    delay(3000);
     break;
  
  }
  Serial.println(data); //prints the stored value in ‘data’ to the serial monito
  
  
  }

  else if (Serial.available()==false){
    ;
  }
  display.display();
  display.clearDisplay();

}

void initialise(){
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(17,0);
  display.print("VIRTUAL ASSISTANT");
  display.setCursor(35,8);
  display.print("CONTROLLED"); 
  display.setCursor(23,16);
  display.print("SMART BEVERAGE");
  display.setCursor(38,24);
  display.print("DISPENSER"); 
  display.display(); 
  delay(4000);
  display.clearDisplay();
  display.setTextSize(4);
  display.setCursor(43,0);
  display.print("BY");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(0,5);
  display.print("BATCH-6");
  display.display();
  delay(3000);
  display.clearDisplay();

}

void loadcell(){
  
  scale.begin(dataPin, clockPin);
  display.setTextSize(2);
  display.setCursor(8,0);
  display.print("CALIBRATE");
  display.setTextSize(1);
  display.setCursor(0,16);
  display.print("Remove weight and    push button");
  display.display();
    
  while(true){
  if(digitalRead(12)==LOW){
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(8,0);
    display.print("CALIBRATE");
    display.display();
    break;
  }
  }
  
  scale.tare();
  display.setTextSize(1);
  display.setCursor(0,20);
  display.print("Keep 32g, push button");
  display.display();
  while(true){
  if(digitalRead(12)==LOW){
     scale.calibrate_scale(32, 5);
     display.clearDisplay();
     break;
  }
  }
}
