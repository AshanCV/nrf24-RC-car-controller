/* nrf24 RC car controller - Transmeter
   24.02.2020
   Programme for Radio controlled car with 4 geared motors
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <I2Cdev.h>
#include <Wire.h>


int data[2];
int x; int y;


RF24 radio(9, 10); //CE, CSN //MSOI-11, MISO-12, CLK-13

const byte password[6] = "00001"; //*enter a security code //

void setup() {
  Serial.begin(9600);
  Wire.begin();

  radio.begin();
  radio.openWritingPipe(password);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();


}

void loop() {
 
 
 
 


int sx=0;
int sy=0;

for(int i=0; i<10; i++){
  x = analogRead(A0);
  y = analogRead(A1);

  sx=sx+x;
  sy=sy+y;
  
}
data[0]=sx/10;
data[1]=sy/10;

data[0] = map(data[0], 0,1024, -255, 255); //265 to 403 for gy3 accelomter.. 
data[1] = map(data[1], 0, 1024, -255, 255);

if(data[0]>255){
  data[0]=255;
}
if(data[1]>255){
  data[1]=255;
}
  
 radio.write(data, sizeof(data));
 
Serial.print(data[0]); Serial.print("    ");Serial.println(data[1]);
   
  delay(20);

}
