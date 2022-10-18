# esp8266-AmazonDashButton

Capture probe request of Amazon dash button.

There are different firmware releases for the second model JK29LP:
- 30017420_US   55s 380mA  short push
- 40018220_WS   55s 380mA  short push
- 50018520_WS  120s 500mA  long press
- 60019520_WS   26s 380mA  short push

Every model can be used as IoT button, because the Amazon Dash Button 
send several probe requests for 200ms. The probe request contains 
the unique mac address of each button and you can define a handler 
for this wifi events.

Each firmware version (e.g. 5xxx) can used without activation via Amazon,
if you long press the button until the blue led display the setup mode.
In this mode the device consume 600mW for 200 seconds and can used 45 times.

Older version <= 4xxx can be activated by a audio hack and after that used by
short push without setup mode.
 1. long press until blue led
 2. play audio (sometimes 50x)
 3. green led signal successful hack
 4. long press until blue led
 5. http://192.168.0.1/?
      amzn_ssid=RSP-8266&
      amzn_pw=Esp.8266
Capture the probe request with ESP. There is a white led after push that
signal the incomplete setup. 
In this mode the device consume 380mW for 55 seconds and can used 135 times.

Newer version 6xxx direct send probe request by short push without the hack.
In this mode the device consume 380mW for 25 seconds and can used 295 times.

Before Amazon shutdown the offical activation the button shut down after
5 seconds and can be used 1385 times.


For more information visit https://blog.christophermullins.com/2019/12/20/rescue-your-amazon-dash-buttons/
 
