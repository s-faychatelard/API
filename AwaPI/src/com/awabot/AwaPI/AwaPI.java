package com.awabot.AwaPI;

import java.util.ArrayList;

import com.awabot.AwaPI.generic.Component;
import com.awabot.AwaPI.generic.GlobalFactory;
import com.awabot.AwaPI.network.client.NetworkClient;
import com.awabot.AwaPI.network.client.ZmqNetworkClient;

public class AwaPI {
	
	public static boolean init() {
		NetworkClient.createInstance(ZmqNetworkClient.class);
		return true;
	}
	
	public static ArrayList<Component> getComponentsByType(String type) {
		return GlobalFactory.getComponentsByType(type);
	}

	public static Component getComponentById(String id) {
		return GlobalFactory.getComponentById(id);
	}

	/* For testing */
	public static void main(String[] args) {
		AwaPI.init();
		
		GlobalFactory.addComponent("leftWheel", "devices.Motor", true);
		GlobalFactory.addComponent("rightWheel", "devices.Motor", true);
		
		GlobalFactory.addComponent("avance", "components.navigation.Avance", true);
		
		AwaPI.getComponentById("avance").exec(AwaPI.getComponentById("avance"), "start", 42);
	}
}
