//
//  main.c
//  NativeServer
//
//  Created by bburles on 05/07/13.
//  Copyright (c) 2013 Dviance. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "../libs/zeromq/include/zmq.h"

#include "../includes/bytestream.h"
#include "../includes/devices.h"
#include "../includes/protocol.h"


static void * zContext;
static void * zSocket;



void initServer(void)
{
    zContext = zmq_ctx_new();
    zSocket = zmq_socket(zContext, ZMQ_REP);
    
    int rc = zmq_bind(zSocket, "tcp://*:8687");
    
    
}


void shutdownServer(void)
{
    zmq_close(zSocket);
    zmq_ctx_destroy(zContext);
}

int main(void)
{
    NetworkCommand command;
    int result;
    unsigned char * outputBuffer;
    unsigned char * inputBuffer;
    
    ByteStream * output;
    ByteStream * input;
    
    unsigned int magic, sizePacket, deviceNumber;
    
    printf("NativeServer Hello World\n");
    
    outputBuffer = (unsigned char *)malloc(BUFFER_SIZE);
    inputBuffer = (unsigned char *)malloc(BUFFER_SIZE);
    
    output = newByteStream(outputBuffer);
    input = newByteStream(inputBuffer);
    
    deviceNumber = initDevicesTable(robotDevices);
        
    initServer();
    
    while(1)
    {
        result = zmq_recv(zSocket, inputBuffer, BUFFER_SIZE, 0);
        
        if (result>0)
        {
            resetByteStream(input);
            
            printf("Received %d bytes\n", result);
        
            magic = read4FromByteStream(input);
            
            if (magic!=PROTOCOL_MAGIC)
            {
                printf("ERROR: Bad magic number !\n");
                continue;
            }
            
            sizePacket = read4FromByteStream(input);
            command = read1FromByteStream(input);
            
            printf("--> sizeTotal %d Command %x\n", sizePacket, command);
            
            switch(command)
            {
                case COMMAND_GET_TABLE:
                    
                    resetByteStream(output);
                    writeGetTableCommand(output, robotDevices, deviceNumber);
                    
                    printf("Send %d bytes for %d devices\n", getByteStreamSize(output), deviceNumber);
                    
                    zmq_send(zSocket, output->buffer, getByteStreamSize(output), 0);
                    
                    break;
                case COMMAND_SEND:
                    
                    readSendCommand(input, robotDevices);
                    
                    
                    zmq_send(zSocket, "WTF?", 4, 0);
                    
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