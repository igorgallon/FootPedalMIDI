
#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H

#include <Arduino.h>
#include <IRremoteInt.h>

class RemoteControl
{
  public:
    IRrecv* MyIrReceiver;

    enum Key
    {
      OnOff   = 0,
      Menu    = 1,
      Clock   = 2,
      Mute    = 3,
      Super   = 4,
      Up      = 5,
      Down    = 6,
      Left    = 7,
      Right   = 8,
      Num1    = 9,
      Num2    = 10,
      Num3    = 11,
      Num4    = 12,
      Num5    = 13,
      Num6    = 14,
      Num7    = 15,
      Num8    = 16,
      Num9    = 17,
      Num0    = 18,
      Num100  = 19,
      AV      = 20,
      Unknown = 21
    };

    RemoteControl(IRrecv * aIrReceiver);
    void initialize(int pinId);
    bool receive(Key *current);
  
  private:
    Key decodeKey(uint32_t rawData);

};

#endif