package com.awabot.AwaPI;

import java.util.ArrayList;

import com.awabot.AwaPI.generic.Component;
import com.awabot.AwaPI.generic.GlobalFactory;
import com.awabot.AwaPI.network.client.NetworkClient;
import com.awabot.AwaPI.network.client.ZmqNetworkClient;
import com.awabot.AwaPI.xml.XmlParser;

public class AwaPI {
	
	/**
	 * Initialize the AwaPI client.
	 * This connect your program to the Native Server instance at serverAddress and initialize the component factory with the XML contents.
	 * 
	 * @param serverAddress 	Server URI address ("tcp://localhost:8687")
	 * @param componentsPath	XML file for component
	 * @return false if error
	 */
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
	
	/**
	 * Shutdown the AwaPI client.
	 */
	public static void shutdown() {
		NetworkClient.getInstance().close();
	}
	
	/**
	 * Get a list of component of the same device type.
	 * @param type		Type of device (for example "devices.Motor")
	 * @return A list with component of specified type.
	 */
	public static ArrayList<Component> getComponentsByType(String type) {
		return GlobalFactory.getComponentsByType(type);
	}

	/**
	 * Get the instance of the component with the specified id name.
	 * @param id 	Name of component's instance (for example "avoider")
	 * @return The component
	 */
	public static Component getComponentById(String id) {
		return GlobalFactory.getComponentById(id);
	}
}
