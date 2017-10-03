// E18-D80NK Infrared Distance Ranging Sensor 
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

#define PIN_LED 2 // D4
#define PIN_DETECTOR 5 // D1
#define PIN_RESET_BUTTON 0 // D3 w/ 10K pullup

// anti-jitter
#define TRIGGER_IN_DELAY 2
#define TRIGGER_OUT_DELAY 10
#define TRIGGER_RESET_DELAY 50

#define PAGE_REFRESH_INTERVAL "250"

#define FINISH_COUNT 20

bool status = false; 
unsigned int count = 0;

const char *ssid = "go_spliter";
const char *password = "12345678";

ESP8266WebServer server(80);

void handleRoot() {
  digitalWrite(PIN_LED, LOW);
  char buf[200] = {0};
  sprintf(buf, "<h1>当前计数：%u%s</h1><script>setTimeout('location.reload(true);'," PAGE_REFRESH_INTERVAL ");</script>", count, (count < FINISH_COUNT ? "" : "，已完成！"));
  server.send(200, "text/html", buf);
  digitalWrite(PIN_LED, HIGH);
}

void setup()  {
  delay(1000);
  
  Serial.begin(115200); 
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_DETECTOR, INPUT);
  pinMode(PIN_RESET_BUTTON, INPUT);
  
  WiFi.softAP(ssid, password);
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
 
}
void loop()  {
  count = 0;
  while(1)  {
    if (digitalRead(PIN_RESET_BUTTON) == LOW) {
      delay(TRIGGER_RESET_DELAY);
      if (digitalRead(PIN_RESET_BUTTON) == LOW) {
        // reset
        count = 0;
        status = false;
      }
    }
    server.handleClient();
    if (digitalRead(PIN_DETECTOR)==LOW)  {
     delay(TRIGGER_IN_DELAY);
     if (digitalRead(PIN_DETECTOR)==LOW)  {
       if (status == false) {
         status = true;
         count++;
         Serial.println("Collision Detected.");
       }
     }
    }
    else  {
     delay(TRIGGER_OUT_DELAY);
     if (digitalRead(PIN_DETECTOR)==HIGH) {
       if (status == true) {
         Serial.println("No Collision Detected.");
         status = false;
       }
      }
    }
  }
}
