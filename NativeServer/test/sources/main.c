//
//  main.c
//  RobotPOB
//
//  Created by bburles on 10/07/13.
//  Copyright (c) 2013 Awabot. All rights reserved.
//

#include <stdio.h>

#define DEVICE_XML "/Volumes/POB/project/foutoir-projet/API/NativeServer/test/sources/pob-devices.xml"

extern int startNativeServer(const char * xmlDevicesFile);

int main(void)
{
    
    printf("===> Native server for robot POB !\n");
    
    startNativeServer(DEVICE_XML);
    
    
}