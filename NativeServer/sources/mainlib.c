//
//  main.c
//  NativeServer
//
//  Created by bburles on 05/07/13.
//  Copyright (c) 2013 Awabot. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libs/zeromq/include/zmq.h"

#include "../includes/list.h"
#include "../includes/bytestream.h"
#include "../includes/devices.h"
#include "../includes/protocol.h"
#include "../includes/simplexml.h"
#include "../includes/robot-hal.h"


#define DEVICE_XML  "../../../../../../../devices.xml"

#define DEVICE      "device"
#define PHYSICAL    "physical"
#define ACTION      "action"

extern unsigned char *fileRead(char *filename, unsigned int *len );

static void * zContext;
static void * zSocket;

static List physicalList;
static List deviceList;

static DeviceAction * currentAction;
static DevicePhysical * currentPhysical;
static Device * currentDevice;


void initServer(void)
{
    zContext = zmq_ctx_new();
    zSocket = zmq_socket(zContext, ZMQ_REP);
    
    int rc = zmq_bind(zSocket, "tcp://*:8687");
    if (rc == -1)
    {
        printf("Cannot bind error code : %d\n", errno);
        exit(-1);
    }
    
}


void shutdownServer(void)
{
    zmq_close(zSocket);
    zmq_ctx_destroy(zContext);
}

void * xmlHandler(SimpleXmlParser parser, SimpleXmlEvent event,
                  const char* szName, const char* szAttribute,
                  const char* szValue)
{
    
    if (event == ADD_SUBTAG)
    {
        //        printf("ADD_SUBTAG ");
        
        if (strcmp(DEVICE, szName)==0)
        {
            currentDevice = (Device *)malloc(sizeof(Device));
            currentDevice->hash = 0;
            
        }
        else if (strcmp(PHYSICAL, szName)==0)
        {
            currentPhysical = (DevicePhysical *)malloc(sizeof(DevicePhysical));
            currentPhysical->hash = 0;
            listInit(&currentPhysical->actions);
        }
        else if (strcmp(ACTION, szName)==0)
        {
            currentAction = (DeviceAction *)malloc(sizeof(DeviceAction));
            currentAction->hash = 0;
        }
    }
    else if (event == ADD_ATTRIBUTE)
    {
        //        printf("ADD_ATTRIBUTE ");
        
        if (strcmp(DEVICE, szName)==0)
        {
            if (strcmp("name", szAttribute)==0)
            {
                currentDevice->name = malloc(strlen(szValue));
                strcpy(currentDevice->name, szValue);
            }
            else if (strcmp("type", szAttribute)==0)
            {
                // get physical device
                currentDevice->device = getDevicePhysicalByName(&physicalList, szValue);
                if (currentDevice->device==0)
                {
                    printf("XML ERROR CANT FOUND PHYSICAL DEVICE %s !\n", szValue);
                }
            }
        }
        else if (strcmp(PHYSICAL, szName)==0)
        {
            if (strcmp("name", szAttribute)==0)
            {
                currentPhysical->type = malloc(strlen(szValue));
                strcpy(currentPhysical->type, szValue);
            }
        }
        else if (strcmp(ACTION, szName)==0)
        {
            if (strcmp("name", szAttribute)==0)
            {
                currentAction->name = malloc(strlen(szValue));
                strcpy(currentAction->name, szValue);
                
                currentAction->action = getUserCallbackByName(currentAction->name,currentPhysical->type);
                
            }
            else if (strcmp("type", szAttribute)==0)
            {
                if (strcmp("int", szValue)==0)
                {
                    currentAction->valueType = VALUE_INTEGER;
                }
                else
                {
                    currentAction->valueType = VALUE_UNKNONW;
                }
            }
            else if (strcmp(ACTION, szAttribute)==0)
            {
                if (strcmp("write", szValue)==0)
                {
                    currentAction->type = ACTION_WRITE;
                }
                else
                {
                    currentAction->type = ACTION_READ;
                }
            }
        }
    }
    else if (event == ADD_CONTENT)
    {
        //        printf("ADD_CONTENT ");
    }
    else if (event == FINISH_ATTRIBUTES)
    {
        //        printf("FINISH_ATTRIBUTES ");
        
        if (strcmp(PHYSICAL, szName)==0)
        {
            listAddElement(&physicalList, currentPhysical);
        }
    }
    else if (event == FINISH_TAG)
    {
        //        printf("FINISH_TAG ");
        
        if (strcmp(DEVICE, szName)==0)
        {
            listAddElement(&deviceList, currentDevice);
        }
        else if (strcmp(ACTION, szName)==0)
        {
            listAddElement(&currentPhysical->actions, currentAction);
        }
    }
    
    //    printf("name=%s attr=%s value=%s\n", szName, szAttribute, szValue);
    
    return xmlHandler;
}

void initXml(void)
{
    unsigned char * xmlBuffer;
    unsigned int xmlSize;
    SimpleXmlParser parser;
    
    listInit(&physicalList);
    listInit(&deviceList);
    
    xmlBuffer = fileRead(DEVICE_XML, &xmlSize);
    
    printf("initialize xml (%d)\n", xmlSize);
    
    parser = simpleXmlCreateParser((char *)xmlBuffer, xmlSize);
    
    simpleXmlParse(parser, xmlHandler);
    
    
    free(xmlBuffer);
}

int startNativeServer(void)
{
    NetworkCommand command;
    int result;
    unsigned char * outputBuffer;
    unsigned char * inputBuffer;
    
    ByteStream * output;
    ByteStream * input;
    
    unsigned int magic, sizePacket;
    
    printf("NativeServer launched...\n");
    
    outputBuffer = (unsigned char *)malloc(BUFFER_SIZE);
    inputBuffer = (unsigned char *)malloc(BUFFER_SIZE);
    
    output = newByteStream(outputBuffer);
    input = newByteStream(inputBuffer);
    
    initRobotHal();
    
    initXml();
    
    initDevicesTable(&deviceList);
    
    initServer();
    
    printf("NativeServer initialized ! now run...\n");
    
    while(1)
    {
        result = zmq_recv(zSocket, inputBuffer, BUFFER_SIZE, 0);
        
        if (result>0)
        {
            resetByteStream(input);
            
            //            printf("Received %d bytes\n", result);
            
            magic = read4FromByteStream(input);
            
            if (magic!=PROTOCOL_MAGIC)
            {
                printf("ERROR: Bad magic number !\n");
                continue;
            }
            
            sizePacket = read4FromByteStream(input);
            command = read1FromByteStream(input);
            
            //            printf("--> sizeTotal %d Command %x\n", sizePacket, command);
            
            switch(command)
            {
                case COMMAND_GET_TABLE:
                    
                    resetByteStream(output);
                    writeGetTableCommand(output, &deviceList);
                    
                    //                    printf("Send %d bytes for %d devices\n", getByteStreamSize(output), deviceNumber);
                    
                    zmq_send(zSocket, output->buffer, getByteStreamSize(output), 0);
                    
                    break;
                case COMMAND_SEND:
                    
                    execCommand(command, input, output, &deviceList);
                    
                    zmq_send(zSocket, "Oki", 3, 0);
                    
                    break;
                case COMMAND_GET:
                    
                    resetByteStream(output);
                    
                    execCommand(command, input, output, &deviceList);
                    
                    zmq_send(zSocket, output->buffer, getByteStreamSize(output), 0);
                    
                    break;
                default:
                    zmq_send(zSocket, "WTF?", 4, 0);
                    break;
            }
            
        }
        
        
    }
    
    
    shutdownServer();
    
    
    return 0;
}