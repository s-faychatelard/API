package com.dviance.AwaPI.generic;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

/**
 * The global factory for the AwaPI.
 *
 */
public class GlobalFactory {

	public final static String API_PREFIX = "com.dviance.AwaPI.";
	
	private final static Map<String, Component> idPool = new HashMap<String, Component>();
	private final static Map<String, ArrayList<Component>> typePool = new HashMap<String, ArrayList<Component>>();
	
	/**
	 * Register a component into the global factory.
	 * If the component's id is already existing, the factory create a new instance and forget the old.
	 * Warning, the older instance is no more accessible in the factory but is always in memory !
	 * 
	 * @param id		Component's identifier (For example "avoider")
	 * @param type		Java package name (for example "components.navigation.Avoider")
	 * @param standardComponent		If your component is directly in the AwaPI, set true, else false.
	 * @return The component.
	 * @throws IllegalStateException
	 */
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
	
	/**
	 * Get the list of all component of the same type.
	 * @param type		Component's type (for example "components.navigation")
	 * @return A list of component.
	 */
	public static ArrayList<Component> getComponentsByType(String type) {
		if (!typePool.containsKey(type)) {
			throw new IllegalStateException("No component typed " + type + "exists for now");
		}
		return typePool.get(type);
	}

	/**
	 * Get the component with the specified id.
	 * @param id 		Component's identifier (for example "avoider")
	 * @return The component or null if not found.
	 */
	public static Component getComponentById(String id) {
		if (!idPool.containsKey(id)) {
			throw new IllegalStateException("The component " + id + " doesn't exist");
		}
		return idPool.get(id);
	}
}
