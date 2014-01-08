#include "networkclient.h"

#include <zmq.h>

class ZmqNetworkClient : public NetworkClient {
public:
    ZmqNetworkClient();
	
	bool open(char* address);
	void close();
	void writeBuffer();
    
private:
    void *	zContext;
	void *	zSocket;
};