#ifndef CAWAPI_NETWORKCLIENT
#define CAWAPI_NETWORKCLIENT
#include <babcode.h>

#include "device.h"

#define MAGIC 0x42415359
#define BUFFER_SIZE 1024

enum Network {
    ZMQ
};

class NetworkClient {
public:
    NetworkClient();
    
    static NetworkClient* getInstance();
    static void createInstance(Network type);
    
    virtual bool open(char* address) { return false; };
	virtual void close() = 0;
	virtual void writeBuffer() = 0;
    
    void init(char* address);
    void writeInt(char* deviceName, char* actionName, int value); /* must be synchronized */
    int readInt(char* deviceName, char* actionName); /* must be synchronized */
    
private:
	unsigned char inputBuffer[BUFFER_SIZE];
    unsigned char outputBuffer[BUFFER_SIZE];
    
    void writeHeader(int sizeToSend, char command);
    void readTable();
    void readAction(Device *device);
    
protected:
    ByteStream *readStream;
	ByteStream *writeStream;
};

#endif