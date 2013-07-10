//
//  main.c
//  NativeServer
//
//  Created by bburles on 05/07/13.
//  Copyright (c) 2013 Awabot. All rights reserved.
//

#define DEVICE_XML  "../../../../../../../devices.xml"

extern int startNativeServer(const char * xmlDevicesFile);

int main(void)
{
    startNativeServer(DEVICE_XML);
    return 0;
}