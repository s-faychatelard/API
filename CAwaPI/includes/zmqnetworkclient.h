/*package com.awabot.AwaPI.network.client;

import org.zeromq.ZMQ;
import org.zeromq.ZMQ.Socket;
import org.zeromq.ZContext;

public class ZmqNetworkClient extends NetworkClient {
	
	private final ZContext	zContext;
	private Socket 		zSocket;
	
	public ZmqNetworkClient()
	{
		super();
		
		zContext = new ZContext();
	}
	
	public boolean open(String address)
	{
		zSocket = zContext.createSocket(ZMQ.REQ);
		zSocket.connect(address);
		
		return true;
	}
	
	public void close()
	{
		zContext.close();
	}
	
	public void writeBuffer()
	{
		byte []buffer = writeStream.toByteArray();
		
		zSocket.send(buffer);
		writeStream.reset();
		
		buffer = zSocket.recv();
		
		System.out.println("Read : " + buffer.length);
		
		readStream.reset();
		readStream.writeNBytes(buffer, buffer.length);
		readStream.reset();
	}
}*/

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