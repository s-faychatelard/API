package com.awabot.AwaPI;

import java.util.ArrayList;

import com.awabot.AwaPI.generic.Component;
import com.awabot.AwaPI.generic.GlobalFactory;
import com.awabot.AwaPI.network.client.NetworkClient;
import com.awabot.AwaPI.network.client.ZmqNetworkClient;
import com.awabot.AwaPI.xml.XmlParser;

public class AwaPI {
	
	public static boolean init(String serverAddress, String componentsPath) {
		NetworkClient.createInstance(ZmqNetworkClient.class);
	
		NetworkClient.getInstance().init(serverAddress);
		
		try {
			XmlParser.parseXmlFile(componentsPath);
		} catch(IllegalStateException e) {
			System.err.println(e.getMessage());
			return false;
		}
		
		return true;
	}
	
	public static void shutdown() {
		NetworkClient.getInstance().close();
	}
	
	public static ArrayList<Component> getComponentsByType(String type) {
		return GlobalFactory.getComponentsByType(type);
	}

	public static Component getComponentById(String id) {
		return GlobalFactory.getComponentById(id);
	}
}
