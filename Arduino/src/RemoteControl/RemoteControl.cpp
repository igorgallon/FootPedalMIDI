/*
 * RemoteControl.cpp
 *
 *  Created on: 07/09/2021
 *      Author: Igor Gallon
 */

#include "RemoteControl.h"

RemoteControl::RemoteControl(IRrecv * aIrReceiver)
{
  MyIrReceiver = aIrReceiver;
}

void RemoteControl::initialize(int pinId)
{
  MyIrReceiver->begin(pinId, DISABLE_LED_FEEDBACK);
}

RemoteControl::Key RemoteControl::decodeKey(uint32_t rawData)
{
  switch(rawData)
  {
    case 3977428800:
      return Key::OnOff;
    case 4044275520:
      return Key::Menu;
    case 3810312000:
      return Key::Clock;
    case 4010852160:
      return Key::Mute;
    case 3960717120:
      return Key::Super;
    case 3827023680:
      return Key::Up;
    case 3760176960:
      return Key::Down;
    case 3776888640:
      return Key::Left;
    case 3843735360:
      return Key::Right;
    case 4261527360:
      return Key::Num1;
    case 4244815680:
      return Key::Num2;
    case 4228104000:
      return Key::Num3;
    case 4211392320:
      return Key::Num4;
    case 4194680640:
      return Key::Num5;
    case 4177968960:
      return Key::Num6;
    case 4161257280:
      return Key::Num7;
    case 4144545600:
      return Key::Num8;
    case 4127833920:
      return Key::Num9;
    case 4278239040:
      return Key::Num0;
    case 4111122240:
      return Key::Num100;
    case 3944005440:
      return Key::AV;
    default:
      return Key::Unknown;
  }
}

bool RemoteControl::receive(Key *current)
{
  if(MyIrReceiver->decode())
  {
    (*current) = decodeKey(MyIrReceiver->decodedIRData.decodedRawData);
    delay(150);
    MyIrReceiver->resume(); // Receive the next value

    if((*current) != Key::Unknown)
      return true;
  }

  return false;
}
