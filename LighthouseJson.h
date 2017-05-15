#include <aJSON.h>
aJsonStream serial_stream(&Serial);

String modeS = "";
String colorNumS = "";
String projtctid = "";

String ID = "{\"ID\":\"590bc5e87bb3e300016e2d9e\"}";

#define  MODE_OFF     0
#define  MODE_A       1
#define  MODE_B       2
#define  MODE_C       3
#define  MODE_D       4
#define  MODE_E       5

//{"ID":"project"}
void IDupload()
{
  Serial.print(ID.substring(0, 17));
  delay(30);
  Serial.println(ID.substring(17, 33));
  delay(30);
}

void Ctrldata(String _st, int _data)
{
  String send_data;
  int number;
  send_data = "{\"";
  send_data += _st;
  send_data += "\":\"";
  send_data += _data;
  send_data += "\"\}";
  number = send_data.length() / 17;

  if (number == 0)
  {
    Serial.println(send_data);
    delay(30);
  }
  else
  {
    while (number >= 0)
    {
      Serial.print(send_data.substring(0, 17));
      send_data = send_data.substring(17, send_data.length());
      delay(30);
      number--;
    }
    Serial.print("\n");
  }
}

//{"mode":"1"}
//{"colorIndex":"1"}
void ComExecution(aJsonObject *msg)
{
  aJsonObject *IDval = aJson.getObjectItem(msg, "ID");
  if (IDval) {
    projtctid = IDval->valuestring;
    if (projtctid == "project")
    {
      IDupload();
      Ctrldata("colorIndex", colorNum);
    }
  }
  else {
#if DEBUG
    Serial.println("no ID data");
#endif
  }

  aJsonObject *modeval = aJson.getObjectItem(msg, "mode");
  if (modeval) {
    modeS  = modeval->valuestring;
    if (modeS != "-1")
      mode = modeS.toInt();
    write_eeprom();
  }
  else {
#if DEBUG
    Serial.println("no mode data");
#endif
  }
  aJsonObject *indexval = aJson.getObjectItem(msg, "colorIndex");
  if (indexval) {
    colorNumS  = indexval->valuestring;
    colorNum = colorNumS.toInt();
    write_eeprom();
  }
  else {
#if DEBUG
    Serial.println("no colorIndex data");
#endif
  }

#if DEBUG
  Serial.println("--------------");
  Serial.print("MODE DATA:");
  Serial.println(mode);
  Serial.print("INDEX DATA:");
  Serial.println(colorNum);
  Serial.println("--------------");
#endif
}

void Lighthousejson_data()
{
  if (serial_stream.available()) {
    serial_stream.skip();
  }
  if (serial_stream.available()) {
    aJsonObject *msg = aJson.parse(&serial_stream);
    ComExecution(msg);
    aJson.deleteItem(msg);
  }
}
