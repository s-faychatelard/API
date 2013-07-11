/*package com.awabot.AwaPI.generic;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class GlobalFactory {

	public final static String API_PREFIX = "com.awabot.AwaPI.";
	
	private final static Map<String, Component> idPool = new HashMap<String, Component>();
	private final static Map<String, ArrayList<Component>> typePool = new HashMap<String, ArrayList<Component>>();
	
	public static Component addComponent(String id, String type, boolean standardComponent) throws IllegalStateException {
		
		Component obj = null;
		try {
			
			Class<?> cl = Class.forName( ((standardComponent) ? API_PREFIX : "") + type);
			Constructor<?> con = cl.getConstructor(String.class);
			obj = (Component)con.newInstance(id);
		} catch (NoSuchMethodException | SecurityException | InstantiationException | IllegalAccessException | IllegalArgumentException | InvocationTargetException | ClassNotFoundException e) {
			
			throw new IllegalStateException("The class " + type + " doesn't exist");
		}
		
		idPool.put(id, obj);
		
		ArrayList<Component> l = typePool.get(type);
		if (l == null)
		{
			l = new ArrayList<>();
		}
		if (!l.contains(l))
			l.add(obj);
		
		typePool.put(type, l);
		
		return obj;
	}
	
	public static ArrayList<Component> getComponentsByType(String type) {
		if (!typePool.containsKey(type)) {
			throw new IllegalStateException("No component typed " + type + "exists for now");
		}
		return typePool.get(type);
	}

	public static Component getComponentById(String id) {
		if (!idPool.containsKey(id)) {
			throw new IllegalStateException("The component " + id + " doesn't exist");
		}
		return idPool.get(id);
	}
}*/
