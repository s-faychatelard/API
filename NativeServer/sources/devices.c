//
//  devices.c
//  NativeServer
//
//  Created by bburles on 05/07/13.
//  Copyright (c) 2013 Dviance. All rights reserved.
//

#include <stdio.h>

#include "../includes/devices.h"


unsigned int initDeviceAction(DeviceAction *actions)
{
    DeviceAction *	ptr =  (DeviceAction *)&actions[0];
	unsigned int index = 0;
    
    while (ptr->type != ACTION_UNKNONW)
	{
        if (ptr->hash==0)
        {
            ptr->hash = hash32((unsigned char *)ptr->name, strlen(ptr->name));
		}
        
        printf("\tAction %s: 0x%x\n", ptr->name, ptr->hash);
        
		index++;
		ptr = (DeviceAction *)&actions[index];
	}
    
    return index;
}

void initDevicesTable(Device devices[])
{
    Device *	ptr =  (Device *)&devices[0];
    DevicePhysical * physical;
	unsigned int index = 0;
    unsigned int size;
    
    while (ptr->device != 0)
	{
        ptr->hash = hash32((unsigned char *)ptr->name, strlen(ptr->name));
		
        physical = ptr->device;
        if (physical->hash==0)
        {
            physical->hash = hash32(physical->type, strlen(physical->type));
        }
        
        printf("Device %s: 0x%x, type %s\n", ptr->name, ptr->hash, physical->type);
        
        size = initDeviceAction(physical->actions);
        
        printf("Size of action: %d\n", size);
        
        physical->number = size;
        
		index++;
		ptr = (Device *)&devices[index];
	}
    
}

