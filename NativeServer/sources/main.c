//
//  main.c
//  NativeServer
//
//  Created by Sylvain Fay-Châtelard, Baptiste Burles on 08/01/14.
//  Copyright (c) 2013 Dviance, Kliplab. All rights reserved.
//

#include "../includes/nativeserver.h"

#define DEVICE_XML  "../../../../../../../devices.xml"



int main(void)
{
    startNativeServer(DEVICE_XML);
    return 0;
}