
#include "PN532_SPI.h"
#include "PN532.h"
#include "NfcAdapter.h"
#include "Grove_LCD_RGB_Backlight.h"

#define SS A2

STARTUP(WiFi.selectAntenna(ANT_EXTERNAL));
SYSTEM_THREAD(ENABLED);

rgb_lcd lcd;

PN532_SPI pn532_spi(SPI, SS);
NfcAdapter nfc = NfcAdapter(pn532_spi);

void setup(void) {
    Serial.begin(9600);
    Serial.println("NDEF Reader");

    lcd.begin(16, 2);
    lcd.setRGB(100, 100, 100);
    lcd.print("TAG UID");

    nfc.begin();
}

void loop(void) {
    Serial.println("\nScan a NFC tag\n");
    if (nfc.tagPresent())
    {
        NfcTag tag = nfc.read();
        tag.print();

        lcd.setCursor(0,1);
        lcd.print(tag.getUidString());
    }
    delay(1000);
}
