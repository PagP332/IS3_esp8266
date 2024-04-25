#include <string>
#include <optional>

String data, returnStr;
String readSerial(){
  if (Serial.available() != 0){
      char value = Serial.read();
      // Decode Software Serial return bytes
      data += value;
      if(value == '\n'){
        returnStr = data;
        data = "";
        return returnStr;
      }
    }
 return "";
}

void setup() {
  Serial.begin(9600);
}
void loop() {
  String value = readSerial();
  if (value != "") Serial.print(value);
}
