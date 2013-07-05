//
//  main.c
//  NativeServer
//
//  Created by bburles on 05/07/13.
//  Copyright (c) 2013 Dviance. All rights reserved.
//

#include <stdio.h>

#include "../libs/zeromq/include/zmq.h"


#define BUFFER_SIZE     16

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
    int result;
    unsigned char buffer[BUFFER_SIZE];
    
    printf("NativeServer Hello World\n");
    
    
    initServer();
    
    while(1)
    {
        result = zmq_recv(zSocket, buffer, BUFFER_SIZE, 0);
        
        printf("Received %d bytes : %s\n", result, buffer);
            
            
        zmq_send(zSocket, "OK", 2, 0);
        
    }
    
    
    shutdownServer();
    
    
    return 0;
}