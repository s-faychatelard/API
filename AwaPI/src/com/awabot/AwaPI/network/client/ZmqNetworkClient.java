package com.awabot.AwaPI.network.client;

import org.zeromq.ZMQ;
import org.zeromq.ZMQ.Socket;
import org.zeromq.ZContext;

public class ZmqNetworkClient extends NetworkClient {
	
	ZContext	zContext;
	Socket 		zSocket;
	
	public ZmqNetworkClient()
	{
		zContext = new ZContext();
	}
	
	public boolean open()
	{
		zSocket = zContext.createSocket(ZMQ.REQ);
		zSocket.connect("tcp://localhost:8687");
		
		return true;
	}
	
	public void test()
	{
		
		zSocket.send("COUCOU");
		
		System.out.println("Send ok, now receive...");
		
		byte [] buffer = zSocket.recv();
		
		System.out.println("Receive : " + buffer.length + " bytes " + (char )buffer[0] );
		
	}
	
	
	public void close()
	{
		zSocket.close();
		
		// moche pa :-(
//		zContext.close() 
	}

	public Integer readInt(Object caller, String actionName)
	{
		
		return 0;
	}
	
	public void writeInt(Object caller, String actionName, Integer i) 
	{
		//writeHeader(caller,actionName,i);
	
		zSocket.send(stream.toByteArray());
		byte []buffer = zSocket.recv();
		
		
	}

}
