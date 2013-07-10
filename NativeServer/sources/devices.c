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
    Device *	ptr;
    DevicePhysical * physical;
	unsigned int index = 0;
    unsigned int size;
    
    ListNode *n = devices->first;
    while (n != NULL)
    {
        ptr = (Device *)n->data;
        ptr->hash = hash32((unsigned char *)ptr->name, (unsigned int)strlen(ptr->name));
		
        physical = ptr->device;
        if (physical->hash==0)
        {
            physical->hash = hash32((unsigned char *)physical->type, (unsigned int)strlen(physical->type));
        }
        
        printf("Device %s: 0x%x, type %s\n", ptr->name, ptr->hash, physical->type);
        
        size = initDeviceAction(&physical->actions);
        
        printf("Size of action: %d\n", size);
        
        
		index++;
		n = n->next;
	}
    
    return index;
}


Device * getDeviceByName(List * devices, unsigned char * name, unsigned int nameSize)
{
    Device *	ptr;
    
    ListNode *n = devices->first;
    while (n != NULL)
    {
        ptr = (Device *)n->data;
        
        if (strncmp(ptr->name, (const char *)name, nameSize)==0)
        {
            return ptr;
        }
        
		n = n->next;
	}
    
    return 0;
}

DevicePhysical * getDevicePhysicalByName(List * physicals, const char * name)
{
    DevicePhysical * ptr;
    ListNode *n = physicals->first;
    while (n != NULL)
    {
        ptr = (DevicePhysical *)n->data;
    
        if (strcmp(name,ptr->type)==0)
        {
            return ptr;
        }
        
        n = n->next;
    }
    
    return 0;
}

DeviceAction * getDeviceActionByName(Device * device, unsigned char * name, unsigned int nameSize)
{
    DevicePhysical * physical = device->device;
    List * actions = &physical->actions;
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
