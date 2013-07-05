package com.awabot.AwaPI.generic;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class GlobalFactory {

	private final static Map<String, Component> idPool = new HashMap<String, Component>();
	private final static Map<String, ArrayList<Component>> typePool = new HashMap<String, ArrayList<Component>>();
	
	static {
		/* Construct both Map */
		
	}
	
	public static ArrayList<Component> getComponentsByType(String type) {
		return typePool.get(type);
	}

	public static Component getComponentById(String id) {
		return idPool.get(id);
	}
}
