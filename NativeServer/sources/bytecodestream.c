
#include <stdlib.h>
#include <string.h>

#include "../includes/bytecodestream.h"

unsigned int get4FromBuffer(unsigned char *buffer)
{
	unsigned int integer = ((buffer)[0]<<24)| ((buffer)[1]<<16)|((buffer)[2]<<8)|((buffer)[3]);
    
	return integer;
}

void set4ToBuffer(unsigned char *buffer, unsigned int integer)
{
	buffer[0] = (integer>>24);
	buffer[1] = (integer>>16);
	buffer[2] = (integer>>8);
	buffer[3] = (integer);
}

unsigned short get2FromBuffer(unsigned char *buffer)
{
	unsigned short integer = ((buffer)[0]<<8)|((buffer)[1]);
    
	return integer;
}

void set2ToBuffer(unsigned char *buffer, unsigned short integer)
{
	buffer[0] = (integer>>8);
	buffer[1] = (unsigned char)(integer);
}


BytecodeStream * newBytecodeStream(unsigned char * input)
{
    BytecodeStream * stream = (BytecodeStream *)malloc(sizeof(BytecodeStream));
    
    stream->buffer = input;
    stream->current = stream->buffer;
    
    return stream;
}

void resetBytecodeStream(BytecodeStream * stream)
{
    stream->current = stream->buffer;
}

unsigned int getBytecodeStreamSize(BytecodeStream * stream)
{
    return (stream->current - stream->buffer);
}

void write1ToBytecodeStream(BytecodeStream * stream, unsigned char data)
{
    *stream->current = data;
    stream->current++;
}

void write2ToBytecodeStream(BytecodeStream * stream, unsigned short data)
{
    set2ToBuffer(stream->current, data);
    stream->current += 2;
}

void write4ToBytecodeStream(BytecodeStream * stream, unsigned int data)
{
    set4ToBuffer(stream->current, data);
    stream->current += 4;
}

void writeBufferToBytecodeStream(BytecodeStream * stream, unsigned char * input, unsigned int size)
{
    memcpy(stream->current, input,size);
    stream->current += size;
}
