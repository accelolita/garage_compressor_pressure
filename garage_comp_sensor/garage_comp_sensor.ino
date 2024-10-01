#include "Ambient.h"
#include "secrets.h"
WiFiClient client;
Ambient ambient;

int val;
float press;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);
  WiFi.begin(ssid, password);  //  Wi-Fi APに接続
  while (WiFi.status() != WL_CONNECTED) {  //  Wi-Fi AP接続待ち
      delay(100);
  }
  Serial.print("WiFi connected\r\nIP address: ");
  Serial.println(WiFi.localIP());
  
  ambient.begin(channelId, writeKey, &client); // チャネルIDとライトキーを指定してAmbientの初期化
}

unsigned int sum=0,ave;

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<32;i++)//28.8秒に一回送信
  {
    val=analogRead(33);
    sum+=(int)val;
    delay(900);
  }
  ave=sum/32;
  sum=0;
  press=map(ave,448,4033,10,1000000);
  Serial.println(press);  
  ambient.set(1, String(press).c_str());
  ambient.send();
  
}
