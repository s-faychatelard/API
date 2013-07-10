//
//  devices.c
//  NativeServer
//
//  Created by bburles on 05/07/13.
//  Copyright (c) 2013 Awabot. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes/list.h"
#include "../includes/devices.h"
#include "../includes/utils.h"

unsigned int initDeviceAction(List *actions)
{
    DeviceAction *	ptr;
	unsigned int index = 0;
    
    ListNode *n = actions->first;
    while (n != NULL)
    {
        ptr = (DeviceAction *)n->data;
        
        if (ptr->hash==0)
        {
            ptr->hash = hash32((unsigned char *)ptr->name, (unsigned int)strlen(ptr->name));
		}
        
        printf("\tAction %s: 0x%x\n", ptr->name, ptr->hash);
        
        index++;
        n = n->next;
    }
    
    return index;
}



unsigned int initDevicesTable(List * devices)
{
    DeviceObject *	ptr;
    DeviceHardware * hw;
	unsigned int index = 0;
    unsigned int size;
    
    ListNode *n = devices->first;
    while (n != NULL)
    {
        ptr = (DeviceObject *)n->data;
        ptr->hash = hash32((unsigned char *)ptr->name, (unsigned int)strlen(ptr->name));
		
        hw = ptr->hardware;
        if (hw->hash==0)
        {
            hw->hash = hash32((unsigned char *)hw->type, (unsigned int)strlen(hw->type));
        }
        
        printf("Device %s: 0x%x, type %s\n", ptr->name, ptr->hash, hw->type);
        
        size = initDeviceAction(&hw->actions);
        
        printf("Size of action: %d\n", size);
        
        
		index++;
		n = n->next;
	}
    
    return index;
}


DeviceObject * getDeviceByName(List * devices, unsigned char * name, unsigned int nameSize)
{
    DeviceObject *	ptr;
    
    ListNode *n = devices->first;
    while (n != NULL)
    {
        ptr = (DeviceObject *)n->data;
        
        if (strncmp(ptr->name, (const char *)name, nameSize)==0)
        {
            return ptr;
        }
        
		n = n->next;
	}
    
    return 0;
}

DeviceHardware * getDevicePhysicalByName(List * physicals, const char * name)
{
    DeviceHardware * ptr;
    ListNode *n = physicals->first;
    while (n != NULL)
    {
        ptr = (DeviceHardware *)n->data;
    
        if (strcmp(name,ptr->type)==0)
        {
            return ptr;
        }
        
        n = n->next;
    }
    
    return 0;
}

DeviceAction * getDeviceActionByName(DeviceObject * device, unsigned char * name, unsigned int nameSize)
{
    DeviceHardware * hw = device->hardware;
    List * actions = &hw->actions;
    DeviceAction *	ptr;
    
    ListNode *n = actions->first;
    while (n != NULL)
    {
        ptr = (DeviceAction *)n->data;
        
        if (strncmp(ptr->name, (const char *)name, nameSize)==0)
        {
            return ptr;
        }
        
        n = n->next;
    }
    
    return 0;
}
