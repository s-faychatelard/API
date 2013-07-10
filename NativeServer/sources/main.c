//
//  main.c
//  NativeServer
//
//  Created by bburles on 05/07/13.
//  Copyright (c) 2013 Awabot. All rights reserved.
//

#include "../includes/nativeserver.h"

#define DEVICE_XML  "../../../../../../../devices.xml"



int main(void)
{
    startNativeServer(DEVICE_XML);
    return 0;
}