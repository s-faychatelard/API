//
//  protocol.c
//  NativeServer
//
//  Created by bburles on 05/07/13.
//  Copyright (c) 2013 Dviance. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "../includes/bytestream.h"
#include "../includes/devices.h"
#include "../includes/protocol.h"



void writeActionTable(ByteStream * stream, DeviceAction * actions)
{
    DeviceAction *	ptr =  (DeviceAction *)&actions[0];
	unsigned int index = 0;
    unsigned int size;
    
    while (ptr->type != ACTION_UNKNONW)
	{
        // action:
        //      1 type action
        //      1 type value
        //      4 size
        //      ... name
        
        size = (unsigned int)strlen(ptr->name);
        
        write1ToByteStream(stream, ptr->type);
        write1ToByteStream(stream, ptr->valueType);
        write4ToByteStream(stream, size);
        writeBufferToByteStream(stream, (unsigned char *)ptr->name, size);
        
		index++;
		ptr = (DeviceAction *)&actions[index];
	}
    
}

void writeGetTableCommand(ByteStream * stream, Device * devices)
{
    unsigned int index = 0;
    unsigned int sizeTotal = 0;
    
    unsigned int nameSize;
    
    Device *	dev =  (Device *)&devices[0];
    DevicePhysical * physical;
    
    // 4 magic
    // 4 size total
    // 1 command
    write4ToByteStream(stream, PROTOCOL_MAGIC);
    write4ToByteStream(stream, 0);
    write1ToByteStream(stream, COMMAND_GET_TABLE);
    
    // payload :
    while (dev->device != 0)
	{
        // get table
        // 4 size
        // ... name
        
        nameSize = (unsigned int)strlen(dev->name);
        
        write4ToByteStream(stream, nameSize);
        writeBufferToByteStream(stream, (unsigned char *)dev->name, nameSize);
        
        physical = dev->device;
        
        // 4 size
        // ... type
        
        nameSize = (unsigned int)strlen(physical->type);
        
        write4ToByteStream(stream, nameSize);
        writeBufferToByteStream(stream, (unsigned char *)physical->type, nameSize);
        
        physical = dev->device;
        
        // 4 action number
        write4ToByteStream(stream, physical->number);
        
        writeActionTable(stream, physical->actions);
        

		index++;
		dev = (Device *)&devices[index];
	}
    
    sizeTotal = getByteStreamSize(stream);
    
    
}