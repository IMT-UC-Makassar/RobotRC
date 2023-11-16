#include <PS2X_lib.h>

PS2X ps2x;

//right now, the library does NOT support hot-pluggable controllers, meaning
//you must always either restart your Arduino after you connect the controller,
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 0;

//l293D driver motor depan
const int motorDepan_kiri_en = 9;
const int motorDepan_kiri_1 = 22;
const int motorDepan_kiri_2 = 23;

const int motorDepan_kanan_en = 8;
const int motorDepan_kanan_1 = 24;
const int motorDepan_kanan_2 = 25;

//L293d driver motor belakang
const int motorBelakang_kiri_en = 7;
const int motorBelakang_kiri_1 = 26;
const int motorBelakang_kiri_2 = 27;

const int motorBelakang_kanan_en = 6;
const int motorBelakang_kanan_1 = 28;
const int motorBelakang_kanan_2 = 29;



void setup() {
  Serial.begin(57600);

  //SETUP MOTOR Depan
  pinMode(motorDepan_kiri_en, OUTPUT);
  pinMode(motorDepan_kiri_1, OUTPUT);
  pinMode(motorDepan_kiri_2, OUTPUT);

  pinMode(motorDepan_kanan_en, OUTPUT);
  pinMode(motorDepan_kanan_1, OUTPUT);
  pinMode(motorDepan_kanan_2, OUTPUT);

  //SETUP MOTOR Belakang
  pinMode(motorBelakang_kiri_en, OUTPUT);
  pinMode(motorBelakang_kiri_1, OUTPUT);
  pinMode(motorBelakang_kiri_2, OUTPUT);

  pinMode(motorBelakang_kanan_en, OUTPUT);
  pinMode(motorBelakang_kanan_1, OUTPUT);
  pinMode(motorBelakang_kanan_2, OUTPUT);

  //INITIAL STATE - MOTOR ALL OFF
  setMotorDirection(1, 0);
  setMotorDirection(2, 0);
  setMotorDirection(3, 0);
  setMotorDirection(4, 0);


  //SETUP JOYSTICK
  error = ps2x.config_gamepad(52, 51, 53, 50, true, false); //GamePad(clock, command, attention, data, Pressures?, Rumble?)

  if (error == 0) {
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
  }

  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");

  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.println("Unknown Controller type");
      break;
    case 1:
      Serial.println("DualShock Controller Found");
      break;
    case 2:
      Serial.println("GuitarHero Controller Found");
      break;
  }

}

void loop() {
  /* You must Read Gamepad to get new values
    Read GamePad and set vibration values
    ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
    if you don't enable the rumble, use ps2x.read_gamepad(); with no values

    you should call this at least once a second
  */
//  if (error == 1)
//    return;
  
  readGamepad();
  delay(50);

  /*
  Serial.println("forward");
  setMotorSpeed(1, 150);//set speed 200
  setMotorSpeed(2, 150);//set speed 200
  setMotorSpeed(3, 150);//set speed 200
  setMotorSpeed(4, 150);//set speed 200
  
  setMotorDirection(1,1);
  setMotorDirection(2,1);
  setMotorDirection(3,1);
  setMotorDirection(4,1);
  delay(3000);
  
  Serial.println("stop");
  setMotorDirection(1,0);
  setMotorDirection(2,0);
  setMotorDirection(3,0);
  setMotorDirection(4,0);
  delay(500);
  
  Serial.println("backward");
  setMotorDirection(1,2);
  setMotorDirection(2,2);
  setMotorDirection(3,2);
  setMotorDirection(4,2);
  delay(3000);
  
  Serial.println("stop");
  setMotorDirection(1,0);
  setMotorDirection(2,0);
  setMotorDirection(3,0);
  setMotorDirection(4,0);
  delay(500);
  */
  
}

void setMotorDirection(int motorNumber, int motorDirection) {
  /*
     MotorNumber berurut sesuai posisi

     1 = kiri depan
     2 = kanan depan
     3 = kiri belakang
     4 = kanan belakang

     motor direction
     0 = off
     1 = maju
     2 = mundur
  */

  if (motorNumber == 1) {
    switch (motorDirection) {
      case 0:
        digitalWrite(motorDepan_kiri_1, LOW);
        digitalWrite(motorDepan_kiri_2, LOW);
        break;
      case 1:
        digitalWrite(motorDepan_kiri_1, HIGH);
        digitalWrite(motorDepan_kiri_2, LOW);
        break;
      case 2:
        digitalWrite(motorDepan_kiri_1, LOW);
        digitalWrite(motorDepan_kiri_2, HIGH);
        break;
    }
  } else if (motorNumber == 2) {
    switch (motorDirection) {
      case 0:
        digitalWrite(motorDepan_kanan_1, LOW);
        digitalWrite(motorDepan_kanan_2, LOW);
        break;
      case 1:
        digitalWrite(motorDepan_kanan_1, HIGH);
        digitalWrite(motorDepan_kanan_2, LOW);
        break;
      case 2:
        digitalWrite(motorDepan_kanan_1, LOW);
        digitalWrite(motorDepan_kanan_2, HIGH);
        break;
    }
  } else if (motorNumber == 3) {
    switch (motorDirection) {
      case 0:
        digitalWrite(motorBelakang_kiri_1, LOW);
        digitalWrite(motorBelakang_kiri_2, LOW);
        break;
      case 1:
        digitalWrite(motorBelakang_kiri_1, HIGH);
        digitalWrite(motorBelakang_kiri_2, LOW);
        break;
      case 2:
        digitalWrite(motorBelakang_kiri_1, LOW);
        digitalWrite(motorBelakang_kiri_2, HIGH);
        break;
    }
  } else if (motorNumber == 4) {
    switch (motorDirection) {
      case 0:
        digitalWrite(motorBelakang_kanan_1, LOW);
        digitalWrite(motorBelakang_kanan_2, LOW);
        break;
      case 1:
        digitalWrite(motorBelakang_kanan_1, HIGH);
        digitalWrite(motorBelakang_kanan_2, LOW);
        break;
      case 2:
        digitalWrite(motorBelakang_kanan_1, LOW);
        digitalWrite(motorBelakang_kanan_2, HIGH);
        break;
    }
  }
}


void setMotorSpeed(int motorNumber, int motorSpeed) {
  /*
     motor speed valua 0-255
  */

  if (motorNumber == 1) {
      analogWrite(motorDepan_kiri_en, motorSpeed);
  } else if (motorNumber == 2) {
      analogWrite(motorDepan_kanan_en, motorSpeed);
  } else if (motorNumber == 3) {
      analogWrite(motorBelakang_kiri_en, motorSpeed);
  } else if (motorNumber == 4) {
      analogWrite(motorBelakang_kanan_en, motorSpeed);
  }
}

void readGamepad() {

  ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
     if (ps2x.Button(PSB_START))                  //will be TRUE as long as button is pressed
    Serial.println("Start is being held");
  if (ps2x.Button(PSB_SELECT))
    Serial.println("Select is being held");
  /*
   * baca value stick
   * mestinya mentok di 125. value ini yang nanti jadi speed motor
   * 
   * Untuk gerakan mecanum refer ke: https://docs.revrobotics.com/duo-build/ftc-starter-kit-mecanum-drivetrain/mecanum-wheel-setup-and-behavior
   * 
   */



   //Baca stick analog
   int stick_LY = (ps2x.Analog(PSS_LY) - 128 )* -1;
   int stick_LX = (ps2x.Analog(PSS_LX) - 128 )* -1;
   int stick_RY = (ps2x.Analog(PSS_RY) - 128 )* -1;
   int stick_RX = (ps2x.Analog(PSS_RX) - 128 )* -1;

   
  Serial.print("Stick Values:");
  Serial.print(stick_LY, DEC); //Left stick, Y axis. Other options: LX, RY, RX
  Serial.print(",");
  Serial.print(stick_LX, DEC);
  Serial.print(",");
  Serial.print(stick_RY, DEC);
  Serial.print(",");
  Serial.println(stick_RX, DEC);

  /*
   * Atur gerakan motor sesuai dengan strik.
   * 
   * 
   * RY+ = maju
   * RY- = mundur
   * RX- = ngesot kanan
   * RX+ = ngesot kiri
   * 
   * LX+ = putar kanan
   * LX- = putar kiri
   * 
   */

   if((stick_RY > 0) && (stick_RX == 0)){
     //maju
     Serial.println("forward");
      setMotorSpeed(1, stick_RY);//set speed 200
      setMotorSpeed(2, stick_RY);//set speed 200
      setMotorSpeed(3, stick_RY);//set speed 200
      setMotorSpeed(4, stick_RY);//set speed 200
      
      setMotorDirection(1,1);
      setMotorDirection(2,1);
      setMotorDirection(3,1);
      setMotorDirection(4,1);
   } else if((stick_RY < 0) && (stick_RX == 0)){
     //maju
      Serial.println("backward");
      Serial.println((stick_RY * -1));
      setMotorSpeed(1, stick_RY * -1);//set speed 200
      setMotorSpeed(2, stick_RY * -1);//set speed 200
      setMotorSpeed(3, stick_RY * -1);//set speed 200
      setMotorSpeed(4, stick_RY * -1);//set speed 200
      
      setMotorDirection(1,2);
      setMotorDirection(2,2);
      setMotorDirection(3,2);
      setMotorDirection(4,2);
   }else if((stick_RX < 0) && (stick_RY == 0)){
     //maju
      Serial.println("ngesot Kanan");
      Serial.println((stick_RX * -1));
      setMotorSpeed(1, stick_RX * -1);//set speed 200
      setMotorSpeed(2, stick_RX * -1);//set speed 200
      setMotorSpeed(3, stick_RX * -1);//set speed 200
      setMotorSpeed(4, stick_RX * -1);//set speed 200
      
      setMotorDirection(1,1);
      setMotorDirection(2,2);
      setMotorDirection(3,2);
      setMotorDirection(4,1);
   } else if((stick_RX > 0) && (stick_RY == 0)){
     //ngesot kiri
      Serial.println("ngesot Kiri");
      Serial.println((stick_RX ));
      setMotorSpeed(1, stick_RX );//set speed 200
      setMotorSpeed(2, stick_RX );//set speed 200
      setMotorSpeed(3, stick_RX );//set speed 200
      setMotorSpeed(4, stick_RX );//set speed 200
      
      setMotorDirection(1,2);
      setMotorDirection(2,1);
      setMotorDirection(3,1);
      setMotorDirection(4,2);
   } else if((stick_LX > 0) && (stick_LY == 0)){
     //maju
      Serial.println("putar Kanan");
      Serial.println((stick_RX ));
      setMotorSpeed(1, stick_RX );//set speed 200
      setMotorSpeed(2, stick_RX );//set speed 200
      setMotorSpeed(3, stick_RX );//set speed 200
      setMotorSpeed(4, stick_RX );//set speed 200
      
      setMotorDirection(1,1);
      setMotorDirection(2,2);
      setMotorDirection(3,1);
      setMotorDirection(4,2);
   } else if((stick_LX < 0) && (stick_LY == 0)){
     //maju
      Serial.println("Putar Kiri");
      Serial.println((stick_RX * -1));
      setMotorSpeed(1, stick_RX * -1);//set speed 200
      setMotorSpeed(2, stick_RX * -1);//set speed 200
      setMotorSpeed(3, stick_RX * -1);//set speed 200
      setMotorSpeed(4, stick_RX * -1);//set speed 200
      
      setMotorDirection(1,2);
      setMotorDirection(2,1);
      setMotorDirection(3,2);
      setMotorDirection(4,1);
   }
   
   else {
    Serial.println("stop");
      setMotorSpeed(1, stick_RY);//set speed 200
      setMotorSpeed(2, stick_RY);//set speed 200
      setMotorSpeed(3, stick_RY);//set speed 200
      setMotorSpeed(4, stick_RY);//set speed 200
      
      setMotorDirection(1,0);
      setMotorDirection(2,0);
      setMotorDirection(3,0);
      setMotorDirection(4,0);
   }
  

  /*
  if (ps2x.Button(PSB_START))                  //will be TRUE as long as button is pressed
    Serial.println("Start is being held");
  if (ps2x.Button(PSB_SELECT))
    Serial.println("Select is being held");


  if (ps2x.Button(PSB_PAD_UP)) {        //will be TRUE as long as button is pressed
    Serial.print("Up held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
  }
  if (ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.print("Right held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
  }
  if (ps2x.Button(PSB_PAD_LEFT)) {
    Serial.print("LEFT held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
  }
  if (ps2x.Button(PSB_PAD_DOWN)) {
    Serial.print("DOWN held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
  }


  vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on
  //how hard you press the blue (X) button

  if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
  {
    if (ps2x.Button(PSB_L3))
      Serial.println("L3 pressed");
    if (ps2x.Button(PSB_R3))
      Serial.println("R3 pressed");
    if (ps2x.Button(PSB_L2))
      Serial.println("L2 pressed");
    if (ps2x.Button(PSB_R2))
      Serial.println("R2 pressed");
    if (ps2x.Button(PSB_GREEN))
      Serial.println("Triangle pressed");

  }


  if (ps2x.ButtonPressed(PSB_RED))            //will be TRUE if button was JUST pressed
    Serial.println("Circle just pressed");

  if (ps2x.ButtonReleased(PSB_PINK))            //will be TRUE if button was JUST released
    Serial.println("Square just released");

  if (ps2x.NewButtonState(PSB_BLUE))           //will be TRUE if button was JUST pressed OR released
    Serial.println("X just changed");


  if (ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
  {
    Serial.print("Stick Values:");
    Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_LX), DEC);
    Serial.print(",");
    Serial.print(ps2x.Analog(PSS_RY), DEC);
    Serial.print(",");
    Serial.println(ps2x.Analog(PSS_RX), DEC);
  }
  */
}
