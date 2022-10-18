/*

 This sketch shows you the MAC address
 of your Amazon Dash Buttons by
 capture the probe requests.

 Use a serial monitor to see the logs.

 There are different firmware releases
 for the second model JK29LP:
 30017420_US   10s 380mA  short push
 40018220_WS   10s 380mA  short push
 50018520_WS  120s 500mA  long press
 60019520_WS   26s 380mA  short push

 Every model can be used as IoT button,
 because the Amazon Dash Button send 
 several probe requests for 200ms.
 The probe request contains the unique
 mac address of each button and you can
 define a handler for this wifi events.

 Each firmware version (e.g. 5xxx) can 
 used without activation via Amazon,
 if you long press the button until 
 the blue led display the setup mode.
 In this mode the device consume 600mW
 for 200 seconds and can used 45 times.

 Older version <= 4xxx can be activated
 by a audio hack and after that used by
 short push without setup mode.
 1. long press until blue led
 2. play audio (sometimes 50x)
 3. green led signal successful hack
 4. long press until blue led
 5. http://192.168.0.1/?
      amzn_ssid=RSP-8266&
      amzn_pw=Esp.8266
 Capture the probe request with ESP.
 There is a white led after push that
 signal the incomplete setup.
 In this mode the device consume 380mW
 for 55 seconds and can used 135 times
 with visible access point and 
 for 10 seconds and 740 times with
 hidden access point.

 Newer version 6xxx direct send probe
 request by short push without the hack.
 In this mode the device consume 380mW
 for 25 seconds and can used 295 times.

 Before Amazon shutdown the offical
 activation the button shut down after
 5 seconds and can be used 1385 times.
 
*/

#include <ESP8266WiFi.h>
#include <stdio.h>

#ifndef APSSID
#define APSSID "ESP-Gateway"
#define APPSK  "Esp.8266"
#endif

const char* ssid     = APSSID;
const char* password = APPSK;

WiFiEventHandler stationConnectedHandler;
WiFiEventHandler stationDisconnectedHandler;
WiFiEventHandler probeRequestPrintHandler;
WiFiEventHandler probeRequestBlinkHandler;

bool blinkFlag;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  // Don't save WiFi configuration in flash
  WiFi.persistent(false);

  // Set up an access point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password, 1, true);

  // Register event handlers.
  // Call "onStationConnected" each time a station connects
  stationConnectedHandler = WiFi.onSoftAPModeStationConnected(&onStationConnected);
  // Call "onStationDisconnected" each time a station disconnects
  stationDisconnectedHandler = WiFi.onSoftAPModeStationDisconnected(&onStationDisconnected);
  // Call "onProbeRequestPrint" and "onProbeRequestBlink" each time
  // a probe request is received.
  // Former will print MAC address of the station to Serial.
  probeRequestPrintHandler = WiFi.onSoftAPModeProbeRequestReceived(&onProbeRequestPrint);
}

void onStationConnected(const WiFiEventSoftAPModeStationConnected& evt) {
  Serial.print("Station connected: ");
  Serial.println(macToString(evt.mac));
}

void onStationDisconnected(const WiFiEventSoftAPModeStationDisconnected& evt) {
  Serial.print("Station disconnected: ");
  Serial.println(macToString(evt.mac));
}

void onProbeRequestPrint(const WiFiEventSoftAPModeProbeRequestReceived& evt) {
  Serial.print("Probe request from: ");
  Serial.println(macToString(evt.mac));
}

void loop() {
  yield();
  delay(10);
}

String macToString(const unsigned char* mac) {
  char buf[20];
  snprintf(buf, sizeof(buf), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}
