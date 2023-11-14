
/*
   RFID_Keyboard.pde
   Sam Sheffield
   
   This code reads the UID from known MiFare Classic NFC tags using an Adafruit PN532 breakout board and simulates a momentary keyboard press in response.
   Keyboard requires Arduino Leonardo or compatible board
   Portions of this code are derived from an example sketch for the Adafruit PN532 NFC/RFID breakout boards: https://www.adafruit.com/products/364
*/
#include <Keyboard.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>

// If using the breakout with SPI, define the pins for SPI communication.
#define PN532_SCK  (2)
#define PN532_MOSI (3)
#define PN532_SS   (4)
#define PN532_MISO (5)
#define PN532_IRQ   (2)
#define PN532_RESET (3)  // Not connected by default on the NFC Shield
Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

// Add a delay to keep from reading a tag multiple times
const int readDelayMS = 500;

// Add all known tag IDs here
const uint32_t knownID[] = {
  1351295744,
  623439741,
  603988480
};

// Keys to match known tags
const char knownIDChar[] = {
  'a',
  's',
  'd'
};

// Update this to match the number of known tags above
const int totalKnownTags = 3;

uint32_t currentID, lastID;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10); // for Leonardo/Micro/Zero
  nfc.begin();
  Keyboard.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  Serial.println("Ready ...");
}


void loop(void) {
  processRFID();
}
