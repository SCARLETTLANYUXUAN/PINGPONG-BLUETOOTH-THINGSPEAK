#include <Wire.h>
#include "SSD1306.h" 
#include <BluetoothSerial.h> 
BluetoothSerial SerialBT; 

SSD1306  display(0x3c, 21, 22);
String player1name = "0", player2name = "0";
int p1pin= 25;
int p2pin= 26;
int uploadpin=32;
int player1pin = 19;


int p1mark=0;
int p2mark=0;
bool ing=0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
display.init();
pinMode(player1pin ,INPUT);


pinMode(p1pin, INPUT);
pinMode(p2pin, INPUT);
pinMode(uploadpin,OUTPUT);

SerialBT.begin("Scarlett"); 

}
bool player1 = 0;
int t = 0;

void loop() {
  if (SerialBT.available()) {
    if(player1name == "0"){
      player1name = SerialBT.readString();
    }else{
      player2name = SerialBT.readString();
    }
  }
  int player1Value=digitalRead(player1pin);
  
 /* if(player1Value == HIGH){
    player1 = 1;

  }else{
    player1=0;
  }

  if(player1 == 1 ){
    t = 0;
    Serial.println("MATCH START!");
    
  }

  if(t >= 30 && (player1 != 1)){
    t = 0;
    player1 =  0;
    Serial.println("timeout!no match");
  }else{
    t += 1;
  }

  if(player1 == 1){
    Serial.println("player: ready!");
  }else{
    Serial.println("player: not ready");
  }
*/
Serial.println(player1Value);
  if((player1Value==HIGH)&&(p1mark!=0||p2mark!=0)){
    digitalWrite(uploadpin,HIGH);
    Serial.println("upload ing");
    delay(700);
    player1Value=LOW;
    p1mark=0;
    p2mark=0;
    
  }else{
    Serial.println("no mark");
    digitalWrite(uploadpin,LOW);
  }

  if(digitalRead(p1pin)==HIGH){
    p1mark++;
  }else if (digitalRead(p2pin)==HIGH){
    p2mark++;
  }
 
  
  // put your main code here, to run repeatedly:
  display.clear();
  display.drawString(0,0, String(player1name)+": " + String(p1mark)+"\n"+String(player2name)+": " + String(p2mark));
  display.display();
  delay(1000);
}
