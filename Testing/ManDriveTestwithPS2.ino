//#include <Shield_PS2.h>/
//#include "Omni.h"/
PS2 ps2 = PS2();                  //PS2 class object: ps2
//Omni omni(40,5);//TODO/
int Left_button, Down_button, Right_button, Up_button, Start_button, Right_Joystick_button, Left_Joystick_button, Select_button;
int Square_button, Cross_button, Circle_button, Triangle_button, R1_button, L1_button, R2_button, L2_button;
int Right_Joystick_x, Right_Joystick_y, Left_Joystick_x, Left_Joystick_y;

#include <Omni.h>
#include <Drive.h>
Drive manBotDrive = Drive();
int pwms[] = {2, 5, 8};
int dirs[] = {3, 6, 9};
int brks[] = {4, 7, 11};

//int M1A= 5,M1B = 4,M2A = 7,M2B = 6,M3A = 9,M3B = 8;/
void setup()
{
  Serial.begin(57600);
  ps2.init(57600, 10, 11);   //initialize the main board to use desired (baudrate, rx, tx)
  // pinMode(direction_M1, OUTPUT); //direction pin m1
  // pinMode(PWM_M1, OUTPUT); //pwm pin m1
  // pinMode(direction_M2, OUTPUT); //direction pin m2
  // pinMode(PWM_M2, OUTPUT); //pwn pin m2
  ps2.reset(1);             //call to reset Shield-PS2
  ps2.reset(0);
  Serial.println("PS2 Remote_Cytron Shield");
  Serial.println("Press Start");
  // pinMode(M1A, OUTPUT);
  // pinMode(M1B, OUTPUT);
  // pinMode(M2A, OUTPUT);
  // pinMode(M2B, OUTPUT);
  // pinMode(M3A, OUTPUT);
  // pinMode(M3B, OUTPUT);

  while ((ps2.getval(p_start)));

  Serial.println("Good");
  manBotDrive.init(pwms, dirs, brks);
  delay(1000);
  Serial.println("Initialize success");
  delay(2000);


}

void loop()
{
  if (ps2.getall() == true)   //get all buttons and joystick status
  { getdata();
    printjoystickdata();
    //     if(Up_button==0)
    //        forward(Right_Joystick_x);
    //     else if(Down_button==0)
    //        backward(Right_Joystick_x);
    //     else if(Right_button==0)
    //        right(Right_Joystick_x);
    //     else if(Left_button==0)
    //        left(Right_Joystick_x);

    //  mo/ve(Right_Joystick_x, Left_Joystick_y);
    if (Left_Joystick_x > 100 && (Left_Joystick_y < 100 && Left_Joystick_y > -100)) {
      manBotDrive.moveright();
    }
    else if (Left_Joystick_x < -100 && (Left_Joystick_y < 100 && Left_Joystick_y > -100)) {
      manBotDrive.moveleft();
    }
    else if (Left_Joystick_y < -100 && (Left_Joystick_x < 100 && Left_Joystick_x > -100)){
      manBotDrive.movebackward();
    }
    else if (Left_Joystick_y > 100 && (Left_Joystick_x < 100 && Left_Joystick_x > -100)){
      manBotDrive.moveforward();
    }
  }
  else    //not valid packet received
  {
    Serial.println("no valid packet received");
  }
  delay(50);
}








//Simple function to print 3 digit decimal
int p_dec(char val)
{
  byte data = byte(val);
  return data;
}

void getdata() {
  //Group 1
  Left_button = (ps2.ps_data[0]) & 128;
  if (Left_button == 0)
    Serial.println("Left_button");

  Down_button = (ps2.ps_data[0]) & 64;
  if (Down_button == 0)
    Serial.println("Down_button");

  Right_button = (ps2.ps_data[0]) & 32;
  if (Right_button == 0)
    Serial.println("Right_button");

  Up_button = (ps2.ps_data[0]) & 16;
  if (Up_button == 0)
    Serial.println("Up_button");

  Start_button = (ps2.ps_data[0]) & 8;
  if (Start_button == 0)
    Serial.println("Start_button");

  Right_Joystick_button = (ps2.ps_data[0]) & 4;
  if (Right_Joystick_button == 0)
    Serial.println("Right_Joystick_button");

  Left_Joystick_button = (ps2.ps_data[0]) & 2;
  if (Left_Joystick_button == 0)
    Serial.println("Left_Joystick_button");

  Select_button = (ps2.ps_data[0]) & 1;
  if (Select_button == 0)
    Serial.println("Select_button");

  //Group 2
  Square_button = (ps2.ps_data[1]) & 128;
  if (Square_button == 0)
    Serial.println("Square_button");

  Cross_button = (ps2.ps_data[1]) & 64;
  if (Cross_button == 0)
    Serial.println("Cross_button");

  Circle_button = (ps2.ps_data[1]) & 32;
  if (Circle_button == 0)
    Serial.println("Circle_button");

  Triangle_button = (ps2.ps_data[1]) & 16;
  if (Triangle_button == 0)
    Serial.println("Triangle_button");

  R1_button = (ps2.ps_data[1]) & 8;
  if (R1_button == 0)
    Serial.println("R1_button");

  L1_button = (ps2.ps_data[1]) & 4;
  if (L1_button == 0)
    Serial.println("L1_button");

  R2_button = (ps2.ps_data[1]) & 2;
  if (R2_button == 0)
    Serial.println("R2_button");

  L2_button = (ps2.ps_data[1]) & 1;
  if (L2_button == 0)
    Serial.println("L2_button");

  //both joysticks values on each axes.
  Right_Joystick_x = p_dec(ps2.ps_data[2]);
  Right_Joystick_y = p_dec(ps2.ps_data[3]);
  Left_Joystick_x = p_dec(ps2.ps_data[4]);
  Left_Joystick_y = p_dec(ps2.ps_data[5]);
}
void printjoystickdata() {
  if ((Right_Joystick_x > 130) || (Right_Joystick_x < 125)) {
    Serial.print("Right_Joystick_x = ");
    Serial.println(Right_Joystick_x);
  }

  if ((Right_Joystick_y > 130) || (Right_Joystick_y < 125)) {
    Serial.print("Right_Joystick_y = ");
    Serial.println(Right_Joystick_y);
  }

  if ((Left_Joystick_x > 130) || (Left_Joystick_x < 125)) {
    Serial.print("Left_Joystick_x = ");
    Serial.println(Left_Joystick_x);
  }

  if ((Left_Joystick_y > 130) || (Left_Joystick_y < 125)) {
    Serial.print("Left_Joystick_y = ");
    Serial.println(Left_Joystick_y);
  }

}



void move(int x, int y) {
  x -= 128, y -= 128;

  if (x < 5 && x > -5)
    x = 0;

  if (y < 5 && y > -5)
    y = 0;

  Serial.println(x);
  Serial.println(y);
  Serial.println("");
  omni.setMotion(x, y, 0);
  int j = omni.getw1();
  int k = omni.getw2();
  int l = omni.getw3();


  motor(1, j);
  motor(2, k);
  motor(3, l);
  Serial.println(j);
  Serial.println(k);
  Serial.println(l);
  Serial.println("");
}
void motor(int a, int b) {
  //a is motor choice
  //b is value -255 to 255
  if (a == 1) { //M1
    if (b < 0) {
      digitalWrite(M1A, HIGH);
      digitalWrite(M1B, -b);
    }
    else {
      digitalWrite(M1A, LOW);
      digitalWrite(M1B, b);
    }
  }
  else if (a == 2) { //M2
    if (b < 0) {
      digitalWrite(M2A, HIGH);
      digitalWrite(M2B, -b);
    }
    else {
      digitalWrite(M2A, LOW);
      digitalWrite(M2B, b);
    }
  }
  else if (a == 3) { //M3
    if (b < 0) {
      digitalWrite(M3A, HIGH);
      digitalWrite(M3B, -b);
    }
    else {
      digitalWrite(M3A, LOW);
      digitalWrite(M3B, b);
    }
  }


}

