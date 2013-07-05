package com.awabot.AwaPI.network.client;

import org.zeromq.ZMQ;
import org.zeromq.ZMQ.Socket;
import org.zeromq.ZContext;

public class NetworkClient {
	
	ZContext	zContext;
	Socket 		zSocket;
	
	public NetworkClient()
	{
		zContext = new ZContext();
		
		zSocket = zContext.createSocket(ZMQ.REQ);
		
		zSocket.connect("tcp://localhost:8687");
	}
	
	public void test()
	{
		
		zSocket.send("Hello");
		
		String str = zSocket.recvStr();
		
		System.out.println("Receive : " + str);
		
	}
	
	
	public void close()
	{
		zSocket.close();
		zContext.close();
	}

}
