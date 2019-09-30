# smart-wifi-thermostat
Control  EQ-3 N/K thermostats with Google Assistant or Alexa (ESP8266 & IFTT)

## What you need?
- EQ-3 N/K thermostat
- ESP8266 (I used a NodeMCU)
- Soldering iron
- radiator

## Let's start: 

You have to solder 3 wires to the rotary encoder on the thermostat. Have a look at [this](http://unwx.de/blog1/2017/01/20/heizkoerperthermostatsteuerung-mit-esp8266-07/) blog entry.

In the next step create a new [Bylnk project](https://github.com/blynkkk) and flash the code below with the created auth token to your ESP8266.

Head over to [IFTT](https://ifttt.com/create) and build your own applet. 
"IF" should be the Google Assistant or Alexa Service and "THAT" should be the service Webhooks which is able to make a webrequest.
If you choose "If say a phrase with a number" your trigger has to include a # a the position of the number: "I want to have # degrece in my living room" 

This number could be used in the GET request to tell Blynk which number should be passed to the ESP8266: 
http://blynk-cloud.com/YOUR_AUTH_TOKEN/update/V1?value={{NumberField}}


Le voilà!

![](gif.gif)

The first input will decrement the thermostat so that the microcontroller and the rotary enconder are synchronized.
Then it will incrment to the wanted temperature. All further temperature steps will be adjusted without this reset.






