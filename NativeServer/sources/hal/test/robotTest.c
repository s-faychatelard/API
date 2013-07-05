//
//  robotTest.c
//  NativeServer
//
//  Created by bburles on 05/07/13.
//  Copyright (c) 2013 Dviance. All rights reserved.
//

#include <stdio.h>


#include "../../../includes/devices.h"


void setSpeed(Device * device, Value * value)
{
    printf("setSpeed value to write: %d (0x%x) to %s\n", value->integer, value->integer, device->name);
}

DeviceAction motorAction[] =
{
    { ACTION_WRITE, VALUE_INTEGER, "setSpeed", 0x00,   &setSpeed },
    { 0,            VALUE_UNKNONW, 0,          0,      0 }
};

DevicePhysical motor =
{
    "devices.Motor", 0x00, 0, motorAction
};

void setAngle(Device * device, Value * value)
{
    printf("setAngle value to write: %d (0x%x) to %s\n", value->integer, value->integer, device->name);
}

DeviceAction servoAction[] =
{
    { ACTION_WRITE, VALUE_INTEGER, "setAngle", 0x00,   &setAngle },
    { 0,            VALUE_UNKNONW, 0,          0,      0 }
};

DevicePhysical servo =
{
    "devices.Servo", 0x00, 0, servoAction
};


Device robotDevices[] =
{
    { "leftWheel",      0x00,           &motor },
    { "rightWheel",     0x00,           &motor },
//    { "servoPourDancerLaZoumba", 0x00,  &servo },
//    { "servoHead",      0x00,           &servo },
    {   0,              0x00,           0 }
};
