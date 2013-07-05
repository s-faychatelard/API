//
//  protocol.h
//  NativeServer
//
//  Created by bburles on 05/07/13.
//  Copyright (c) 2013 Dviance. All rights reserved.
//

#ifndef NativeServer_protocol_h
#define NativeServer_protocol_h


#define PROTOCOL_MAGIC  0x42415359

#define BUFFER_SIZE     2048

typedef enum _command_
{
    COMMAND_GET_TABLE   = 0x00,
    COMMAND_SEND        = 0x01
} NetworkCommand;


extern void writeGetTableCommand(ByteStream * stream, Device * devices);


#endif
