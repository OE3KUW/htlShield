/******************************************************************
                        all inits
                                                    қuran nov 2022
******************************************************************/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "init.h"
#include "mfc.h"


void initMFC(void)
{
    Wire.beginTransmission(MFS);
    Wire.write(0x02);        // select mode register
    Wire.write(0x00);        // continuous measurement mode
    Wire.endTransmission();
}



int getMFC(int * x, int * y, int * z)
{
    int akn;
    int angleXY, angleYZ, angleZX;

    Wire.beginTransmission(MFS);
    Wire.write(0x03);
    akn = Wire.endTransmission();

    Wire.requestFrom(MFS, 6);
    if (6 <= Wire.available())
    {
        *x =  Wire.read() << 8; *x |= Wire.read();
        *z =  Wire.read() << 8; *z |= Wire.read();
        *y =  Wire.read() << 8; *y |= Wire.read();
    }

    angleXY = atan2(*y, *x) * 180 / M_PI;
    if (angleXY < 0) angleXY += 360;

    angleYZ = atan2(*z, *y) * 180 / M_PI;
    if (angleYZ < 0) angleYZ += 360;

    angleZX = atan2(*x, *z) * 180 / M_PI;
    if (angleZX < 0) angleZX += 360;

    *x = angleXY;
    *y = angleYZ;
    *z = angleZX;


    return akn;
}
