#include <BlynkSimpleEsp8266.h>

#define VALUE_NOT_SET -1
#define VALUE_LOWEST_TEMP 5
#define VALUE_HIGHEST_TEMP 25
#define VALUE_TEMP_STEPS 40

const char* ssid = "YOUR_WIFI_SSID";             //Set your wifi network name(ssid)
const char* password = "YOUR_WIFI_PASSWORD";                //Set your router password

char auth[] = "YOUR_AUTH_TOKEN";


#define DLY 6000

//The PINs you used
const int mEncoderPinA = D2;
const int mEncoderPinB = D3;
int mRotaryState = 0;
float mTemperature = VALUE_NOT_SET;

void setup() {
  Serial.begin(9600); //change according to your com port baud rate
  Serial.print("Started ");

  pinMode (mEncoderPinA, OUTPUT);
  pinMode (mEncoderPinB, OUTPUT);
  delay(10);

  Blynk.begin(auth, ssid, password);
}

void loop() {
  Blynk.run();
}

void setTempUp() {
  if (mRotaryState == 1) {
    mRotaryState = 0;
    digitalWrite(mEncoderPinB, HIGH);
    delayMicroseconds(DLY);
    digitalWrite(mEncoderPinA, HIGH);
  } else  {
    mRotaryState = 1;
    digitalWrite(mEncoderPinB, LOW);
    delayMicroseconds(DLY);
    digitalWrite(mEncoderPinA, LOW);
  }
}

void setTempDown() {
  if (mRotaryState == 0) {
    mRotaryState = 1;
    delayMicroseconds(DLY);
    digitalWrite(mEncoderPinA, HIGH);
    delayMicroseconds(DLY);
    digitalWrite(mEncoderPinB, HIGH);
  } else {
    mRotaryState = 0;
    digitalWrite(mEncoderPinA, LOW);
    delayMicroseconds(DLY);
    digitalWrite(mEncoderPinB, LOW);
  }
}

BLYNK_WRITE(V1)
{
  float pinData = param.asInt();
  if (mTemperature == VALUE_NOT_SET) {
    for (int i = 0; i <= VALUE_TEMP_STEPS; i++) {
      setTempDown();
      Serial.print(".");
      delay(200);
    }
    mTemperature = VALUE_LOWEST_TEMP;
  } else if (mTemperature < VALUE_LOWEST_TEMP)
  {
    mTemperature = VALUE_LOWEST_TEMP;
  } else if (mTemperature > VALUE_HIGHEST_TEMP)
  {
    mTemperature = VALUE_HIGHEST_TEMP;
  }

  while (pinData <= mTemperature) {
    setTempDown();
    mTemperature = mTemperature - 0.5;
    Serial.print("Temp: ");
    Serial.println(mTemperature);
    delay(200);
  }

  while (pinData >= mTemperature) {
    setTempUp();
    mTemperature = mTemperature + 0.5;
    Serial.print("Temp: ");
    Serial.println(mTemperature);
    delay(200);
  }

}