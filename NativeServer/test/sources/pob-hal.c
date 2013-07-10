//
//  pob-hal.c
//  RobotPOB
//
//  Created by bburles on 10/07/13.
//  Copyright (c) 2013 Awabot. All rights reserved.
//

#include <stdio.h>
#include <pob/biglibpob.h>

#include "../../includes/nativeserver.h"

RProtocol * protocol;

short motorLeft = 0;
short motorRight = 0;
int servomotor = 0;

void setMotorSpeed(DeviceObject * device, Value * value)
{
//    printf("setSpeed value to write: %d (0x%x) to %s\n", value->integer, value->integer, device->name);
    
    if (strcmp("leftWheel", device->name)==0)
    {
        motorLeft = (short)value->integer;
    }
    else
    {
        motorRight = (short)value->integer;
    }
    
//    printf("l %d r %d s %d\n", motorLeft, motorRight, servomotor);
    
    RProtocolSendJoypad(protocol, motorLeft, motorRight, servomotor, 0, 0, 0, 0, 0);
    Wait(10);
}


void setServoPosition(DeviceObject * device, Value * value)
{
    servomotor = value->integer;
    RProtocolSendJoypad(protocol, motorLeft, motorRight, servomotor, 0, 0, 0, 0, 0);
    Wait(10);
}

int GetDistanceFromGP2D12AnalogValue(int value)
{
    int result;
    
    // see "docs/sharp-analog-distance.xlsx" for value and approximation.
    
    if( value > 527)
    {
        //       result = 263 - 0.215 * value;
        result = 263 - (55 * value) / 256;
    }
    else if( value > 341 && value <= 527)
    {
        //       result = 433 - 0.5376 * value;
        result = 433 - (137 * value) / 256;
    }
    else if( value > 207 && value <= 341)
    {
        //       result = 759 - 1.492 * value;
        result = 759 - (382 * value) / 256;
    }
    else if( value > 155 && value <= 207)
    {
        //       result = 1246 - 3.846 * value;
        result = 1246 - (984 * value) / 256;
    }
    else if( value <= 155)
    {
        //       result = 1511 - 5.555 * value;
        result = 1511 - (1422 * value) / 256;
    }
    
    return result;
}

void getDistanceSensor(DeviceObject * device, Value * value)
{
    RealTimeData realtime;
    
    RProtocolGetRealTimeData(protocol, &realtime);
    Wait(10);
    
//    value->integer = realtime.analogChannel[0];
    
//    printf("getDistanceSensor %d\n", realtime.analogChannel[0]);
    
    value->integer = GetDistanceFromGP2D12AnalogValue((realtime.analogChannel[0]<<2));
}

void initUserCallback(void)
{
    addUserDeviceAction(setMotorSpeed, "setSpeed", "devices.Motor");
    addUserDeviceAction(setServoPosition, "setPosition", "devices.Servo");
    addUserDeviceAction(getDistanceSensor, "getDistance", "devices.DistanceSensor");
    
    
    protocol = RProtocolNew(False);
    
    if( protocol->detect(protocol)==False)
    {
        RProtocolDelete(protocol);
        printf("No wireless (Wifi) robot detected on your Wifi network !\n");
        
        return;
    }
    else
    {
        printf("Connected on robot %s !\n", protocol->robots[0].name);
        
        protocol->wificonf->ip = protocol->robots[0].ip;
    }
    
    RProtocolOpen(protocol);
    
 /*   Value v;
    
    v.integer = 90;
    setServoPosition(0,&v);
    Wait(300);
    
    while(1)
    {
        getDistanceSensor(0,&v);
        if (v.integer<300)
        {
            motorLeft = 0;
            motorRight = 0;
            RProtocolSendJoypad(protocol, motorLeft, motorRight, servomotor, 0, 0, 0, 0, 0);
            
            
            v.integer = 0;
            setServoPosition(0, &v);
            Wait(500);
            
            getDistanceSensor(0, &v);
            if (v.integer<300)
            {
                v.integer = 180;
                setServoPosition(0, &v);
                Wait(500);
            
                getDistanceSensor(0, &v);
                if (v.integer<300)
                {
                    motorLeft = -100;
                    motorRight = -100;
                    RProtocolSendJoypad(protocol, motorLeft, motorRight, servomotor, 0, 0, 0, 0, 0);
                    Wait(1000);
                }
                else
                {
                    motorLeft = -100;
                    motorRight = 100;
                    RProtocolSendJoypad(protocol, motorLeft, motorRight, servomotor, 0, 0, 0, 0, 0);
                    Wait(1000);
                }
            }
            else
            {
                motorLeft = 100;
                motorRight = -100;
                RProtocolSendJoypad(protocol, motorLeft, motorRight, servomotor, 0, 0, 0, 0, 0);
                Wait(1000);
            }
            
            v.integer = 90;
            setServoPosition(0,&v);
            Wait(300);
        }
        else
        {
            motorLeft = 100;
            motorRight = 100;
            RProtocolSendJoypad(protocol, motorLeft, motorRight, servomotor, 0, 0, 0, 0, 0);
            Wait(100);
        }
        
        
        
    }*/
    
    
}
