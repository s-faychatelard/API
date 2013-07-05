package com.awabot.AwaPI.network.client;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

public abstract class NetworkClient {

	private static NetworkClient networkInstance = null;
	
	private static final int MAGIC = 0x42415359;
	protected static final int BUFFER_SIZE = 1024;
	
	protected BytecodeStream stream;
	
	public NetworkClient() {
		stream = new BytecodeStream(BUFFER_SIZE);
	}
	
	public static void createInstance(Class<?> networkClientClass) {
		try {
			Constructor<?> con = networkClientClass.getConstructor();
			networkInstance = (NetworkClient)con.newInstance();
		} catch (NoSuchMethodException | SecurityException | InstantiationException | IllegalAccessException | IllegalArgumentException | InvocationTargetException e) {

			e.printStackTrace();
		}
	}
	
	public static NetworkClient getInstance() {
		return networkInstance;
	}
	
	public abstract boolean open();
	
	public abstract void close();
	
	public abstract void writeInt(Object caller, String actionName, Integer i);
	
	public abstract Integer readInt(Object caller, String actionName);

	
	public void writeHeader(Integer sizeToSend, byte command) {
		
		// Header
		// 4 octets Magic
		// 4 octets Total size
		// 1 octet  Command
		
		// reset buffer index
		stream.reset();
		
		// send magic
		stream.write32Bits(MAGIC);
		
		// send size
		stream.write32Bits(sizeToSend);
		
		// send command
		stream.write8Bits(command);
		
		/*//String name = caller.getClass().getSimpleName();
		
		System.out.println("Begin write: caller=" + name + " action=" + actionName + " int=" + integer);
		
		int h = Hash.get(name.getBytes());
		
		System.out.println("Hash = " + h);
		
		stream.write32Bits(h);
		
		h = Hash.get(actionName.getBytes());
		stream.write32Bits(h);
		
		stream.write32Bits(integer);*/
	}
	
	public void readTable() {
		// Command get table
		// 4 octets Name size
		// x octets Name
		// 4 octets Type size
		// x octets Type name
		// 4 octets Action number
		
		Integer nameSize = stream.read32Bits();
		String name = stream.readNBits(nameSize).toString();
		
		Integer typeSize = stream.read32Bits();
		String type = stream.readNBits(typeSize).toString();
		
		Integer numActions = stream.read32Bits();
		for(int i=0; i<numActions; i++) {
			readAction();
		}
	}
	
	public void readAction() {
		// Action
		// 1 octet  Type action
		// 1 octet  Type value
		// 4 octets Action name size
		// x octets Action name
		
		byte action = stream.read8Bits();
		byte value = stream.read8Bits();
		
		Integer actionNameSize = stream.read32Bits();
		String actionName = stream.readNBits(actionNameSize).toString();
	}
	
}
