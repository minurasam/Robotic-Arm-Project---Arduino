#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27,16,2);
byte customChar1[] = {
  B11110,
  B00011,
  B11111,
  B10010,
  B10010,
  B11110,
  B00010,
  B00010
};
void setup()
{
 lcd.init();                     
 lcd.backlight();
 lcd.createChar(0, customChar1);
 lcd.home();
 lcd.write(0);
}

void loop()
{}
