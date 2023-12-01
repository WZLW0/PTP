#define BLINKER_WIFI
#define BLINKER_MIOT_OUTLET   //小爱同学

#include <Servo.h>
#include <Blinker.h>

Servo myservo;

char auth[] = "b50bc7";
char ssid[] = "bbb~";
char pswd[] = "144144xy.com";
int servo_max,servo_min;
BlinkerButton Button1("btn-on");     //定义按钮数据
BlinkerButton Button2("btn-off"); 
//BlinkerButton Button3("btn-aaa");  
bool oState = false;
int counter = 0;
void miotPowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {     //小爱同学控制开命令
        myservo.write(0);
        Blinker.vibrate();
        Blinker.delay(400);
        myservo.write(120);
        Blinker.vibrate();
        BlinkerMIOT.powerState("on");

        BlinkerMIOT.print();

        oState = true;
    }
    else if (state == BLINKER_CMD_OFF) {   //小爱同学控制关命令
        myservo.write(0);
        Blinker.vibrate();
        Blinker.delay(400);
        myservo.write(120);
        Blinker.vibrate();
        BlinkerMIOT.powerState("off");

        BlinkerMIOT.print();

        oState = false;
    }
}

void miotQuery(int32_t queryCode)      //小爱同学控制
{
    BLINKER_LOG("MIOT Query codes: ", queryCode);

    switch (queryCode)
    {
        case BLINKER_CMD_QUERY_ALL_NUMBER :
            BLINKER_LOG("MIOT Query All");
            BlinkerMIOT.powerState(oState ? "on" : "off");
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_POWERSTATE_NUMBER :
            BLINKER_LOG("MIOT Query Power State");
            BlinkerMIOT.powerState(oState ? "on" : "off");
            BlinkerMIOT.print();
            break;
        default :
            BlinkerMIOT.powerState(oState ? "on" : "off");
            BlinkerMIOT.print();
            break;
    }
}

void dataRead(const String & data)      // 如果未绑定的组件被触发，则会执行其中内容
{
    BLINKER_LOG("Blinker readString: ", data);

    Blinker.vibrate();
    
    uint32_t BlinkerTime = millis();
    
    Blinker.print("millis", BlinkerTime);
}
void button1_callback(const String & state)     //点灯app内控制按键触发
{
    
    myservo.write(0);
        Blinker.vibrate();
        Blinker.delay(400);
        myservo.write(120);
        Blinker.vibrate();
    BLINKER_LOG("get button state:on", state);


}
void button2_callback(const String & state)     //点灯app内控制按键触发
{
    
        myservo.write(0);
        Blinker.vibrate();
        Blinker.delay(400);
        myservo.write(120);
        Blinker.vibrate();
    BLINKER_LOG("get button state:off", state);


}

void button3_callback(const String & state)     //点灯app内控制按键触发
{  
  
    BLINKER_LOG("get button state:on", state);
     Blinker.print(state);
    if(state=="on"){
    digitalWrite(0,LOW);
   // Button3.print("on");
     }else if(state =="off"){
            digitalWrite(0,HIGH);
        
    //        Button3.print("off");
    }


}



void setup()
{
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
  
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);
    myservo.attach(0);
    //pinMode(2, OUTPUT);              //定义io口为输出
    myservo.write(120);           //定义io默认为高电平

    BlinkerMIOT.attachPowerState(miotPowerState);
    BlinkerMIOT.attachQuery(miotQuery);
    Button1.attach(button1_callback);  
    Button2.attach(button2_callback);     
 //   Button3.attach(button3_callback); 
 servo_max=70;
    servo_min=120;  
}

void loop()
{
    Blinker.run();
}
