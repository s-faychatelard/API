package com.awabot.AwaPI.network.client;

public abstract class NetworkClient {

	private static final int BUFFER_SIZE = 16;
	
	private BytecodeStream stream;
	
	public NetworkClient()
	{
		stream = new BytecodeStream(BUFFER_SIZE);
	}
	
	public abstract boolean open();
	
	public abstract void close();
	
	public abstract void writeInt(Object caller, String actionName, Integer i);
	
	public abstract Integer readInt(Object caller, String actionName);

	
	protected void beginWrite(Object caller, String actionName, Integer integer)
	{
		String name = caller.getClass().getSimpleName();
		
		// reset buffer index
		stream.reset();
		
		
		int h = Hash.get(name.getBytes());
		
		System.out.println("Hash = " + h);
		
		stream.write32Bits(h);
		
		h = Hash.get(actionName.getBytes());
		stream.write32Bits(h);
		
		stream.write32Bits(integer);
		
	}
	
}
