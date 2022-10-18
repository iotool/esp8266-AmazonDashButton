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

