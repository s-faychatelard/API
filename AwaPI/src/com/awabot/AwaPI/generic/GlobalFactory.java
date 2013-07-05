package com.awabot.AwaPI.generic;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class GlobalFactory {

	private final static String API_PREFIX = "com.awabot.AwaPI.";
	private final static Map<String, Component> idPool = new HashMap<String, Component>();
	private final static Map<String, ArrayList<Component>> typePool = new HashMap<String, ArrayList<Component>>();
	
	public static boolean addComponent(String id, String type) {
		
		Component obj = null;
		try {
			Class<?> cl = Class.forName(API_PREFIX + type);
			Constructor<?> con = cl.getConstructor();
			obj = (Component)con.newInstance();
		} catch (NoSuchMethodException | SecurityException | InstantiationException | IllegalAccessException | IllegalArgumentException | InvocationTargetException | ClassNotFoundException e) {
			
			throw new IllegalStateException("The class " + type + " doesn't exist");
		}
		
		idPool.put(id, obj);
		
		ArrayList<Component> l = typePool.get(type);
		if (l == null)
		{
			l = new ArrayList<>();
		}
		l.add(obj);
		
		typePool.put(type, l);
		
		return true;
	}
	
	public static ArrayList<Component> getComponentsByType(String type) {
		return typePool.get(type);
	}

	public static Component getComponentById(String id) {
		return idPool.get(id);
	}
}
