#include <Servo.h>

Servo servo;

//Main motor pins
int motorPin1 = 2;
int motorPin2 = 3;
int motorPin3 = 4;
int motorPin4 = 5;
int motorPin5 = 6;

//Servo pins
int servoPin1 = 7;
int servoPin2 = 8;
int servoPin3 = 9;
int servoPin4 = 10;
int servoPin5 = 11;
int servoPin6 = 12;

//Instruction Buffers
byte instructionB1;

//Reading data
byte MotorE1;
byte MotorE2;
byte MotorE3;
byte MotorE4;
byte MotorE5;


//Data Collection Byte
int incomingByte = 0;
String incomingSByte;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
        Serial.println();
        Serial.write("Waiting");
        Serial.write(45);
        // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingSByte = Serial.readString();

                // say what you got:
                Serial.println();
                Serial.print("I received: ");
                Serial.println(incomingSByte);
        }
        delay(300);
  if (incomingSByte == "s") {
    Send();
    Serial.flush();
  }
  if (incomingSByte == "r") {
    Recieve();
    Serial.flush();
     if (incomingByte == 1) {
    
    }
    if (incomingByte == 2) {
    
    }
    if (incomingByte == 3) {
    
    }
    if (incomingByte == 4) {
    
    }
    if (incomingByte == 5) {
    
    }
    if (incomingByte == 6) {
    
    }
    if (incomingByte == 7) {
    
    }
    if (incomingByte == 8) {
    
    }
    if (incomingByte == 9) {
    
    }
    if (incomingByte == 10) {
    
    }
    if (incomingByte == 11) {
    
    }
    if (incomingByte == 12) {
    
    }
    if (incomingByte == 13) {
    
    }
    if (incomingByte == 14) {
    
    }
  }
}

int Send(){
  bool sending = true;
  bool sent = false;
  while (sending == true){
      Serial.write(40);
      Serial.write("sending");
      Serial.write(41);
      incomingSByte = "";
      return(sent == true);
  }
}
int Recieve(){
  bool recieved = false;
  
  return(recieved = true);
}

void MotorC1(int directional){
  if(directional == 1){
    servo.attach(motorPin1);
    servo.writeMicroseconds(1500); // send "stop" signal to ESC.
    delay(1000);// delay to allow the ESC to recognize the stopped signal
  
    int signal = 1700; // Set signal value, which should be between 1100 and 1900

    servo.writeMicroseconds(signal); // Send signal to ESC.
  }
  else if(directional == 2){
    servo.attach(motorPin1);
    servo.writeMicroseconds(1500); // send "stop" signal to ESC.
    delay(1000);// delay to allow the ESC to recognize the stopped signal
  
    int signal = 1100; // Set signal value, which should be between 1100 and 1900

    servo.writeMicroseconds(signal); // Send signal to ESC.
  }
  else{
    Serial.println("Error 11");
  }
}
void MotorC2(int directional){
  if(directional == 1){
    servo.attach(motorPin2);
    servo.writeMicroseconds(1500); // send "stop" signal to ESC.
    delay(1000);// delay to allow the ESC to recognize the stopped signal
  
    int signal = 1700; // Set signal value, which should be between 1100 and 1900

    servo.writeMicroseconds(signal); // Send signal to ESC.
  }
  else if(directional == 2){
    servo.attach(motorPin2);
    servo.writeMicroseconds(1500); // send "stop" signal to ESC.
    delay(1000);// delay to allow the ESC to recognize the stopped signal
  
    int signal = 1100; // Set signal value, which should be between 1100 and 1900

    servo.writeMicroseconds(signal); // Send signal to ESC.
  }
  else{
    Serial.println("Error 11");
  }
}
void MotorC3(int directional){
  if(directional == 1){
    servo.attach(motorPin3);
    servo.writeMicroseconds(1500); // send "stop" signal to ESC.
    delay(1000);// delay to allow the ESC to recognize the stopped signal
  
    int signal = 1700; // Set signal value, which should be between 1100 and 1900

    servo.writeMicroseconds(signal); // Send signal to ESC.
  }
  else if(directional == 3){
    servo.attach(motorPin1);
    servo.writeMicroseconds(1500); // send "stop" signal to ESC.
    delay(1000);// delay to allow the ESC to recognize the stopped signal
  
    int signal = 1100; // Set signal value, which should be between 1100 and 1900

    servo.writeMicroseconds(signal); // Send signal to ESC.
  }
  else{
    Serial.println("Error 11");
  }
}
void MotorC4(int directional){
  if(directional == 1){
    servo.attach(motorPin4);
    servo.writeMicroseconds(1500); // send "stop" signal to ESC.
    delay(1000);// delay to allow the ESC to recognize the stopped signal
  
    int signal = 1700; // Set signal value, which should be between 1100 and 1900

    servo.writeMicroseconds(signal); // Send signal to ESC.
  }
  else if(directional == 2){
    servo.attach(motorPin4);
    servo.writeMicroseconds(1500); // send "stop" signal to ESC.
    delay(1000);// delay to allow the ESC to recognize the stopped signal
  
    int signal = 1100; // Set signal value, which should be between 1100 and 1900

    servo.writeMicroseconds(signal); // Send signal to ESC.
  }
  else{
    Serial.println("Error 11");
  }
}
void MotorC5(int directional){
  if(directional == 1){
    servo.attach(motorPin5);
    servo.writeMicroseconds(1500); // send "stop" signal to ESC.
    delay(1000);// delay to allow the ESC to recognize the stopped signal
  
    int signal = 1700; // Set signal value, which should be between 1100 and 1900

    servo.writeMicroseconds(signal); // Send signal to ESC.
  }
  else if(directional == 2){
    servo.attach(motorPin5);
    servo.writeMicroseconds(1500); // send "stop" signal to ESC.
    delay(1000);// delay to allow the ESC to recognize the stopped signal
  
    int signal = 1100; // Set signal value, which should be between 1100 and 1900

    servo.writeMicroseconds(signal); // Send signal to ESC.
  }
  else{
    Serial.println("Error 11");
  }
}
void ServoC1(int directional){
    if(directional == 1){
      
    }
    else if(directional ==2){
      
    }
    else{
      Serial.println("Error 11");
    }
  
}
void ServoC2(int directional){
    if(directional == 1){
      
    }
    else if(directional ==2){
      
    }
    else{
      Serial.println("Error 11");
    }
  
}
void ServoC3(int directional){
    if(directional == 1){
      
    }
    else if(directional ==2){
      
    }
    else{
      Serial.println("Error 11");
    }
  
}
void ServoC4(int directional){
    if(directional == 1){
      
    }
    else if(directional ==2){
      
    }
    else{
      Serial.println("Error 11");
    }
  
}
void ServoC5(int directional){
    if(directional == 1){
      
    }
    else if(directional ==2){
      
    }
    else{
      Serial.println("Error 11");
    }
  
}
void ServoC6(int directional){
    if(directional == 1){
      
    }
    else if(directional ==2){
      
    }
    else{
      Serial.println("Error 11");
    }
  
}
