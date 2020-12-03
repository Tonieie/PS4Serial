#ifndef PS4Serial_h
#define PS4Serial_h

#include <Arduino.h>
#include <HardwareSerial.h>

//These are button constant
#define PSB_Triangle 0x01
#define PSB_Circle 0x02
#define PSB_Cross 0x03
#define PSB_Square 0x04
#define PSB_Up 0x05
#define PSB_Right 0x06
#define PSB_Down 0x07
#define PSB_Left 0x08
#define PSB_R1 0x09
#define PSB_R3 0x0A
#define PSB_L1 0x0B
#define PSB_L3 0x0C
#define PSB_Options 0x0D
#define PSB_Share 0x0E
#define PSB_Touch 0x0F

//These are analog button constant
#define PSA_Lx 0x10
#define PSA_Ly 0x20
#define PSA_L2 0x30
#define PSA_Rx 0x40
#define PSA_Ry 0x50
#define PSA_R2 0x60
#define PSA_Touch_X 0x70
#define PSA_Touch_Y 0x80

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

    union IntToByte
    {
        uint16_t asInt;
        uint8_t asByte[2];
    };

public:
    enum Button
    {
        PS4B_Triangle = 1,
        PS4B_Circle,
        PS4B_Cross,
        PS4B_Square,
        PS4B_Up,
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

    bool getButton(Button button);      //Get Button state For VS Code Programmer
    bool getButton(uint8_t button);           //Get Button state For Arduino IDE Programmer

    uint8_t getAnalog(Axis axis);       //Get Analog value For VS Code Programmer
    uint8_t getAnalog(uint8_t axis);        //Get Analog value For Arduino IDE Programmer

    bool isConnected(void);
    bool isTouching(bool finger);
    uint16_t getX(bool finger);
    uint16_t getY(bool finger);

private:
    HardwareSerial *_port = NULL;
    uint8_t buff_len = 21;
    uint32_t last_time = 0, loop_time = 10; //Set loop frequency to 100 Hz
    volatile uint8_t buffer[42];            //buffer size = data_len * 2
    volatile uint8_t counter = 0;
    Boolconv button_left, button_right, button_center;
    IntToByte touch_x1,touch_y1,touch_x2,touch_y2;
    uint8_t joyAnalog_Lx = 0, joyAnalog_Ly = 0, joyAnalog_L2 = 0, joyAnalog_Rx = 0, joyAnalog_Ry = 0, joyAnalog_R2 = 0;

    void unpack(void);
};

#endif