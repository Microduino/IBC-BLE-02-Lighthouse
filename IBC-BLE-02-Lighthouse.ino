#include "colorLed.h"
#include "userDef.h"
#include "eeprom.h"
#include "LighthouseJson.h"

void setup() {
  Serial.begin(57600);
  strip.begin();
  strip.setBrightness(BRIGHT_MAX);
  read_eeprom();
  if (mode < 0 || mode > 5 || colorNum < 0 || colorNum > 9)
  {
    mode = 1;
    colorNum = 5;
  }
#if DEBUG
  Serial.println("**************START************");
  Serial.print("MODE DATA:");
  Serial.println(mode);
  Serial.print("INDEX DATA:");
  Serial.println(colorNum);
  Serial.println("--------------");
#endif
  //每隔0.1秒换一种颜色，总共十种颜色。
  for (int i = 0; i < 10; i++)
  {
    setAllLed(i);
    delay(150);   //每个颜色持续时间
  }
}

void loop() {
  Lighthousejson_data();
  switch (mode)
  {
    case MODE_OFF:
      setAllLed(COLOR_NONE);
      break;
    case MODE_A:
      ledRainbow(20);            //彩虹效果，每种颜色持续20 ms。
      break;
    case MODE_B:
      ledBreath(COLOR_WARM, 10);
      break;
    case MODE_C:
      ledBreath(COLOR_COLD, 10);
      break;
    case MODE_D:
      setAllLed(colorNum);
      break;
    case MODE_E:
      ledBreath(colorNum, 10);
      break;
    default:
      break;
  }
}
