package com.awabot.AwaPI.network.client;

public class BytecodeStream {
	private int currentIndex;
	private byte [] buffer;
	
	
	public BytecodeStream(int size)
	{
		currentIndex = 0;
		buffer = new byte[size];
	}
	
	byte []toByteArray()
	{
		byte []temp = new byte[currentIndex];
		
		for(int i=0;i<currentIndex;i++)
		{
			temp[i] = buffer[i];
		}
		
		return temp;
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
		
		/*
		System.out.println( buffer[currentIndex-4] + " " 
		+ buffer[currentIndex-3] + " " 
		+ buffer[currentIndex-2] + " " 
		+ buffer[currentIndex-1]);*/
		
	}

	public void write16Bits(Integer integer)
	{
		int temp = integer.intValue();
		buffer[currentIndex] = (byte)(temp>>8);
		buffer[currentIndex] = (byte)(temp);
	}
	
	public void write8Bits(byte b)
	{
		buffer[currentIndex++] = b;
	}
}
