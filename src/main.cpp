#include <Arduino.h>
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>


PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);


void setup() {
  Serial.begin(115200);           ////serial communication initialization (speed 115200 baud)
  Serial.println("NDEF Writer");  //displaying that the module saves a message that is defined in the code to the card
  nfc.begin();                    //initialization of communication with the module
}


void loop() {
  Serial.println("\nPress the formatted card against the reader.");
  if (nfc.tagPresent()) {
    NdefMessage message = NdefMessage();  //creating a variable of NdefMessage type
    //depending on whether we want to write a certain text or url, we need to comment or uncomment the corresponding line of the code
    //message.addTextRecord("Hello, Arduino!");//adding text to the message variable
    message.addUriRecord("http://arduino.cc");  //adding url to the message variable


    //writing the message variable on the card as a message, the function returns data about whether writing is successful or not
    bool success = nfc.write(message);
    if (success) {
      //if writing was successful, displaying a message about it
      Serial.println("Successful. Try reading the message using reader or mobile phone.");
    } else {
      //if writing was not successful, displaying that there was an error
      Serial.println("Writing unsuccessful.");
    }
  }
  //2 seconds pause
  delay(2000);
}
