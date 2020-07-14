#include <Arduino.h>
#include <HardwareSerial.h>
#include "PS4Serial.h"

PS4Serial::PS4Serial(){};

void PS4Serial::setPort(HardwareSerial *port)
{
    _port = port; //Set serial port
    _port->begin(57600);
}

bool PS4Serial::getButton(Button button)
{
    if (millis() - last_time >= loop_time)
    {
        last_time = millis();
        unpack(); //Unpack data before return
    }
    switch (button)
    {
    //*****Left Button*****//
    case PS4B_UP:
        return button_left.asBool.bit0;
        break;
    case PS4B_Right:
        return button_left.asBool.bit1;
        break;
    case PS4B_Down:
        return button_left.asBool.bit2;
        break;
    case PS4B_Left:
        return button_left.asBool.bit3;
        break;
    case PS4B_L1:
        return button_left.asBool.bit4;
        break;
    case PS4B_Share:
        return button_left.asBool.bit5;
        break;
    case PS4B_L3:
        return button_left.asBool.bit6;
        break;

    //*****Right Button*****//
    case PS4B_Triangle:
        return button_right.asBool.bit0;
        break;
    case PS4B_Circle:
        return button_right.asBool.bit1;
        break;
    case PS4B_Cross:
        return button_right.asBool.bit2;
        break;
    case PS4B_Square:
        return button_right.asBool.bit3;
        break;
    case PS4B_R1:
        return button_right.asBool.bit4;
        break;
    case PS4B_Options:
        return button_right.asBool.bit5;
        break;
    case PS4B_R3:
        return button_right.asBool.bit6;
        break;
    case PS4B_Touch:
        return button_right.asBool.bit7;
        break;

    default:
        break;
    }
}

uint8_t PS4Serial::getAnalog(Axis axis)
{
    if (millis() - last_time >= loop_time)
    {
        last_time = millis();
        unpack(); //Unpack data before return
    }
    switch (axis)
    {
    //*****Left Analog*****//
    case PS4A_Lx:
        return joyAnalog_Lx;
        break;
    case PS4A_Ly:
        return joyAnalog_Ly;
        break;
    case PS4A_L2:
        return joyAnalog_L2;
        break;

    //*****Right Analog*****//
    case PS4A_Rx:
        return joyAnalog_Rx;
        break;
    case PS4A_Ry:
        return joyAnalog_Ry;
        break;
    case PS4A_R2:
        return joyAnalog_R2;
        break;
    }
}

void PS4Serial::unpack(void)
{
    counter = 0;
    while (_port->available())
    {
        buffer[counter++] = _port->read();
        if (counter == 0 && buffer[0] != '#')
            counter = 0;
        if ((buffer[counter - 11] == '#') && (buffer[counter - 10] == 's') && (buffer[counter - 1] == '\r') && (buffer[counter] == '\n'))
        {
            joyAnalog_Lx = buffer[counter - 9];
            joyAnalog_Ly = buffer[counter - 8];
            joyAnalog_L2 = buffer[counter - 7];
            joyAnalog_Rx = buffer[counter - 6];
            joyAnalog_Ry = buffer[counter - 5];
            joyAnalog_R2 = buffer[counter - 4];
            button_left.asByte = buffer[counter - 3];
            button_right.asByte = buffer[counter - 2];
            break;
        }
        if (counter >= (buff_len * 2))
            counter = 0;
    }
}
