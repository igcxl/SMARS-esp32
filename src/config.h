const char* ssid = "ESP32_Web"; //Enter SSID
const char* password = "1234qwer"; //Enter Password


//******************PWM引脚和电机驱动引脚***************************//

#define AIN1 32  // A电机控制PWM波
#define AIN2 33  // A电机控制PWM波

#define BIN1 25  // B电机控制PWM波
#define BIN2 26  // B电机控制PWM波

#define CIN1 27  // C电机控制PWM波
#define CIN2 26  //14 v1 // C电机控制PWM波//该端口重启时会输出高电平 需更换

#define DIN1 13  // D电机控制PWM波
#define DIN2 12  // D电机控制PWM波

// these constants are used to allow you to make your motor configuration
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;
int M1_Speed, M2_Speed, M3_Speed, M4_Speed;

//******************电机启动初始值 **********************//
int motorDeadZone =
    30;  //高频时电机启动初始值高约为130，低频时电机启动初始值低约为30,和电池电压、电机特性、PWM频率等有关，需要单独测试
/**************************************************************************
函数功能：赋值给PWM寄存器
入口参数：PWM 还需要添加限幅
**************************************************************************/
void Set_PWM(int motora, int motorb, int motorc, int motord) {
  if (motora > 0)
    analogWrite(AIN2, motora + motorDeadZone),
        analogWrite(AIN1, 0);  //赋值给PWM寄存器根据电机响应速度与机械误差微调,
  else if (motora == 0)
    analogWrite(AIN2, 0), analogWrite(AIN1, 0);
  else if (motora < 0)
    analogWrite(AIN1, -motora + motorDeadZone),
        analogWrite(
            AIN2,
            0);  //高频时电机启动初始值高约为130，低频时电机启动初始值低约为30

  if (motorb > 0)
    analogWrite(BIN2, motorb + motorDeadZone),
        analogWrite(BIN1, 0);  //赋值给PWM寄存器根据电机响应速度与机械误差微调,
  else if (motorb == 0)
    analogWrite(BIN2, 0), analogWrite(BIN1, 0);
  else if (motorb < 0)
    analogWrite(BIN1, -motorb + motorDeadZone),
        analogWrite(
            BIN2,
            0);  //高频时电机启动初始值高约为130，低频时电机启动初始值低约为30

  if (motorc > 0)
    analogWrite(CIN1, motorc + motorDeadZone),
        analogWrite(CIN2, 0);  //赋值给PWM寄存器根据电机响应速度与机械误差微调,
  else if (motorc == 0)
    analogWrite(CIN2, 0), analogWrite(CIN1, 0);
  else if (motorc < 0)
    analogWrite(CIN2, -motorc + motorDeadZone),
        analogWrite(
            CIN1,
            0);  //高频时电机启动初始值高约为130，低频时电机启动初始值低约为30

  if (motord > 0)
    analogWrite(DIN1, motord + motorDeadZone),
        analogWrite(DIN2, 0);  //赋值给PWM寄存器根据电机响应速度与机械误差微调,
  else if (motord == 0)
    analogWrite(DIN1, 0), analogWrite(DIN2, 0);
  else if (motord < 0)
    analogWrite(DIN2, -motord + motorDeadZone),
        analogWrite(
            DIN1,
            0);  //高频时电机启动初始值高约为130，低频时电机启动初始值低约为30
}
 
using namespace websockets;
WebsocketsServer server;
AsyncWebServer webserver(80);

int LValue, RValue, commaIndex;