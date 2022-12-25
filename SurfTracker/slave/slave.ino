/*
 * Rui Santos 
 * Complete Project Details https://raspberryme.com
 * https://www.raspberryme.com/guide-du-module-gps-neo-6m-arduino/
 */
 
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

// The TinyGPS++ object
TinyGPSPlus gps;


void setup(){
  Serial.begin(9600);
  ss.begin(9600);
}

struct Message {
  double latitude;
  double longitude;
  uint32_t time;
  uint32_t nbSats;
  int32_t hdop;
};

void loop() {
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0) {
    // get the byte data from the GPS
    byte gpsData = ss.read();
    Serial.write(gpsData);
    gps.encode(gpsData);
    if (gps.location.isUpdated()){
      Message message = {
        gps.location.lat(),
        gps.location.lng(),
        gps.time.value(),
        gps.satellites.value(),
        gps.hdop.value()
      }
      // ToDo: find a way to send message to master
      Serial.print("Sending: "); Serial.println(message);
    }
  }
}
