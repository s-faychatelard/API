//
//  main.c
//  RobotPOB
//
//  Created by Sylvain Fay-Châtelard, Baptiste Burles on 08/01/14.
//  Copyright (c) 2013 Dviance, Kliplab. All rights reserved.
//

#include <stdio.h>

#define DEVICE_XML "/Volumes/POB/project/foutoir-projet/API/NativeServer/test/sources/pob-devices.xml"

extern int startNativeServer(const char * xmlDevicesFile);

int main(void)
{
    
    printf("===> Native server for robot POB !\n");
    
    startNativeServer(DEVICE_XML);
    
    
}