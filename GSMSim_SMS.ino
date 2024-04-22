

#include <GSMSimSMS.h>

// You can use any Serial interface. I recommended HardwareSerial. Please use the library with highiest baudrate.
// In examples, i used HardwareSerial. You can change it anymore.

#define RESET_PIN 10 // you can use any pin.

static volatile int num = 0;

GSMSimSMS sms(Serial1, RESET_PIN); // GSMSimSMS inherit from GSMSim. You can use GSMSim methods with it.

void setup() {
  Serial1.begin(115200); // If you dont change module baudrate, it comes with auto baudrate.

  while(!Serial1) {
    ; // wait for module for connect.
  }

  Serial.begin(115200); // Serial for debug...

  // Init module...
  sms.init(); // use for init module. Use it if you dont have any valid reason.

  Serial.print("Set Phone Function... ");
  Serial.println(sms.setPhoneFunc(1));
  delay(1000);

  Serial.print("is Module Registered to Network?... ");
  Serial.println(sms.isRegistered());
  delay(1000);

  Serial.print("Signal Quality... ");
  Serial.println(sms.signalQuality());
  delay(1000);

  Serial.print("Operator Name... ");
  Serial.println(sms.operatorNameFromSim());
  delay(1000);



  Serial.print("Init SMS... ");
  Serial.println(sms.initSMS()); // Its optional but highly recommended. Some function work with this function.
  delay(1000);

  Serial.print("List Unread SMS... ");
  Serial.println(sms.list(true)); // Its optional but highly recommended. Some function work with this function.
  delay(1000);

  
  Serial.print("SMS to any number... ");
  Serial.println(sms.send("201093024548", "Selam kardesim, naber?")); // only use ascii chars please
  //delay(1000);

  // For other methods please look at readme.txt file.

  Serial.println("Begin to listen incoming messages...");

}

void loop() {
  
  // Use your Serial interface...
  if(Serial1.available()) {
      String buffer = "";
      buffer = Serial1.readString();
      num = num + 1;
      Serial.print(num);
      Serial.print(". ");
      //Serial.println(buffer);

      /**/
      // This example for how you catch incoming calls.
      if(buffer.indexOf("+CMTI:") != -1) {
        
        Serial.print("SMS Index No... ");
        int indexno = sms.indexFromSerial(buffer);
        Serial.println(indexno);

        Serial.print("Who send the message?...");
        Serial.println(sms.getSenderNo(indexno));

        Serial.print("Read the message... ");
        Serial.println(sms.readFromSerial(buffer));
      } else {
        Serial.println(buffer);
      }
      
  }
  
  // put your main code here, to run repeatedly:
}