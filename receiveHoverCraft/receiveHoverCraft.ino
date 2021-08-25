/*
         Arduino based RC Hovercraft
   == Receiver Code - ESC and Servo Control =
  by Dejan, www.HowToMechatronics.com
  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define led 10

RF24 radio(8, 9);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001";
unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

Servo esc1;  // create servo object to control the ESC
Servo esc2;
Servo servo1;

int esc1Value, esc2Value, servo1Value;
// Max size of this struct is 32 bytes - NRF24L01 buffer limit
struct Data_Package {
  byte j1PotX;
  byte j1PotY;
  byte j1Button;
  byte j2PotX;
  byte j2PotY;
  byte j2Button;
  byte pot1;
  byte pot2;
  byte tSwitch1;
  byte tSwitch2;
  byte button1;
  byte button2;
  byte button3;
  byte button4;
};
Data_Package data; //Create a variable with the above structure
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver
  resetData();
  esc1.attach(7);
  esc2.attach(6);
  servo1.attach(5);
  pinMode(led, OUTPUT);
}
void loop() {
  // Check whether we keep receving data, or we have a connection between the two modules
  currentTime = millis();
  if ( currentTime - lastReceiveTime > 1000 ) { // If current time is more then 1 second since we have recived the last data, that means we have lost connection
    resetData(); // If connection is lost, reset the data. It prevents unwanted behavior, for example if a drone jas a throttle up, if we lose connection it can keep flying away if we dont reset the function
  }
  // Check whether there is data to be received
  if (radio.available()) {
    radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
    lastReceiveTime = millis(); // At this moment we have received the data
  }
  // Controlling servos
  servo1Value = map(data.j2PotX-30, 0, 255, 80, 175);//最后两个数值用于调整舵机的极限角度，防止舵机转动角度过大顶坏舵面
  //a为舵机安装误差，可以自己试来调整，直到舵面垂直朝向后面，即舵面处于中值。 
  // servo1Value = map(data.j2PotX-a, 0, 255, 80, 175);
  servo1.write(servo1Value);

  // Controlling brushless motor with ESC
  // Lift propeller中央升力风扇，采用左上角旋钮控制，调整到下方气囊充满即可保持在该位置
  esc1Value = map(data.pot1, 0, 255, 1000, 2000); // Map the receiving value form 0 to 255 to 0 1000 to 2000, values used for controlling ESCs
  esc1.writeMicroseconds(esc1Value); // Send the PWM control singal to the ESC
  
  // Thrust propeller后推涵道风扇，用于控制前行,选用左摇杆，若想实现倒车需要采用双向电调，且不可直接拉到反向，需等螺旋桨停转后方可改变转向
  esc2Value = constrain(data.j1PotY, 130, 255); // 最后两个数值用于设定模式，单向电调设置130，255；双向设置0，255
  esc2Value = map(esc2Value, 130, 255, 1000, 2000);
  //esc2Value = map(data.pot2, 0, 255, 1000, 2000); // 注释掉上面两行取消注释该行来启用右上角旋钮控制后推涵道风扇（仅限单向电调）
  esc2.writeMicroseconds(esc2Value);

  // Monitor the battery voltage灯电量显示
  //int sensorValue = analogRead(A0);
  //float voltage = sensorValue * (5.00 / 1023.00) * 3; // Convert the reading values from 5v to suitable 12V i
  //Serial.println(voltage);
  // If voltage is below 11V turn on the LED
  //if (voltage < 11) {
  //  digitalWrite(led, HIGH);
  //}
  //else {
  //  digitalWrite(led, LOW);
  //}
}
void resetData() {
  // Reset the values when there is no radio connection - Set initial default values
  data.j1PotX = 127;
  data.j1PotY = 127;
  data.j2PotX = 127;
  data.j2PotY = 127;
  data.j1Button = 1;
  data.j2Button = 1;
  data.pot1 = 1;
  data.pot2 = 1;
  data.tSwitch1 = 1;
  data.tSwitch2 = 1;
  data.button1 = 1;
  data.button2 = 1;
  data.button3 = 1;
  data.button4 = 1;
}
