/* nrf24 RC car controller - Receiver
   24.02.2020
   Programme for Radio controlled car with 4 geared motors
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define enL 5//conneced pin num//
#define enR 6//conneced pin num//
#define LF 8//conneced pin num//
#define LB 7//conneced pin num//
#define RF 4//conneced pin num//
#define RB 3//conneced pin num//



int data[2];


RF24 radio(9, 10);  //CE, CSN

const byte password[6] = "00001"; //*enter a security code

const int M = 80;


void setup() {
  pinMode(enL, OUTPUT);
  pinMode(enR, OUTPUT);
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,password);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

}

void loop() {

while (radio.available()) {

    radio.read(data, sizeof(data));

 Serial.print(data[0]);Serial.print("    "); Serial.print(data[1]);Serial.print("    ");

if (data[0] > -M && data[0] < M &&
        data[1] > -M && data[1] < M) {
      analogWrite(enL, 0);
      analogWrite(enL, 0);
      digitalWrite(LF, LOW);
      digitalWrite(RF, LOW);       //stop
      digitalWrite(LB, LOW);
      digitalWrite(RB, LOW);
      Serial.println("data recv- stop");
      
    }else if (data[0] > M && -M<data[1] && data[1]<M) {
      analogWrite(enL, data[0]);
      analogWrite(enR, data[0]);
      digitalWrite(LF, HIGH);
      digitalWrite(RF, HIGH);       //forword
      digitalWrite(LB, LOW);
      digitalWrite(RB, LOW);
Serial.println("data recv- forw");

    }else if (data[0] < -M && -M<data[1] && data[1]<M) {
      analogWrite(enL, -data[0]);
      analogWrite(enR, -data[0]);
      digitalWrite(LB, HIGH);
      digitalWrite(RB, HIGH);      //backword
      digitalWrite(LF, LOW);
      digitalWrite(RF, LOW);
Serial.println("data recv- bacck");

    }else if (-M<data[0] && data[0]<M && data[1]< -M) {
      analogWrite(enL, 200); //data[1]
      analogWrite(enR, 200); //data[1]
      digitalWrite(LF, LOW);
      digitalWrite(RF, HIGH);      //left rotate
      digitalWrite(LB, HIGH);
      digitalWrite(RB, LOW);
Serial.println("data recv- L rot");

    }else if (-M<data[0] && data[0]<M && data[1]>M) {
      analogWrite(enL, 200); //-data[1]
      analogWrite(enR, 200); //-data[1]
      digitalWrite(LF, HIGH);
      digitalWrite(RF, LOW);      //right rotate
      digitalWrite(LB, LOW);
      digitalWrite(RB, HIGH);
Serial.println("data recv- R rot");

    }else if (data[0]>M && data[1]< -M) {
      analogWrite(enL,100 ); //data[0]-data[1]
      analogWrite(enR, 200); //data[0]
      digitalWrite(LF, HIGH);
      digitalWrite(RF, HIGH);      // forword left turn
      digitalWrite(LB, LOW);
      digitalWrite(RB, LOW);
Serial.println("data recv- L trn");

    }else if (data[0]>M && data[1]>M) {
      analogWrite(enL,200 ); //data[0]
      analogWrite(enR, 100); //data[0]+data[1]
      digitalWrite(LF, HIGH);
      digitalWrite(RF, HIGH);      //forword right turn
      digitalWrite(LB, LOW);
      digitalWrite(RB, LOW);
Serial.println("data recv- R trn");

    }else if (-M>data[0] && data[1]<-M) {
      
      analogWrite(enL,100 ); //-data[0]-data[1]
      analogWrite(enR,200 ); //-data[0]
      digitalWrite(LF, LOW);
      digitalWrite(RF, LOW);      //back left turn
      digitalWrite(LB, HIGH);
      digitalWrite(RB, HIGH);
      
Serial.println("left trun back");

    }else if (-M>data[0] && data[1]>M) {
      
      analogWrite(enL,200 ); //-data[0]
      analogWrite(enR,100 ); //-data[0]+data[1]
      digitalWrite(LF, LOW);
      digitalWrite(RF, LOW);      //back right turn
      digitalWrite(LB, HIGH);
      digitalWrite(RB, HIGH);
      
Serial.println("right trun back");

    }

    


  }
}
