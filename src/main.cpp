#include <Arduino.h>
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "analogWrite.h"
#include "config.h"
#include "web.h"


void setup()
{
  Serial.begin(115200);

  // Create AP
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // HTTP handler assignment
  webserver.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html_gz, sizeof(index_html_gz));
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

  // start server
  webserver.begin();
  server.listen(82);
  Serial.print("Is server live? ");
  Serial.println(server.available());
 
}
 
// handle http messages
void handle_message(WebsocketsMessage msg) {
  commaIndex = msg.data().indexOf(',');
  LRValue = msg.data().substring(0, commaIndex).toInt();
  FBValue  = msg.data().substring(commaIndex + 1).toInt();

   M1_Speed = ( LRValue + FBValue) ;
    M2_Speed = (-LRValue + FBValue) ;
    M3_Speed = ( -LRValue + FBValue) ;
    M4_Speed = ( LRValue + FBValue) ;
  Set_PWM(M1_Speed, M2_Speed, M3_Speed, M4_Speed);
}
 
void loop()
{
  auto client = server.accept();
  client.onMessage(handle_message);
  while (client.available()) {
    client.poll();
  }
}