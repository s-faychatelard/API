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
    zmq_recv(zSocket, buffer, 10, 0);
}