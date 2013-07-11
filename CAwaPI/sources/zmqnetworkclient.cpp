#include "../includes/ZmqNetworkClient.h"

ZmqNetworkClient::ZmqNetworkClient() : NetworkClient()
{
    zContext = zmq_ctx_new();
}

bool ZmqNetworkClient::open(char* address)
{
    zSocket = zmq_socket(zContext, ZMQ_REP);
    zmq_connect(zSocket, address);
    
    return true;
}

void ZmqNetworkClient::close()
{
    zmq_close(zSocket);
    zmq_ctx_destroy(zContext);
}

void ZmqNetworkClient::writeBuffer()
{
    zmq_send (zSocket, writeStream->buffer, getByteStreamSize(writeStream), 0);
    resetByteStream(writeStream);
    
    resetByteStream(readStream);
    zmq_recv(zSocket, readStream->buffer, getByteStreamSize(readStream), 0);
    resetByteStream(readStream);
}
