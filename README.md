概述

![Image text](https://github.com/johnsonwust/ArduinoHoverCraft/blob/main/images/01.jpg)
![Image text](https://github.com/johnsonwust/ArduinoHoverCraft/blob/main/images/02.jpg)

通过使用arduino为基础的RC遥控器来控制飞船。具体是，将舵机定位在推力电机的背面，控制推力的方向，设置电位器来控制无刷直流电机的转速，带动螺旋桨转动提供浮力及推力，并设置左操纵杆来控制推进。

![Image text](https://howtomechatronics.com/wp-content/uploads/2019/03/How-Hovercraft-Works-Working-Principle-768x481.jpg)
![Image text](https://howtomechatronics.com/wp-content/uploads/2019/03/DIY-Arduino-RC-Hovercraft-Working-Principle.jpg)
悬浮气垫船 3D 模型

气垫船工作原理
气垫船的基础工作原理是飞船由中央螺旋桨将空气吹入飞船下面，使由柔软材料制成的包围裙膨胀，用空气托起飞船。

![Image text](https://github.com/johnsonwust/ArduinoHoverCraft/blob/main/images/01.jpg)
该气垫船基于开源气垫船方案，进行多处改进以实现更好的操控性及未来拓展性。初代图片仅供参考，该图片外壳使用光固化打印，如有外观需求可联系客服补差价修改打印壳体颜色或更换为光固化打印、更换有机玻璃代替木板，后续会不断改进外观，未来会推出水上航行版本，敬请期待。

![Image text](https://github.com/johnsonwust/ArduinoHoverCraft/blob/main/images/14.jpg)
电调电机采用XXD2212电机2000kv，电调采用3S-30A电调，可自行购买，注意电调需要选择带BEC5V供电的如好盈天行者3S-30A电调，推荐电池为3S 2200mah，电池长度不要超过130mm，桨叶中心孔大小为5mm。该船需搭配接收机使用，无接收机可以选购配套的开源遥控器及接收机，该遥控器还兼容其他创意开源Arduino项目。

随船购买赠送开源接收机PCB空板，可选购Arduino最小系统板（nano或pro mini）及2.4G通信模块，配合Arduino开源遥控器使用，即可实现遥控，也可自行增加无线串口（wifi/蓝牙/2.4G）模块进行遥控（需自己编程）

购买链接：https://item.taobao.com/item.htm?spm=a1z10.1-c-s.w4004-23815833841.12.4f231fe70jFDq6&id=650590887596


在此套件中，我们将构建基于RC悬浮飞船。下面构建悬浮气垫船的整个过程，从设计和 3D 打印气垫船部件（包括螺旋桨）到连接电子元件和Arduino。

![Image text](https://github.com/johnsonwust/ArduinoHoverCraft/blob/main/images/04.jpg)
配货零件及图片
![Image text](https://github.com/johnsonwust/ArduinoHoverCraft/blob/main/images/03.jpg)
正反桨叶一套，后涵道管一件，中涵道管电机固定座一件，左、右后导流板各一件，长短连杆各一件
![Image text](https://github.com/johnsonwust/ArduinoHoverCraft/blob/main/images/05jpg)
后涵道管安装后图片
![Image text](https://github.com/johnsonwust/ArduinoHoverCraft/blob/main/images/16.jpg)
壳体一套，
![Image text](https://github.com/johnsonwust/ArduinoHoverCraft/blob/main/images/08.jpg)
下气垫侧裙一套（该图片包含无刷电机）
![Image text](https://github.com/johnsonwust/ArduinoHoverCraft/blob/main/images/14.jpg)
30A电调，Arduino pro mini ，2.4Ghz通信模块，接收机PCB
![Image text](https://github.com/johnsonwust/ArduinoHoverCraft/blob/main/images/01.jpg)
安装完成后图片


使用串口进行烧录，如ch340、ft232等，编译前需安装nrf24模块的库，在代码最前几行有列出需安装的库。

气垫船接收机的PCB上设计预留了arduino nano版，如需要安装nano最小系统板则注意代码编译时候要选择nano，
采用pro mini最小系统板则编译时选择pro/pro mini，否则会报错。

接收机代码在原版的基础上进行了修改，原版遥控器代码适合带陀螺仪版本的遥控器，可联系客服改价更换，新版遥控器代码去掉了原有陀螺仪控制的部分。代码后续可以自行添加其他功能。


