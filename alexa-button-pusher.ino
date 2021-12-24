#include <Servo.h>
#include <fauxmoESP.h>
#include "ESP8266WiFi.h"

#define SERVO_PIN 14
#define SERVO_DOWN_US 850
#define SERVO_UP_US 2500

const char* ssid = "abc";
const char* password = "abc";

Servo servo;
fauxmoESP fauxmo;

bool time_to_push_button = true;

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
  }
  
  fauxmo.addDevice("tea");
  fauxmo.setPort(80); // required for gen3 devices
  fauxmo.enable(true);

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
      time_to_push_button = true;
  });

}

void loop() {
  fauxmo.handle();
  
  if(time_to_push_button){
    pushButton();
    time_to_push_button = false;
  }
}

void pushButton()
{
  servo.attach(SERVO_PIN, 500, 2500);
  servo.writeMicroseconds(SERVO_DOWN_US);
  delay(1000);
  servo.writeMicroseconds(SERVO_UP_US);
  delay(2000);
  // detach servo when done using so that it doesn't buzz
  servo.detach();
}
