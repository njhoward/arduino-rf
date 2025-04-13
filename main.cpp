#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // D2 = interrupt 0
}

void loop() {
  if (mySwitch.available()) {
    unsigned long value = mySwitch.getReceivedValue();
    unsigned int protocol = mySwitch.getReceivedProtocol();
    unsigned int bitlen = mySwitch.getReceivedBitlength();
    unsigned int pulse = mySwitch.getReceivedDelay();

    Serial.print("RAW;");
    Serial.print("value=");
    Serial.print(value);
    Serial.print(";protocol=");
    Serial.print(protocol);
    Serial.print(";bitlen=");
    Serial.print(bitlen);
    Serial.print(";pulse=");
    Serial.print(pulse);
    Serial.print(";data=");

    const unsigned int* timings = mySwitch.getReceivedRawdata();
    int len = bitlen * 2;
    if (len > 256) len = 256;

    for (int i = 0; i < len; i++) {
      Serial.print(timings[i]);
      if (i < len - 1) Serial.print(" ");
    }

    Serial.println();

    mySwitch.resetAvailable();
  }
}
