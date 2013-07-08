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

void writeGetTableCommand(ByteStream * stream, Device * devices, unsigned int deviceNumber)
{
    unsigned int index = 0;
    unsigned int sizeTotal = 0;
    
    unsigned int nameSize;
    
    Device *	dev =  (Device *)&devices[0];
    DevicePhysical * physical;
    
    // 4 magic
    // 4 size total
    // 1 command
    // 4 device number
    write4ToByteStream(stream, PROTOCOL_MAGIC);
    write4ToByteStream(stream, 0);
    write1ToByteStream(stream, COMMAND_GET_TABLE);
    write4ToByteStream(stream, deviceNumber);
    
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
    
    sizeTotal = sizeTotal - 8;
    set4ToBuffer(stream->buffer+4, sizeTotal);
    
//    printf("writeGetTableCommand: sizeTotal %d\n", sizeTotal);
    
    
}


void readSendCommand(ByteStream * stream, Device * devices)
{
    unsigned char deviceName[255];
    unsigned char actionName[255];
    
    unsigned int deviceSize, actionSize;
    int value;
    
    Device * device;
    DeviceAction * action;
    
    memset(deviceName,0, 255);
    memset(actionName,0, 255);
    
    // 4 device name size
    // ... device name
    deviceSize = read4FromByteStream(stream);
    readBufferFromByteStream(stream, deviceName, deviceSize);
    
    // 4 action name size
    // ... action name
    
    actionSize = read4FromByteStream(stream);
    readBufferFromByteStream(stream, actionName, actionSize);
    
    // 4 value
    value = (int)read4FromByteStream(stream);
    
//    printf("Device %s Action %s Value %d\n", deviceName, actionName, value);
    
    device = getDeviceByName(devices, deviceName, deviceSize);
    
    if (device == 0)
    {
        return;
    }
    
    action = getDeviceActionByName(device,actionName,actionSize);
    
    if (action==0)
    {
        return;
    }
    
    printf("-> execute on %s.%s = %d\n", device->name, action->name, value);
    
    //todo select correct value in Value struct
    
    Value v;
    v.integer = value;
    action->action(device, &v);
    
    // todo if read action, send back value of structure
    
    
}


