package com.awabot.AwaPI.network.client;

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
	
	public boolean open()
	{
		zSocket = zContext.createSocket(ZMQ.REQ);
		//zSocket.connect("tcp://192.168.11.144:8687");
		zSocket.connect("tcp://127.0.0.1:8687");
		
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
}
