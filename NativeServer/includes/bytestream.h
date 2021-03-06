//
//  hal.h
//  NativeServer
//
//  Created by Sylvain Fay-Châtelard, Baptiste Burles on 08/01/14.
//  Copyright (c) 2013 Dviance, Kliplab. All rights reserved.
//

#ifndef NativeServer_ByteStream_h
#define NativeServer_ByteStream_h

/** @file ByteStream
 
 Manage byte array as a input/output stream of bytes for network layer.
 
 */

typedef struct _byte_stream_
{
    unsigned char * buffer;
    unsigned char * current;
} ByteStream;

extern void set4ToBuffer(unsigned char *buffer, unsigned int integer);


extern ByteStream * newByteStream(unsigned char * input);

extern void resetByteStream(ByteStream * stream);

extern unsigned int getByteStreamSize(ByteStream * stream);


extern void write1ToByteStream(ByteStream * stream, unsigned char data);
extern void write2ToByteStream(ByteStream * stream, unsigned short data);
extern void write4ToByteStream(ByteStream * stream, unsigned int data);
extern void writeBufferToByteStream(ByteStream * stream, unsigned char * input, unsigned int size);


extern unsigned char read1FromByteStream(ByteStream * stream);
extern unsigned int read4FromByteStream(ByteStream * stream);
extern void readBufferFromByteStream(ByteStream * stream, unsigned char * output, unsigned int size);

#endif
