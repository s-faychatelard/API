
#include <stdlib.h>
#include <string.h>

#include "../includes/ByteStream.h"

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


ByteStream * newByteStream(unsigned char * input)
{
    ByteStream * stream = (ByteStream *)malloc(sizeof(ByteStream));
    
    stream->buffer = input;
    stream->current = stream->buffer;
    
    return stream;
}

void resetByteStream(ByteStream * stream)
{
    stream->current = stream->buffer;
}

unsigned int getByteStreamSize(ByteStream * stream)
{
    return (stream->current - stream->buffer);
}

void write1ToByteStream(ByteStream * stream, unsigned char data)
{
    *stream->current = data;
    stream->current++;
}

void write2ToByteStream(ByteStream * stream, unsigned short data)
{
    set2ToBuffer(stream->current, data);
    stream->current += 2;
}

void write4ToByteStream(ByteStream * stream, unsigned int data)
{
    set4ToBuffer(stream->current, data);
    stream->current += 4;
}

void writeBufferToByteStream(ByteStream * stream, unsigned char * input, unsigned int size)
{
    memcpy(stream->current, input,size);
    stream->current += size;
}

unsigned char read1FromByteStream(ByteStream * stream)
{
    unsigned char data = *stream->current;
    stream->current++;
    
    return data;
}

unsigned int read4FromByteStream(ByteStream * stream)
{
    int integer = (stream->current[0]<<24)| (stream->current[1]<<16)|(stream->current[2]<<8)|(stream->current[3]);
	    
	stream->current +=4;
    return integer;
}
