#include <Servo.h>
#include <DHT.h>
#include <PID_v1.h>
#include <Wire.h>
#include <SPI.h>
//#include <Adafruit_LSM9DS0.h>
//#include <Adafruit_Sensor.h>
//#include <SparkFun_MS5803.h>

const long conServoStopValue = 90; // change after recorded
const long motorHigh = 1760;
const long motorLow = 1230;
const long highAmp = 4.75;
const long lowAmp = 4.82;
const long stopValue = 1500;
const long stopAmp = 0.05;

#define DHTPIN 22     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

#define PIN_INPUT 0
#define PIN_OUTPUT 3
#define LSM9DS0_CSG  9  // CSG connected to Arduino pin 9
#define LSM9DS0_CSXM 10 // CSXM connected to Arduino pin 10
//Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double kp = 2, ki = 5, kd = 1;
PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);

//Comunications
bool function = true;
//Main motor pins
//Servo pins
Servo twistarm; //4 (stop value 90)
Servo servoPin2; //3
Servo servoPin3; //4
Servo agarServo; //3 (less than 90 to colect; 90 is stop value)
Servo servoPin5; //6

Servo LV_motorPin; //7
Servo LH_motorPin; //8
Servo RH_motorPin; //9
Servo RS_motorPin; //10 rear not right
Servo RV_motorPin; //11 
Servo FS_motorPin; //12

//9 degrees of freedom orientation sensor
const long fSDA = 20;
const long fSCL = 21;
//Temperature Humidity Sensor
const long THS = 22;
//Beepy Thingy (Active Low)
const long ByTy = 23;
//RGB Pins (Active Low)
const long RLed = 24;
const long GLed = 25;
const long BLed = 26;
//LED relays (Active High)
const long LedRelay1 = 27;
const long LedRelay2 = 28;

bool lights = false;
double maxamp = 10;

boolean motor1 = false;
boolean motor2 = false;
boolean motor3 = false;
boolean motor4 = false;
boolean motor5 = false;
boolean motor6 = false;
double motorUsage1 = 0;
double motorUsage2 = 0;
double motorUsage3 = 0;
double motorUsage4 = 0;
double motorUsage5 = 0;
double motorUsage6 = 0;

//Motor Servo data
long MotorE1 = 1500;
long MotorE2 = 1500;
long MotorE3 = 1500;
long MotorE4 = 1500; //backwards
long MotorE5 = 1500;
long MotorE6 = 1500;

//DHT variables
long chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

// Begin class with selected address
// available addresses (selected by jumper on board)
// default is ADDRESS_HIGH

//  ADDRESS_HIGH = 0x76
//  ADDRESS_LOW  = 0x77

//MS5803 sensor(ADDRESS_HIGH);

//Create variables to store results
float temperature_c, temperature_f;
double pressure_abs, pressure_relative, altitude_delta, pressure_baseline;

// Create Variable to store altitude in (m) for calculations;
double base_altitude = 1655.0; // Altitude of SparkFun's HQ in Boulder, CO. in (m)

long Vertical;
long X;
long Y;
long Control;
long Strafe;
long sampleRate = 10;


double setpt, input, output;

void setup() {
  
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);

  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);

  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);

  //dht.begin();

  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LedRelay1, OUTPUT);
  pinMode(LedRelay2, OUTPUT);
  //Retrieve calibration constants for conversion math.
  //sensor.reset();
  //sensor.begin();

  //pressure_baseline = sensor.getPressure(ADC_4096);
  for (long i = 2; i <= 12; i++) {
    pinMode(i, OUTPUT);
  }

 // servoPin1.attach(2);
 // servoPin2.attach(3);
 // servoPin3.attach(4);
 // agarServo.attach(2);
 // servoPin5.attach(6);

  LV_motorPin.attach(7); 
  LH_motorPin.attach(8); 
  RH_motorPin.attach(9); 
  RS_motorPin.attach(10); 
  RV_motorPin.attach(11); 
  FS_motorPin.attach(12); 

  digitalWrite(ByTy, HIGH);
  delay(200);
  Serial.println();
  Serial.println("!RSET");
  Serial.println("!PPER 75,77");
  Serial.println("!SPAN 0,10.5");
  Serial.println("!TMAX600");
  Serial.println("!O Slider.Max=10");
  Serial.println("!O txtSW*= "); // Clear all switch text boxes
  Serial.println("!O txtSW3=Master"); //Rename Switch 0
  Serial.println("!O txtSW1=Lights"); //Rename Switch 1
  Serial.println("!O txtLED*= "); // Clear all LED text boxes
  Serial.println("!0 txtLED=Main");
  Serial.println("!0 txtLED=Arm");
  Serial.println("!O txtSlider=Control"); // Label slider
  Serial.println("!PLOT ON");
  Serial.println("@TEXT 35A, 105A, 1.5,(RED), Colonial Robotics");

  //myPID.SetMode(AUTOMATIC);
  //myPID.SetSampleTime(sampleRate);

  LV_motorPin.writeMicroseconds(1500);
  LH_motorPin.writeMicroseconds(1500);
  RH_motorPin.writeMicroseconds(1500);
  RS_motorPin.writeMicroseconds(1500);
  RV_motorPin.writeMicroseconds(1500);
  FS_motorPin.writeMicroseconds(1500);
  delay(100);
}

void loop() {

  read_GUI();
  if (Control == 0)
  {
    Serial.print("ROV control");
   // Serial.print(hum);
   // Serial.print(",");
   // Serial.print(temp);
    Serial.println();
    boolean sw1 = motor1;
    boolean sw2 = motor2;
    boolean sw3 = motor3;
    boolean sw4 = motor4;
    boolean sw5 = motor5;
    boolean sw6 = motor6;
      Lights();
   // MotorC1();
   // MotorC2();
   // MotorC3();
   // MotorC4();
  //  MotorC5();
   // MotorC6();
    //turn();
    if (sw1 != motor1) {
      if (motor1) {
        maxamp -= motorUsage1;
      } else {
        maxamp += motorUsage1;
        motorUsage1=0;
      }
    }
        if (sw1 != motor2) {
      if (motor2) {
        maxamp -= motorUsage2;
      } else {
        maxamp += motorUsage2;
        motorUsage2=0;
      }
    }
        if (sw3 != motor3) {
      if (motor3) {
        maxamp -= motorUsage3;
      } else {
        maxamp += motorUsage3;
        motorUsage3=0;
      }
    }
        if (sw1 != motor4) {
      if (motor4) {
        maxamp -= motorUsage4;
      } else {
        maxamp += motorUsage4;
        motorUsage4=0;
      }
    }
        if (sw5 != motor5) {
      if (motor5) {
        maxamp -= motorUsage5;
      } else {
        maxamp += motorUsage5;
        motorUsage5=0;
      }
    }

    if (sw6 != motor6) {
      if (motor6) {
        maxamp -= motorUsage6;
      } else {
        maxamp += motorUsage6;
        motorUsage6=0;
      }
    }
  }
  else {
    Serial.println("Tool control");
    Serial.println("!O txtSW0=Auger"); //Rename Switch 1
    Serial.println();
       Lights();
    // ServoC1();
    // ServoC2();
    // ServoC3();
    // ServoC4();
    // ServoC5();
  }
  Serial.print(maxamp);
  Serial.print(",");
  Serial.println(motorUsage1);
}

/*lsm.read();

  Serial.print("Accel X: "); Serial.print((int)lsm.accelData.x); Serial.print(" ");
  Serial.print("Y: "); Serial.print((int)lsm.accelData.y);       Serial.print(" ");
  Serial.print("Z: "); Serial.println((int)lsm.accelData.z);     Serial.print(" ");
  Serial.print("Mag X: "); Serial.print((int)lsm.magData.x);     Serial.print(" ");
  Serial.print("Y: "); Serial.print((int)lsm.magData.y);         Serial.print(" ");
  Serial.print("Z: "); Serial.println((int)lsm.magData.z);       Serial.print(" ");
  Serial.print("Gyro X: "); Serial.print((int)lsm.gyroData.x);   Serial.print(" ");
  Serial.print("Y: "); Serial.print((int)lsm.gyroData.y);        Serial.print(" ");
  Serial.print("Z: "); Serial.println((int)lsm.gyroData.z);      Serial.println(" ");
  Serial.print("Temp: "); Serial.print((int)lsm.temperature);    Serial.println(" ");
  delay(200);
}*/

void read_GUI()
{
  //long x, y;
  long control;
  long x2;
  long strafe;
  long servo1;
  long servo2; 
  long servo3;
  long servo4;
  long servo5;
  long Lights;
  flushBuffer();
  Serial.println("!READ (SW3)"); //reads the value for switch 3
  control = Serial.parseInt();
  flushBuffer();
  Serial.println("!READ (gamepad.curY)");
  servo1 = Serial.parseInt();
  flushBuffer();
  Serial.println("!READ (gamepad.curX)");
  servo2 = Serial.parseInt();
  flushBuffer();
  Serial.println("!READ (gamepad.btn1)");
  servo3 = Serial.parseInt();
  flushBuffer();
  Serial.println("!READ (gamepad.btn2)");
  servo4 = Serial.parseInt();
  flushBuffer();
  Serial.println("!READ (gamepad.btn4)");
  servo5 = Serial.parseInt();
  flushBuffer();
  Serial.println("!READ (SW1)");
  Lights = Serial.parseInt();
  if (Lights == 0){
    lights = false;
  }
  else {
    lights = true;
  }
  flush
  flushBuffer();
  Serial.println("!READ (gamepad.curX)"); // read 0 to 65535 for joystick X position, 32767 center
  X = Serial.parseInt();
  flushBuffer();
  Serial.println("!READ (gamepad.curY)");
  Y = Serial.parseInt();
  flushBuffer();
  Serial.println("!READ (gamepad.curX2)"); // read 0 to 65535 for joystick X position, 32767 center
  x2 = Serial.parseInt();
  flushBuffer();
  Serial.println("!READ (gamepad.curPOV)");
  strafe = Serial.parseInt();
  Strafe = strafe;
  Control = control;
  Vertical = x2;
}
void flushBuffer()
{
  Serial.flush(); // flush serial buffer (may not always flush?)
  while (Serial.available()) // manually empty as well, read as long as bytes are in there
    Serial.read();
}

void Lights(){
  if (lights == false){
    digitalWrite(LedRelay1, LOW);
    digitalWrite(LedRelay2, LOW);
  }
  else {
    digitalWrite(LedRelay1, HIGH);
    digitalWrite(LedRelay2, HIGH);
  }
}
int PIDdepth() {
  Serial.println("!READ (gamepad.curY)");
  long  curY = Serial.parseInt();
//  setpt = map(altitude(pressure_abs , pressure_baseline), 0, 1024, 0, 255);
  Input = map(curY, 0, 65355, 0, 255);
  myPID.Compute();
  Serial.println(Output);
  return Serial.parseInt();
}
void turn() {
  if (Strafe == 270) {
    long x = X;
    X = 0;
    MotorC3();
    X = 65355;
    MotorC4();
    X = x;
  }
  else if (Strafe == 90) {
    long x = X;
    X = 65355;
    MotorC3();
    X = 0;
    MotorC4();
    X = x;
  }
  else {

  }
}
void MotorC1() {
  long directional = X;
  if (directional > 32768) {

    RS_motorPin.writeMicroseconds(MotorE2); // send "stop" signal to ESC.

    delay(10);// delay to allow the ESC to recognize the stopped signal

    MotorE2 = map(X, 0, 32767, motorLow, stopValue);

    double usage = map(MotorE2, motorLow, stopValue, lowAmp, stopAmp);
    usage = abs(usage);

    motorUsage2 = usage;


    //maxamp = maxamp - usage;

    long signal = MotorE2; // Set signal value, which should be between 1100 and 1900

    RS_motorPin.writeMicroseconds(signal); // Send signal to ESC.

    MotorE2 = 1500;

    motor2 = true;

  }
  else if (directional < 32766) {


    RS_motorPin.writeMicroseconds(MotorE2); // send "stop" signal to ESC.


    delay(10);// delay to allow the ESC to recognize the stopped signal

    MotorE2 = map(X, 32767, 65535, stopValue, motorHigh);

    double usage = map(MotorE2, stopValue, motorHigh, stopAmp, highAmp);

    usage = abs(usage);

    motorUsage2 = usage;


    //maxamp = maxamp - usage;

    long signal = MotorE2; // Set signal value, which should be between 1100 and 1900

    RS_motorPin.writeMicroseconds(signal); // Send signal to ESC.

    MotorE2 = 1500;

    motor2 = true;
  }
  else {
    motor2 = false;
    RS_motorPin.writeMicroseconds(1500);
    return;
  }
}
void MotorC2() {
  long directional = X;
  if (directional > 32768) {

    FS_motorPin.writeMicroseconds(MotorE2); // send "stop" signal to ESC.

    delay(10);// delay to allow the ESC to recognize the stopped signal

    MotorE2 = map(X, 0, 32767, motorLow, stopValue);

    double usage = map(MotorE2, motorLow, stopValue, lowAmp, stopAmp);
    usage = abs(usage);

    motorUsage2 = usage;


    //maxamp = maxamp - usage;

    long signal = MotorE2; // Set signal value, which should be between 1100 and 1900

    FS_motorPin.writeMicroseconds(signal); // Send signal to ESC.

    MotorE2 = 1500;

    motor2 = true;

  }
  else if (directional < 32766) {


    FS_motorPin.writeMicroseconds(MotorE2); // send "stop" signal to ESC.


    delay(10);// delay to allow the ESC to recognize the stopped signal

    MotorE2 = map(X, 32767, 65535, stopValue, motorHigh);

    double usage = map(MotorE2, stopValue, motorHigh, stopAmp, highAmp);

    usage = abs(usage);

    motorUsage2 = usage;


    //maxamp = maxamp - usage;

    long signal = MotorE2; // Set signal value, which should be between 1100 and 1900

    FS_motorPin.writeMicroseconds(signal); // Send signal to ESC.

    MotorE2 = 1500;

    motor2 = true;
  }
  else {
    motor2 = false;
    FS_motorPin.writeMicroseconds(1500);
    return;
  }
}

void MotorC3() { 
  long directional = Y;
  if (directional > 32768) {


    LH_motorPin.writeMicroseconds(MotorE3  ); // send "stop" signal to ESC.

    delay(10);// delay to allow the ESC to recognize the stopped signal

    MotorE3 = map(Y, 0, 32767, motorLow, stopValue);

    float usage = map(MotorE3, motorLow, stopValue, lowAmp, stopAmp);

    usage = abs(usage);

    motorUsage3 = usage;

    long signal = MotorE3; // Set signal value, which should be between 1100 and 1900

    LH_motorPin.writeMicroseconds(signal); // Send signal to ESC.

    MotorE3 = 1500;
  }

  else if (directional < 32766) {

    LH_motorPin.writeMicroseconds(MotorE3  ); // send "stop" signal to ESC.

    delay(10);// delay to allow the ESC to recognize the stopped signal

    MotorE3 = map(Y, 32767, 65535, stopValue, motorHigh);

    float usage = map(MotorE3, stopValue, motorHigh, stopAmp, highAmp);

    usage = abs(usage);

    motorUsage3 = usage;

    long signal = MotorE3; // Set signal value, which should be between 1100 and 1900

    LH_motorPin.writeMicroseconds(signal); // Send signal to ESC.

    MotorE3 = 1500;
  }

  else {
    LH_motorPin.writeMicroseconds(1500);
  }

}

void MotorC4() {
  long directional = Y;
  if (directional > 32768) {

    RH_motorPin.writeMicroseconds(MotorE4  ); // send "stop" signal to ESC.

    delay(10);// delay to allow the ESC to recognize the stopped signal

    MotorE4 = map(Y, 0, 32767, motorLow, stopValue);

    float usage = map(MotorE4, motorLow, stopValue, lowAmp, stopAmp);

    usage = abs(usage);

    motorUsage4 = usage;

    long signal = MotorE4; // Set signal value, which should be between 1100 and 1900

    RH_motorPin.writeMicroseconds(signal); // Send signal to ESC.

    MotorE2 = 1500;

  }

  else if (directional < 32766) {



    RH_motorPin.writeMicroseconds(MotorE4  ); // send "stop" signal to ESC.

    delay(10);// delay to allow the ESC to recognize the stopped signal

    MotorE4 = map(Y, 32767, 65535, stopValue, motorHigh);

    float usage = map(MotorE4, stopValue, motorHigh, stopAmp, highAmp);

    usage = abs(usage);

    motorUsage4 = usage;

    long signal = 1300; // Set signal value, which should be between 1100 and 1900

    RH_motorPin.writeMicroseconds(signal); // Send signal to ESC.

    MotorE4 = 1500;

  }

  else {
    RH_motorPin.writeMicroseconds(1500);
  }

}

void MotorC5() {
  long directional = Vertical;
  if (directional > 35000) {

    RV_motorPin.writeMicroseconds(1500); // send "stop" signal to ESC.

    delay(10);// delay to allow the ESC to recognize the stopped signal



    long signal = 1700; // Set signal value, which should be between 1100 and 1900



    RV_motorPin.writeMicroseconds(signal); // Send signal to ESC.

  }


  else if (directional < 30000) {


    RV_motorPin.writeMicroseconds(1500); // send "stop" signal to ESC.

    delay(10);// delay to allow the ESC to recognize the stopped signal



    long signal = 1100; // Set signal value, which should be between 1100 and 1900



    RV_motorPin.writeMicroseconds(signal); // Send signal to ESC.

  }

  else {
    RV_motorPin.writeMicroseconds(1500);
  }

}

void MotorC6() {
  long directional = Vertical;

  if (directional > 35000) {

    LV_motorPin.writeMicroseconds(1500); // send "stop" signal to ESC.

    delay(10);// delay to allow the ESC to recognize the stopped signal

    long signal = 1700; // Set signal value, which should be between 1100 and 1900

    LV_motorPin.writeMicroseconds(signal); // Send signal to ESC.
  }

  else if (directional < 30000) {

    LV_motorPin.writeMicroseconds(1500); // send "stop" signal to ESC.

    delay(10);// delay to allow the ESC to recognize the stopped signal

    long signal = 1100; // Set signal value, which should be between 1100 and 1900

    LV_motorPin.writeMicroseconds(signal); // Send signal to ESC.
  }
  else {
    LV_motorPin.writeMicroseconds(1500);
  }
}

void ServoC1() {
  long directional = Y;
    delay(10);// delay to allow the ESC to recognize the stopped signal

    float s1 = map(Y, 0, 32767, 0, 180);

    long signal = s1; // Set signal value, which should be between 1100 and 1900

    s1 = 90;
  
}

void ServoC2() {
   long directional = X;
    delay(10);// delay to allow the ESC to recognize the stopped signal

    float s1 = map(X, 0, 32767, 0, 180);

    long signal = s1; // Set signal value, which should be between 1100 and 1900

    s1 = 90;
  
}

void ServoC3(int directional) {

  if (directional == 1) {
    servoPin3.write(0);
  }
  else if (directional == 2) {
    servoPin3.write(180);
  }
  else if (directional == 3) {
    servoPin3.write(90);
  }
  else {
    Serial.println("Error 11");
  }
}

void ServoC4(int directional) {
  if(directional==1){
    agarServo.write(180);
    agarServo.writeMicroseconds(1800);
    agarServo.write(0);
    agarServo.write(1800);
  }
}

void ServoC5(int directional) {
  if (directional == 1) {
    servoPin5.write(0);
  }
  else if (directional == 2) {
    servoPin5.write(180);
  }
  else if (directional == 3) {
    servoPin5.write(conServoStopValue);
  }
  else {

    Serial.println("Error 11");

  }
}

double sealevel(double P, double A)
// Given a pressure P (mbar) taken at a specific altitude (meters),
// return the equivalent pressure (mbar) at sea level.
// This produces pressure readings that can be used for weather measurements.
{
  return (P / pow(1 - (A / 44330.0), 5.255));
}


double altitude(double P, double P0)
// Given a pressure measurement P (mbar) and the pressure at a baseline P0 (mbar),
// return altitude (meters) above baseline.
{
  return (44330.0 * (1 - pow(P / P0, 1 / 5.255)));
}

