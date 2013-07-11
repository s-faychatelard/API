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
        //      4 size name of action
        //      ... name of action
        
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
    
    DeviceObject *	dev;
    DeviceHardware * hw;
    
    // get table command packet structure
    // 4 magic
    // 4 size total
    // 1 command
    // 4 device number
    writeProtocolHeader(stream,COMMAND_GET_TABLE);
    write4ToByteStream(stream, devices->size);
    
    // table payload :
    ListNode *n = devices->first;
    while (n != NULL)
    {
        dev = (DeviceObject *)n->data;
        
        // 4 size name of device
        // ... name of device
        
        nameSize = (unsigned int)strlen(dev->name);
        
        write4ToByteStream(stream, nameSize);
        writeBufferToByteStream(stream, (unsigned char *)dev->name, nameSize);
        
        hw = dev->hardware;
        
        // 4 size name of hardware
        // ... hardware name
        
        nameSize = (unsigned int)strlen(hw->type);
        
        write4ToByteStream(stream, nameSize);
        writeBufferToByteStream(stream, (unsigned char *)hw->type, nameSize);
        
        // 4 action number
        write4ToByteStream(stream, hw->actions.size);
        
        writeActionTable(stream, &hw->actions);
        

		n = n->next;
	}
    
    writeProtocolHeaderSize(stream);
}

void execCommand(NetworkCommand command, ByteStream * stream, ByteStream * output ,List * devices)
{
    unsigned char deviceName[255];
    unsigned char actionName[255];
    
    unsigned int deviceSize, actionSize;
    int value;
    unsigned int valueSize;
    
    DeviceObject * device;
    DeviceAction * action;
    
    Value v;
    
    memset(deviceName,0, 255);
    memset(actionName,0, 255);
    
    // send / get command structure
    // 4 device name size
    // ... device name
    deviceSize = read4FromByteStream(stream);
    readBufferFromByteStream(stream, deviceName, deviceSize);
    
    // 4 action name size
    // ... action name
    
    actionSize = read4FromByteStream(stream);
    readBufferFromByteStream(stream, actionName, actionSize);
    
    // 4 value size
    valueSize = read4FromByteStream(stream);
    
    
    device = getDeviceByName(devices, deviceName, deviceSize);
    if (device == 0)
    {
        printf("execCommand: device %s not found !\n", deviceName);
        return;
    }
    
    action = getDeviceActionByName(device,actionName,actionSize);
    if (action==0)
    {
        printf("execCommand: action %s not found !\n", actionName);
        return;
    }
    
    if (command==COMMAND_SEND)
    {
        // ... value
        
        if (valueSize==4)
        {
            value = (int)read4FromByteStream(stream);
        }
        else
        {
            //todo
//            readBufferFromByteStream(stream, un chtit buffer a malloc, valueSize);
            value = 0;
        }
        
        //todo set value in Value struct
        switch (action->valueType)
        {
            case VALUE_UNKNONW:
                v.integer = 0;
                break;
            case VALUE_INTEGER:
                v.integer = value;
                break;
            case VALUE_ARRAY:
                //todo get array address
                v.array = 0;
                break;
        }
        
    }
    else if (command==COMMAND_GET)
    {
        // it's a read order, we write the wanted size
        v.wantedSize = valueSize;
    }
    
    printf("-> execute on %s.%s = %d\n", device->name, action->name, v.integer);
    
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


