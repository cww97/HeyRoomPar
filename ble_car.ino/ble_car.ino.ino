#define my_Serial Serial
#define DEBUG_MODE false


const String Go = "G";//蓝牙遥控器发送信息代码定义
const String Back = "B";
const String Right = "R";
const String Left = "L";
const String Stop = "S";
String s = "G";


int left_motor_pin=8;     //左电机(IN3) 输出0  前进   输出1 后退
int left_motor_pwm_pin=9;     //左电机PWM调速
int right_motor_pwm_pin=10;    // 右电机PWM调速
int right_motor_pin=11;    // 右电机后退(IN1)  输出0  前进   输出1 后退

int left_motor;
int right_motor;

void setup()
{
  my_Serial.begin(9600);
  pinMode(left_motor_pin,OUTPUT); // PIN 8 8脚无PWM功能
  pinMode(left_motor_pwm_pin,OUTPUT); // PIN 9 (PWM)
  pinMode(right_motor_pwm_pin,OUTPUT);// PIN 10 (PWM) 
  pinMode(right_motor_pin,OUTPUT);// PIN 11 (PWM)


  right_motor=175;
  left_motor=120;
  digitalWrite(right_motor_pwm_pin,LOW);  // 右电机PWM 调速输出0      
  analogWrite(right_motor_pwm_pin,0);//PWM比例0~255调速，左右轮差异略增减

  digitalWrite(left_motor_pwm_pin,LOW);  //左电机PWM 调速输出0          
  analogWrite(left_motor_pwm_pin,0);//PWM比例0~255调速，左右轮差异略增减
  delay(100);
}


void brake()         //刹车，停车
{
  if (DEBUG_MODE) Serial.println("brake!");
  digitalWrite(right_motor_pwm_pin,LOW);  // 右电机PWM 调速输出0      
  analogWrite(right_motor_pwm_pin,0);//PWM比例0~255调速，左右轮差异略增减

  digitalWrite(left_motor_pwm_pin,LOW);  //左电机PWM 调速输出0          
  analogWrite(left_motor_pwm_pin,0);//PWM比例0~255调速，左右轮差异略增减
  return;
}

void forward()     // 前进
{
  if (DEBUG_MODE) Serial.println("forward!");
  digitalWrite(right_motor_pin,LOW);  // 右电机前进
  digitalWrite(right_motor_pwm_pin,HIGH);  // 右电机前进     
  analogWrite(right_motor_pwm_pin,right_motor);//PWM比例0-255调速
  
  digitalWrite(left_motor_pin,LOW);  // 左电机前进
  digitalWrite(left_motor_pwm_pin,HIGH);  //左电机PWM     
  analogWrite(left_motor_pwm_pin,left_motor);//PWM比例0-255调速
  return;
}

void back()          //后退
{
  if (DEBUG_MODE) Serial.println("back!");
  digitalWrite(right_motor_pin,HIGH);  // 右电机后退
  digitalWrite(right_motor_pwm_pin,HIGH);  // 右电机前进     
  analogWrite(right_motor_pwm_pin,right_motor);//PWM比例0~255调速，左右轮差异略增减
  
  
  digitalWrite(left_motor_pin,HIGH);  // 左电机后退
  digitalWrite(left_motor_pwm_pin,HIGH);  //左电机PWM     
  analogWrite(left_motor_pwm_pin,left_motor);//PWM比例0~255调速，左右轮差异略增减
}

void left()         //左转(左轮后退，右轮前进)
{
  if (DEBUG_MODE) Serial.println("spin_left!");
  digitalWrite(right_motor_pin,LOW);  // 右电机前进
  digitalWrite(right_motor_pwm_pin,HIGH);    // 右电机前进     
  analogWrite(right_motor_pwm_pin,255);//PWM比例0~255调速，左右轮差异略增减
  
  digitalWrite(left_motor_pin,HIGH);  // 左电机后退
  digitalWrite(left_motor_pwm_pin,HIGH);  //左电机PWM     
  analogWrite(left_motor_pwm_pin,255);//PWM比例0~255调速，左右轮差异略增减
  return;
}
void right()        //右转(右轮后退，左轮前进)
{
  if (DEBUG_MODE) Serial.println("spin_right");
  digitalWrite(right_motor_pin,HIGH);  // 右电机后退
  digitalWrite(right_motor_pwm_pin,HIGH);  // 右电机PWM输出1     
  analogWrite(right_motor_pwm_pin,255);//PWM比例0~255调速，左右轮差异略增减
  
  
  digitalWrite(left_motor_pin,LOW);  // 左电机前进
  digitalWrite(left_motor_pwm_pin,HIGH);  //左电机PWM     
  analogWrite(left_motor_pwm_pin,255);//PWM比例0~255调速，左右轮差异略增减
  return;
}

void loop()//主循环函数
{
  if(my_Serial.available()>=0)
  {
    s = my_Serial.readStringUntil('\n');
     Serial.println(s);
  }
  
  if (s == Go ) forward();//如果按GO键，小车前进，直到按STOP键停止
  if (s == Left ) left();
  if (s == Stop ) brake();
  if (s == Right ) right();
  if (s == Back ) back();
//  if (strstr(s, Go) != null ) forward();//如果按GO键，小车前进，直到按STOP键停止
//  else if (strstr(s, Left) != null ) left();
//  else if (strstr(s, Stop) != null ) brake();
//  else if (strstr(s, Right) != null ) right();
//  else if (strstr(s, Back) != null  ) back();
  delay(50);
   //forward();
   //left();
}

