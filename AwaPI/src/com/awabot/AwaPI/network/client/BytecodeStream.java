package com.awabot.AwaPI.network.client;

public class BytecodeStream {
	private int currentIndex;
	private byte [] buffer;
	
	
	public BytecodeStream(int size)
	{
		currentIndex = 0;
		buffer = new byte[size];
	}
	
	
	public void reset()
	{
		currentIndex = 0;
	}
	
	public Integer read32Bits()
	{
		int integer = ((buffer)[currentIndex]<<24)| ((buffer)[currentIndex+1]<<16)|((buffer)[currentIndex+2]<<8)|((buffer)[currentIndex+3]);
	    
		currentIndex+=4;
		
		return integer;
	}

	public Integer read16Bits()
	{
		int integer = ((buffer)[currentIndex]<<8)|((buffer)[currentIndex+1]);
	    
		currentIndex+= 2;
		
		return integer;
	}
	
	public void write32Bits(Integer integer)
	{
		int temp = integer.intValue();
		buffer[currentIndex++] = (byte)((temp>>24));
		buffer[currentIndex++] = (byte)(temp>>16);
		buffer[currentIndex++] = (byte)(temp>>8);
		buffer[currentIndex++] = (byte)(temp);
		
		System.out.println( (char)buffer[currentIndex-4] + " " 
		+ (char)buffer[currentIndex-3] + " " 
		+ (char)buffer[currentIndex-2] + " " 
		+(char)buffer[currentIndex-1]);
		
	}

	

	public void write16Bits(Integer integer)
	{
		int temp = integer.intValue();
		buffer[currentIndex] = (byte)(temp>>8);
		buffer[currentIndex] = (byte)(temp);
	}
}
