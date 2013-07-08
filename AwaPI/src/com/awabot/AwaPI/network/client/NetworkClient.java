package com.awabot.AwaPI.network.client;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

import com.awabot.AwaPI.generic.GlobalFactory;

public abstract class NetworkClient {

	private static NetworkClient networkInstance = null;
	
	private static final int MAGIC = 0x42415359;
	protected static final int BUFFER_SIZE = 1024;
	
	protected BytecodeStream readStream;
	protected BytecodeStream writeStream;
	
	public NetworkClient() {
		
		writeStream = new BytecodeStream(BUFFER_SIZE);
		readStream = new BytecodeStream(BUFFER_SIZE);
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
	
	public abstract void writeBuffer();
	
	
	public void init() {
		
		open();
		writeHeader(1, (byte)0x0);
		writeBuffer();
		this.readTable();
	}
	
	public void writeInt(String deviceName, String actionName, Integer value) {
		// Command get table
		// 4 octets Device Name size
		// x octets Device Name
		// 4 octets Action Name size
		// x octets Action Name
		// 4 octets Value

		writeStream.reset();
		writeHeader(4 + deviceName.length() + 4 + actionName.length() + 4, (byte)0x1);
		writeStream.write32Bits(deviceName.length());
		writeStream.writeNBytes(deviceName.getBytes(), deviceName.length());
		
		System.out.println("Write deviceName " + deviceName.length() + " : " + deviceName);
		
		writeStream.write32Bits(actionName.length());
		writeStream.writeNBytes(actionName.getBytes(), actionName.length());
		
		System.out.println("Write actionName " + actionName.length() + " : " + actionName);
		
		writeStream.write32Bits(value);
		
		System.out.println("Write value : " + value);
		
		writeBuffer();
	}
	
	public void writeHeader(Integer sizeToSend, byte command) {
		
		// Header
		// 4 octets Magic
		// 4 octets Total size
		// 1 octet  Command
		
		// reset buffer index
		writeStream.reset();
		
		// send magic
		writeStream.write32Bits(MAGIC);
		
		// send size
		writeStream.write32Bits(sizeToSend);
		
		// send command
		writeStream.write8Bits(command);
		
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
		// 4 octets Devices number
		// 4 octets Name size
		// x octets Name
		// 4 octets Type size
		// x octets Type name
		// 4 octets Action number
		
		Integer magic = readStream.read32Bits();
		Integer globalSize = readStream.read32Bits();
		byte command = readStream.read8Bits();
		
		System.out.println("Magic 0x" + Integer.toHexString(magic));
		System.out.println("Global size " + globalSize);
		System.out.println("Command " + command);
		
		Integer numDevices = readStream.read32Bits();
		
		for(int i=0; i<numDevices; i++) {
			
			Integer nameSize = readStream.read32Bits();
			String name = new String(readStream.readNBytes(nameSize));
			
			Integer typeSize = readStream.read32Bits();
			String type = new String(readStream.readNBytes(typeSize));
			
			System.out.println("Name " + nameSize + " : " + name);
			System.out.println("Type " + typeSize + " : " + type);
			
			GlobalFactory.addComponent(name, type, true);
			
			Integer numActions = readStream.read32Bits();
			for(int j=0; j<numActions; j++) {
				readAction();
			}
		}
	}
	
	public void readAction() {
		// Action
		// 1 octet  Type action
		// 1 octet  Type value
		// 4 octets Action name size
		// x octets Action name
		
		byte action = readStream.read8Bits();
		byte value = readStream.read8Bits();
		
		Integer actionNameSize = readStream.read32Bits();
		String actionName = readStream.readNBytes(actionNameSize).toString();
	}
	
}
