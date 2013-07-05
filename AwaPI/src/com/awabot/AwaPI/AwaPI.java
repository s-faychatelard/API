package com.awabot.AwaPI;

import java.util.ArrayList;

import com.awabot.AwaPI.generic.Component;
import com.awabot.AwaPI.generic.GlobalFactory;
import com.awabot.AwaPI.network.client.NetworkClient;
import com.awabot.AwaPI.network.client.ZmqNetworkClient;

public class AwaPI {
	
	public static boolean init() {
		NetworkClient.createInstance(ZmqNetworkClient.class);
		NetworkClient.getInstance().init();
		
		/* For testing */
		GlobalFactory.addComponent("avance", "components.navigation.Avance", true);
		
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
