package com.dviance.AwaPI.network.client;

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
	
	public byte read8Bits()
	{
		byte b = buffer[currentIndex];
	    
		currentIndex+= 1;
		
		return b;
	}
	
	public Integer read32Bits()
	{
		int integer	 = ((buffer)[currentIndex]<<24) & 0xFF000000;
		integer 	|= ((buffer)[currentIndex+1]<<16) & 0x00FF0000;
		integer 	|= ((buffer)[currentIndex+2]<<8) & 0x0000FF00;
		integer 	|= ((buffer)[currentIndex+3]) & 0x000000FF;
	    
		currentIndex+=4;
		
		return integer;
	}
	
	public byte[] readNBytes(Integer numBytes)
	{
		byte []temp = new byte[numBytes];
		
		for(int i=currentIndex, j=0;i<currentIndex+numBytes;i++,j++)
		{
			temp[j] = buffer[i];
		}
		
		currentIndex+=numBytes;
		
		return temp;
	}
	
	public void write8Bits(byte b)
	{
		buffer[currentIndex++] = b;
	}
	
	public void write16Bits(Integer integer)
	{
		int temp = integer.intValue();
		buffer[currentIndex] = (byte)(temp>>8);
		buffer[currentIndex] = (byte)(temp);
		
		currentIndex+=2;
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
	
	public void writeNBytes(byte[] buffer, Integer numBytes)
	{
		for(int i=currentIndex, j=0;i<currentIndex+numBytes;i++, j++)
		{
			this.buffer[i] = buffer[j];
		}
		
		currentIndex+=numBytes;
	}
}
