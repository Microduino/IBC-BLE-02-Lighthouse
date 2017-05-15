#include <EEPROM.h>

//EEPROM配置
#define EEPROM_write(address, p) {int i = 0; byte *pp = (byte*)&(p);for(; i < sizeof(p); i++) EEPROM.write(address+i, pp[i]);}
#define EEPROM_read(address, p)  {int i = 0; byte *pp = (byte*)&(p);for(; i < sizeof(p); i++) pp[i]=EEPROM.read(address+i);}

int mode = 1;
int colorNum = 1;

struct config_type
{
  int EEPROMmode;
  int EEPROMindex;
};

void read_eeprom() {
  config_type config_readback;
  EEPROM_read(0, config_readback);
  mode = config_readback.EEPROMmode;
  colorNum = config_readback.EEPROMindex;
}

void write_eeprom() {
  config_type config;                  // 定义结构变量config，并定义config的内容
  config.EEPROMmode = mode;
  config.EEPROMindex = colorNum;
  EEPROM_write(0, config);         // 变量config存储到EEPROM，地址0写入
}
