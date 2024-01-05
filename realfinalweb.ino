#include <WiFi.h>
#include <HTTPClient.h>
const char ssid[]     = "阿福香香的"; //ssid:網路名稱
const char password[] = "68680137"; //password:網路密碼
String url = "http://api.thingspeak.com/update?api_key=2E3MHZ1WMTOX4QG6";
int p1pin= 25;
int p2pin= 26;
int uploadpin=35;
byte totalpoint1 = 0;
byte totalpoint2 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("開始連線到無線網路SSID:");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("連線完成");
  pinMode(p1pin, INPUT);
  pinMode(p2pin, INPUT);
  pinMode(uploadpin,INPUT);
}

void loop() {
  bool upload=0;
  // put your main code here, to run repeatedly:
  upload=digitalRead(uploadpin);
  Serial.println(upload);
  Serial.println(totalpoint1);
  Serial.println(totalpoint2);
  if (digitalRead(p1pin)==HIGH){
    totalpoint1++;
  }else if(digitalRead(p2pin)==HIGH){
   totalpoint2++;
  }
  if(upload==1){
    HTTPClient http;
    String url1 = url + "&field1=" + (int)totalpoint1+ "&field2=" + (int)totalpoint2;
  //http client取得網頁內容
    http.begin(url1);
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK)      {
    //讀取網頁內容到payload
    String payload = http.getString();
    //將內容顯示出來
    Serial.print("網頁內容=");
    Serial.println(totalpoint1);
    Serial.println(totalpoint2);
    } else {
    //讀取失敗
    Serial.println("網路傳送失敗");
    }
  totalpoint1=0;
  totalpoint2=0;
    upload=0;
    http.end();
  
  }delay(1000);
}
