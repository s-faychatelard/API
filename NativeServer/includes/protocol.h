//
//  protocol.h
//  NativeServer
//
//  Created by Sylvain Fay-Châtelard, Baptiste Burles on 08/01/14.
//  Copyright (c) 2013 Dviance, Kliplab. All rights reserved.
//

#ifndef NativeServer_protocol_h
#define NativeServer_protocol_h


/** @file Network protocol
 
 Packet between Java client and Native server have the following format :
 
 Name           Size            Description
 ------------------------------------------------------------------------

 magic          4 bytes         Protocol identifier
 size-total     4 bytes         Size total of packet without magic and size-total
 command        1 byte          Protocol commmand
 data           size-total-1    Command's data
 
 data field are command's specific, see protocol.c for more details about the payload structure.
 
 */
 

#define PROTOCOL_MAGIC  0x42415359  /**< packet identifier */
#define BUFFER_SIZE     2048        /**< default input/output buffer size */

/** @brief A network command */
typedef enum _command_
{
    COMMAND_GET_TABLE   = 0x00,     /**< retrieve the device table */
    COMMAND_SEND        = 0x01,     /**< send a data to the specific device */
    COMMAND_GET         = 0x02      /**< get a data from a specific device */
} NetworkCommand;


extern void writeGetTableCommand(ByteStream * stream, List * devices);

extern void execCommand(NetworkCommand command, ByteStream * input, ByteStream * output, List * devices);

#endif
