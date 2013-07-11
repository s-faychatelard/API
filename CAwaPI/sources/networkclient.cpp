#include "../includes/networkclient.h"

#include "../includes/globalfactory.h"

#include "../includes/zmqnetworkclient.h"

#include <string.h>

static NetworkClient *networkInstance = NULL;

NetworkClient::NetworkClient()
{
    readStream = newByteStream(inputBuffer);
    writeStream = newByteStream(outputBuffer);
}

void NetworkClient::createInstance(Network type)
{
    switch (type) {
        case ZMQ:
            networkInstance = new ZmqNetworkClient();
            break;
    }
}

NetworkClient* NetworkClient::getInstance()
{
    return networkInstance;
}

void NetworkClient::init(char* address)
{
    open(address);
    writeHeader(1, 0x0);
    writeBuffer();
    readTable();
}

void NetworkClient::writeInt(char* deviceName, char* actionName, int value)
{
    // Command Write
    // 4 octets Device Name size
    // x octets Device Name
    // 4 octets Action Name size
    // x octets Action Name
    // 4 octets Value Size
    // 4 octets Value
    
    
    resetByteStream(writeStream);
    
    writeHeader(4 + (int)strlen(deviceName) + 4 + (int)strlen(actionName) + 4, 0x1);
    
    write4ToByteStream(writeStream, (int)strlen(deviceName));
    writeBufferToByteStream(writeStream, (unsigned char*)deviceName, (int)strlen(deviceName));
    
    printf("Write deviceName %d : %s\n", (int)strlen(deviceName), deviceName);
    
    write4ToByteStream(writeStream, (int)strlen(actionName));
    writeBufferToByteStream(writeStream, (unsigned char*)actionName, (int)strlen(actionName));
    
    printf("Write actionName %d : %s\n", (int)strlen(actionName), actionName);
    
    /* Specify the size of the data, here Int equal to 4 bytes */
    write4ToByteStream(writeStream, 4);
    write4ToByteStream(writeStream, value);
    
    printf("Write value : %d\n", value);
    
    writeBuffer();
}

int NetworkClient::readInt(char* deviceName, char* actionName)
{
    // Command Read Int
    // 4 octets Device Name size
    // x octets Device Name
    // 4 octets Action Name size
    // x octets Action Name
    // 4 octets Wanted size
    
    resetByteStream(writeStream);
    
    writeHeader(4 + (int)strlen(deviceName) + 4 + (int)strlen(actionName) + 4, 0x2);
    
    write4ToByteStream(writeStream, (int)strlen(deviceName));
    writeBufferToByteStream(writeStream, (unsigned char*)deviceName, (int)strlen(deviceName));
    
    printf("Write deviceName %d : %s\n", (int)strlen(deviceName), deviceName);
    
    write4ToByteStream(writeStream, (int)strlen(actionName));
    writeBufferToByteStream(writeStream, (unsigned char*)actionName, (int)strlen(actionName));
    
    printf("Write actionName %d : %s\n", (int)strlen(actionName), actionName);
    
    /* Specify that I want 4 bytes */
    write4ToByteStream(writeStream, 4);
    
    writeBuffer();
    
    int magic = read4FromByteStream(readStream);
    int globalSize = read4FromByteStream(readStream);
    char command = read1FromByteStream(readStream);
    
    (void)magic;
    (void)globalSize;
    (void)command;
    
    //System.out.println("Magic 0x" + Integer.toHexString(magic));
    //System.out.println("Global size " + globalSize);
    //System.out.println("Command " + command);*/
    
    return read4FromByteStream(readStream);
}

void NetworkClient::writeHeader(int sizeToSend, char command) {
    
    // Header
    // 4 octets Magic
    // 4 octets Total size
    // 1 octet  Command
    
    // reset buffer index
    resetByteStream(writeStream);
    
    // send magic
    write4ToByteStream(writeStream, MAGIC);
    
    // send size
    write4ToByteStream(writeStream, sizeToSend);
    
    // send command
    write1ToByteStream(writeStream, command);
}

void NetworkClient::readTable() {
    // Command get table
    // 4 octets Devices number
    // 4 octets Name size
    // x octets Name
    // 4 octets Type size
    // x octets Type name
    // 4 octets Action number
    
    int magic = read4FromByteStream(readStream);
    int globalSize = read4FromByteStream(readStream);
    char command = read1FromByteStream(readStream);
    
    (void)magic;
    (void)globalSize;
    (void)command;
    
    //System.out.println("Magic 0x" + Integer.toHexString(magic));
    //System.out.println("Global size " + globalSize);
    //System.out.println("Command " + command);
    
    int numDevices = read4FromByteStream(readStream);
    
    for(int i=0; i<numDevices; i++) {
        
        int nameSize = read4FromByteStream(readStream);
        char *name = (char*)malloc(nameSize);
        readBufferFromByteStream(readStream, (unsigned char*)name, nameSize);
        
        int typeSize = read4FromByteStream(readStream);
        char *type = (char*)malloc(typeSize);
        readBufferFromByteStream(readStream, (unsigned char*)type, typeSize);
        
        printf("Name %d : %s\n", nameSize, name);
        printf("Type %d : %s\n", typeSize, type);

        Device* device = (Device*)GlobalFactory::addComponent(name, type);
        
        int numActions = read4FromByteStream(readStream);
        for(int j=0; j<numActions; j++) {
            readAction(device);
        }
    }
}

void NetworkClient::readAction(Device* device) {
    // Action
    // 1 octet  Type action (READ | WRITE)
    // 1 octet  Type value ( UNKNOWN | INTEGER | FLOAT | ... )
    // 4 octets Action name size
    // x octets Action name
    
    char action = read1FromByteStream(readStream);
    char value = read1FromByteStream(readStream);
    
    //Action a = Action.getAction(action);
    //Value v = Value.getValue(value);
    
    int actionNameSize = read4FromByteStream(readStream);
    char* actionName = (char*)malloc(actionNameSize);
    readBufferFromByteStream(readStream, (unsigned char*)actionName, actionNameSize);
    
    device->addAction(actionName, (Device::Action)action, (Device::Value)value);
    
    printf("Action : %s : %d-%d\n", actionName, action, value);
}









