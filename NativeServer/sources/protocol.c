//
//  protocol.c
//  NativeServer
//
//  Created by bburles on 05/07/13.
//  Copyright (c) 2013 Awabot. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "../includes/list.h"
#include "../includes/bytestream.h"
#include "../includes/devices.h"
#include "../includes/protocol.h"

//----------------------------- private functions

static void writeProtocolHeader(ByteStream * stream, NetworkCommand command)
{
    write4ToByteStream(stream, PROTOCOL_MAGIC);
    write4ToByteStream(stream, 0);
    write1ToByteStream(stream, command);
}

static void writeProtocolHeaderSize(ByteStream * stream)
{
    unsigned int sizeTotal = getByteStreamSize(stream);
    
    sizeTotal = sizeTotal - 8;
    set4ToBuffer(stream->buffer+4, sizeTotal);
}

static void writeActionTable(ByteStream * stream, List * actions)
{
    DeviceAction *	ptr;
    unsigned int size;
    
    ListNode *n = actions->first;
    while (n != NULL)
    {
        ptr = (DeviceAction *)n->data;
        
        // action:
        //      1 type action (read / write)
        //      1 type value (integer, float, array)
        //      4 size
        //      ... name
        
        size = (unsigned int)strlen(ptr->name);
        
        write1ToByteStream(stream, ptr->type);
        write1ToByteStream(stream, ptr->valueType);
        write4ToByteStream(stream, size);
        writeBufferToByteStream(stream, (unsigned char *)ptr->name, size);
        
        n = n->next;
	}
    
}

//----------------------------- public functions

void writeGetTableCommand(ByteStream * stream, List * devices)
{
    unsigned int nameSize;
    
    Device *	dev;
    DevicePhysical * physical;
    
    // 4 magic
    // 4 size total
    // 1 command
    // 4 device number
    writeProtocolHeader(stream,COMMAND_GET_TABLE);
    write4ToByteStream(stream, devices->size);
    
    // payload :
    ListNode *n = devices->first;
    while (n != NULL)
    {
        dev = (Device *)n->data;
        
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
        write4ToByteStream(stream, physical->actions.size);
        
        writeActionTable(stream, &physical->actions);
        

		n = n->next;
	}
    
    writeProtocolHeaderSize(stream);
    
//    printf("writeGetTableCommand: sizeTotal %d\n", sizeTotal);
    
    
}


void execCommand(NetworkCommand command, ByteStream * stream, ByteStream * output ,List * devices)
{
    unsigned char deviceName[255];
    unsigned char actionName[255];
    
    unsigned int deviceSize, actionSize;
    int value;
    
    Device * device;
    DeviceAction * action;
    
    Value v;
    
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
    
    if (command==COMMAND_SEND)
    {
        // 4 value
        value = (int)read4FromByteStream(stream);
        
        //todo select correct value in Value struct
        
        v.integer = value;
    }
    
//    printf("Device %s Action %s Value %d\n", deviceName, actionName, value);
    
    device = getDeviceByName(devices, deviceName, deviceSize);
    
    if (device == 0)
    {
        printf("execCommand: device %s not found\n", deviceName);
        return;
    }
    
    action = getDeviceActionByName(device,actionName,actionSize);
    
    if (action==0)
    {
        printf("execCommand: action %s not found\n", actionName);
        return;
    }
    
    printf("-> execute on %s.%s = %d\n", device->name, action->name, value);
    
    if (action->action!=0)
    {
        action->action(device, &v);
    }
    
    if (command==COMMAND_GET)
    {
        // it's a read order, send back value
        
        // 4 magic
        // 4 size total
        // 1 command
        // 4 value
        writeProtocolHeader(output, COMMAND_SEND);
        write4ToByteStream(output, v.integer);
        
        writeProtocolHeaderSize(output);
    }
    
}


