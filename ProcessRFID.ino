
void processRFID() {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    // Only MiFare Classic tags supported
    if (uidLength == 4)
    {
      uint32_t cardid = uid[0];
      cardid <<= 8;
      cardid |= uid[1];
      cardid <<= 8;
      cardid |= uid[2];
      cardid <<= 8;
      cardid |= uid[3];
      currentID = cardid;
      
      // Uncomment to get card ID numbers
      Serial.println(currentID);

      // Send a keypress whenever a new tag is detected
      if (currentID != lastID) {
        for (int i = 0; i < totalKnownTags; i++) {
          if (currentID == knownID[i]) {
          Keyboard.write(knownIDChar[i]);
          }
        }
        lastID = currentID;
      }
    }
    
    // Add delay just to slow down multiple reads
    delay(readDelayMS);
  }
}
