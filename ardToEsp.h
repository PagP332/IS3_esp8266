#include <SoftwareSerial.h>

class ESP{
  private:
    int rxPin;
    int txPin;
    int baud;
    SoftwareSerial espSerial;

  public:
  ESP(int rx, int tx, int baud) : rxPin(rx), txPin(tx), baud(baud), espSerial(rxPin, txPin){
    espSerial.begin(baud);
  }
  
  void writeInt(int data){
    espSerial.print(data);
  }

  void writeStr(String data){
    espSerial.print(data);
  }
};