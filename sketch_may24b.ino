/*
   IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
   An IR detector/demodulator must be connected to the input RECV_PIN.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
*/

#//include <IRremote.h>
#include <LiquidCrystal.h>

int V = 0;
int RECV_PIN = A0;

int Value;

// IRrecv irrecv(RECV_PIN);

// decode_results results;

#define dirA 12 //定量
#define dirB 13
#define SpeedA 10
#define SpeedB 11

#define VDD 53
#define V0 2
#define RS 49
#define RW 47
#define E 45
#define D4 35
#define D5 33
#define D6 31
#define D7 29
#define A 27
#define K 25

#define Trig 7
#define Echo 8

#define Beep 4 //蜂鸣器

#define Key 9 //按键

int Mode = 0;
int Middle = 180;
//#define Beep 4

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
int Time=0;

void Move(int SpeedL, int SpeedR) {
  analogWrite(SpeedA, abs(SpeedL));
  analogWrite(SpeedB, abs(SpeedR));

  if (SpeedL > 0) digitalWrite(dirA, HIGH);
  else digitalWrite (dirA, LOW);

  if (SpeedR > 0) digitalWrite(dirB, LOW);
  else digitalWrite (dirB, HIGH);
}
void setup()
{
  pinMode(Beep, OUTPUT);
  pinMode(Key, INPUT);
  
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  // irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
  pinMode(dirA, OUTPUT); //电机
  pinMode(dirB, OUTPUT);
  pinMode(SpeedA, OUTPUT);
  pinMode(SpeedB, OUTPUT);

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);

  pinMode(VDD, OUTPUT); digitalWrite(VDD, HIGH);
  pinMode(V0, OUTPUT); analogWrite(V0, 100);
  pinMode(RW, OUTPUT); digitalWrite(RW, LOW);
  pinMode(A, OUTPUT); digitalWrite(A, HIGH);
  pinMode(K, OUTPUT); digitalWrite(K, LOW);

  lcd.begin(16, 2);
  lcd.print("    D-Car");

  Serial.begin(9600);

}

/*void irremote() { //红外遥控器//
  if (irrecv.decode(&results)) {
    V=results.value;

    Serial.println(V);
    irrecv.resume(); // Receive the next value
  }
  if(V==6375) {Move(-255,-255);Serial.println("go");}
  else if(V==4335) Move(-255,0);
  else if(V==26775) Move(0,0);
  else if(V==23205) Move(0,-255);
  else if(V==19125) Move(255,255);
  }*/
/*void LineFollower() { //巡线//
  int T1 = analogRead(A1);
  int T2 = analogRead(A2);
  int T3 = analogRead(A3);
  int T4 = analogRead(A4);
  int T5 = analogRead(A5);
  Serial.print(T1); Serial.print(" ");
  Serial.print(T2); Serial.print(" ");
  Serial.print(T3); Serial.print(" ");
  Serial.print(T4); Serial.print(" ");
  Serial.print(T5); Serial.println(" ");*/
  /* 红外巡线
    if (T4 > 180 && T2 > 180) {
    Move(-255, -255);
    Serial.println("go");
    }
    else if (T4 < 180 && T2 < 180) {
    Move(0, 0);
    Serial.println("stop");
    }
    else if (T4 > 180 && T2 < 180) {
    Move(0, 255);
    Serial.println("right");
    }
    else if (T4 < 180 && T2 > 180) {
    Move(255, 0);
    Serial.println("left");
    }
///防掉落///
    if (T5 < 165) Move(255, -255);
    else if (T1 < 165) Move(-255, 255);
    if (T5 < 165 && T1 < 165) Move(255, -255);
    if (T5 < 165) {
    Move(-255, -255);
    delay(200);
    T1 = analogRead(A1);
    T2 = analogRead(A2);
    T3 = analogRead(A3);
    T4 = analogRead(A4);
    T5 = analogRead(A5);
    if (T5 > 165 && (T4 < 165 || T3 < 165 || T2 < 165 || T1 < 165))
    {
      if (T5 < 165 && T1 < 165) {
        Move(-255, -255);
        delay(200);
        T1 = analogRead(A1);
        T2 = analogRead(A2);
        T3 = analogRead(A3);
        T4 = analogRead(A4);
        T5 = analogRead(A5);
        if (T5 > 165 && T1 > 165 && (T4 < 165 || T3 < 165 || T2 < 165))
          //边缘检测
          if (T5 > 165 && T1 > 165) Move(-255, -255);
          else if (T5 < 165 && T1 < 165) {
            Move(-255, -255);
            delay(500);
            Move(255, 0);
            delay(500);
          }
          else if (T5 > 165 && T1 < 165)Move(0, 255);
          else if (T5 < 165 && T1 > 165)Move(255, 0);
      }*/
//五路传感器//
  

  int getdistance() {
    digitalWrite(Trig, HIGH);
    delayMicroseconds(15);
    digitalWrite(Trig, LOW);

    int Time = pulseIn(Echo, HIGH);
    int distance = Time / 58;
    Serial.println(distance);
    return distance; delay(60);
  }
  /*void loop()
  {
    //if(getdistance()<15) Move(0,0);
    // else Move(-255,-255);
    LineFollower();
  }*/

  void LineFollower() {

    int T1 = analogRead(A1);
    int T2 = analogRead(A2);
    int T3 = analogRead(A3);
    int T4 = analogRead(A4);
    int T5 = analogRead(A5);
    Serial.print(T1); Serial.print(" ");
    Serial.print(T2); Serial.print(" ");
    Serial.print(T3); Serial.print(" ");
    Serial.print(T4); Serial.print(" ");
    Serial.print(T5); Serial.println(" ");

    if(millis()-Time > 500)
    {
    Time = millis();
      
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    D-Car");
    lcd.setCursor(0, 1);
    lcd.print(T1/10); lcd.print(" ");
    lcd.print(T2/10); lcd.print(" ");
    lcd.print(T3/10); lcd.print(" ");
    lcd.print(T4/10); lcd.print(" ");
    lcd.print(T5/10); lcd.print(" ");
    }
     if (T4 < 180)   Move(0, 150);
  if (T2 < 180)   Move(150, 0);
  if (T3 < 180)   Move(255, 255);
  if (T5 < 180)   Move(200, -200);
  if (T1 < 180)   Move(-200, 200);
  }

  void bluetooth()
  {
    //lineFollower();
    if(Serial.available()>0)
    {
      Value=Serial.read();
      Serial.println(Value);
    }
    /*
    if(Value='g')Move(255,255);
   else if(Value='s')Move(0,0);
   */
   switch(Value)
   {
    case 'g':Move(-255,-255);break;
    case 'b':Move(255,255);break;
    case 'l':Move(255,-255);break;
    case 'r':Move(-255,255);break;
    case 's':Move(0,0);break;
   }
  }
  void loop() {
    if (digitalRead(Key) == 0){
      digitalWrite(Beep, HIGH);
      Mode++;
      while (digitalRead(Key) == 0);
      if(Mode>5) Mode=0;
    } 
    else
      digitalWrite(Beep,LOW);
      Serial.println(Mode);
      switch (Mode){
      case 0: Move(0,0); break;
      case 1: LineFollower(); break;
      case 2: EdgeDetect(); break;
      case 3: Ultrasonic(); break;
      case 4: Bluetooth(); break;
      default: Serial.println("something is wrong!")
      }
  }
