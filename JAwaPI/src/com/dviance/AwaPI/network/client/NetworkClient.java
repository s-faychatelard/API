package com.dviance.AwaPI.network.client;

import java.io.UnsupportedEncodingException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

import com.dviance.AwaPI.generic.Device;
import com.dviance.AwaPI.generic.GlobalFactory;
import com.dviance.AwaPI.generic.Device.Action;
import com.dviance.AwaPI.generic.Device.Value;

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
	
	public abstract boolean open(String address);
	
	public abstract void close();
	
	public abstract void writeBuffer();
	
	
	public void init(String address) {

		open(address);
		writeHeader(1, (byte)0x0);
		writeBuffer();
		this.readTable();
	}
	
	public synchronized void writeInt(String deviceName, String actionName, Integer value) {
		// Command Write
		// 4 octets Device Name size
		// x octets Device Name
		// 4 octets Action Name size
		// x octets Action Name
		// 4 octets Value Size
		// 4 octets Value

		writeStream.reset();
		writeHeader(4 + deviceName.length() + 4 + actionName.length() + 4, (byte)0x1);
		writeStream.write32Bits(deviceName.length());
		writeStream.writeNBytes(deviceName.getBytes(), deviceName.length());
		
		System.out.println("Write deviceName " + deviceName.length() + " : " + deviceName);
		
		writeStream.write32Bits(actionName.length());
		writeStream.writeNBytes(actionName.getBytes(), actionName.length());
		
		System.out.println("Write actionName " + actionName.length() + " : " + actionName);
		
		/* Specify the size of the data, here Int equal to 4 bytes */
		writeStream.write32Bits(4);
		writeStream.write32Bits(value);
		
		System.out.println("Write value : " + value);
		
		writeBuffer();
	}
	
	public synchronized Integer readInt(String deviceName, String actionName) {
		// Command Read Int
		// 4 octets Device Name size
		// x octets Device Name
		// 4 octets Action Name size
		// x octets Action Name
		// 4 octets Wanted size

		writeStream.reset();
		writeHeader(4 + deviceName.length() + 4 + actionName.length() + 4, (byte)0x2);
		writeStream.write32Bits(deviceName.length());
		writeStream.writeNBytes(deviceName.getBytes(), deviceName.length());
		
		System.out.println("Write deviceName " + deviceName.length() + " : " + deviceName);
		
		writeStream.write32Bits(actionName.length());
		writeStream.writeNBytes(actionName.getBytes(), actionName.length());
		
		System.out.println("Write actionName " + actionName.length() + " : " + actionName);
		
		/* Specify that I want 4 bytes */
		writeStream.write32Bits(4);
		
		writeBuffer();
		
		Integer magic = readStream.read32Bits();
		Integer globalSize = readStream.read32Bits();
		byte command = readStream.read8Bits();
		
		System.out.println("Magic 0x" + Integer.toHexString(magic));
		System.out.println("Global size " + globalSize);
		System.out.println("Command " + command);
		
		return readStream.read32Bits();
	}
	
	private void writeHeader(Integer sizeToSend, byte command) {
		
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
	}
	
	private void readTable() {
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
			
			Device device = (Device)GlobalFactory.addComponent(name, type, true);
			
			Integer numActions = readStream.read32Bits();
			for(int j=0; j<numActions; j++) {
				readAction(device);
			}
		}
	}
	
	private void readAction(Device device) {
		// Action
		// 1 octet  Type action (READ | WRITE)
		// 1 octet  Type value ( UNKNOWN | INTEGER | FLOAT | ... )
		// 4 octets Action name size
		// x octets Action name
		
		byte action = readStream.read8Bits();
		byte value = readStream.read8Bits();
		
		Action a = Action.getAction(action);
		Value v = Value.getValue(value);
		
		Integer actionNameSize = readStream.read32Bits();
		String actionName = null;
		try {
			actionName = new String(readStream.readNBytes(actionNameSize), "ASCII");
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		
		device.addAction(actionName, a, v);
		
		System.out.println(actionName + " " + a.toString() + " " + v.toString());
	}
	
}
