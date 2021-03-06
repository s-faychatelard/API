//
//  robotTest.c
//  NativeServer
//
//  Created by Sylvain Fay-Châtelard, Baptiste Burles on 08/01/14.
//  Copyright (c) 2013 Dviance, Kliplab. All rights reserved.
//

#include <stdio.h>

#include "../../../includes/list.h"
#include "../../../includes/devices.h"
#include "../../../includes/robot-hal.h"


void setMotorSpeed(DeviceObject * device, Value * value)
{
    printf("setSpeed value to write: %d (0x%x) to %s\n", value->integer, value->integer, device->name);
}


void getServoPosition(DeviceObject * device, Value * value)
{
    printf("getServoPosition for %s size wanted: %d\n", device->name, value->wantedSize);
    
    value->integer = 12345678;
}

void initUserCallback(void)
{
    addUserDeviceAction(setMotorSpeed, "setSpeed", "devices.Motor");
    addUserDeviceAction(getServoPosition, "getPosition", "devices.Servo");
}
