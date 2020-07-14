#ifndef PS4Serial_h
#define PS4Serial_h

#include <Arduino.h>
#include <HardwareSerial.h>

class PS4Serial
{
    union Boolconv //Union data for convertion between byte and bit
    {
        unsigned char asByte;
        struct asBool
        {
            unsigned int bit0 : 1;
            unsigned int bit1 : 1;
            unsigned int bit2 : 1;
            unsigned int bit3 : 1;
            unsigned int bit4 : 1;
            unsigned int bit5 : 1;
            unsigned int bit6 : 1;
            unsigned int bit7 : 1;

        } asBool;
    };

public:
    enum Button
    {
        PS4B_Triangle = 1,
        PS4B_Circle,
        PS4B_Cross,
        PS4B_Square,
        PS4B_UP,
        PS4B_Right,
        PS4B_Down,
        PS4B_Left,
        PS4B_R1,
        PS4B_R3,
        PS4B_L1,
        PS4B_L3,
        PS4B_Options,
        PS4B_Share,
        PS4B_Touch,
    };

    enum Axis
    {
        PS4A_Lx = 1,
        PS4A_Ly,
        PS4A_L2,
        PS4A_Rx,
        PS4A_Ry,
        PS4A_R2,
        PS4A_Touch_X,
        PS4A_Touch_Y,
    };
    PS4Serial(void);
    void setPort(HardwareSerial *port); //Set Serial port
    bool getButton(Button button); //Get Button state
    uint8_t getAnalog(Axis axis); //Get Analog value

private:
    HardwareSerial *_port = NULL;
    uint8_t buff_len = 12;
    uint32_t last_time = 0, loop_time = 10; //Set loop frequency to 100 Hz
    volatile uint8_t buffer[24]; //buffer size = data_len * 2
    volatile uint8_t counter = 0;
    Boolconv button_left, button_right;
    uint8_t joyAnalog_Lx = 0, joyAnalog_Ly = 0, joyAnalog_L2 = 0, joyAnalog_Rx = 0, joyAnalog_Ry = 0, joyAnalog_R2 = 0;

    void unpack(void);
};

#endif