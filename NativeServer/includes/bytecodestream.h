

#ifndef asm2babvm_bytecodestream_h
#define asm2babvm_bytecodestream_h

typedef struct _bytecode_stream_
{
    unsigned char * buffer;
    unsigned char * current;
} BytecodeStream;


extern BytecodeStream * newBytecodeStream(unsigned char * input);

extern void resetBytecodeStream(BytecodeStream * stream);

extern unsigned int getBytecodeStreamSize(BytecodeStream * stream);

extern void write1ToBytecodeStream(BytecodeStream * stream, unsigned char data);

extern void write2ToBytecodeStream(BytecodeStream * stream, unsigned short data);

extern void write4ToBytecodeStream(BytecodeStream * stream, unsigned int data);

extern void writeBufferToBytecodeStream(BytecodeStream * stream, unsigned char * input, unsigned int size);


#endif
