#include <PS4Serial.h>
PS4Serial joy;
void setup()
{
  joy.setPort(&Serial);
}

void loop()
{
    joy.getButton(PSB_Cross);
}
