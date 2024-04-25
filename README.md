Arduino.ino = Arduino sample code
NodeMCU.ino = NodeMCU sample code
ardToNode.h = header file

ardToNode.h:
NOTHING TO CHANGE, ONLY CONTAINS ESP CLASS FOR SERIAL CONNECTION AND WRITE FUNCTION


Arduino.ino:
#include "ardToEsp.h" -- to include header file

#define RXPIN
#define TXPIN -- to define the software serial pins (can be used for both DIGITAL and ANALOG pins)

extern ESP serialESP(RXPIN, TXPIN, 9600); -- Create serialESP object, uses RXPIN and TXPIN as attributes, and baudrate (default 9600, change if needed)

String value = "Distance: " + String(distance) + "\n"; -- !!SAMPLE ONLY!! define data to be sent to NodeMCU, must be concatonated to one variable, both STRING and INT
serialESP.writeStr(value); -- use .writeStr() to send with STRING types, and .writeInt() to send with INT types


NodeMCU.ino:

Serial.begin(9600); -- make sure baud rates for both ESP8266 serial and SoftwareSerial is the same!

readSerial(){} -- function to decode and return the data of the SoftwareSerial into readable text/string

String value = readSerial(); -- reads the current entry of the serial, will return empty if there is NONE
if (value != "") Serial.print(value); -- only read data when the serial is NOT NONE

