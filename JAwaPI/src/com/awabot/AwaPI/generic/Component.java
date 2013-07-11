package com.awabot.AwaPI.generic;

import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map;

/**
 * A generic component is identified by a unique name.
 * It can also include other component, identified by name/alias.
 * 
 */
public abstract class Component {
	
	protected final String name;
	private final Map<String, String> deviceNames = new HashMap<>();
	
	public Component(String name) {
		this.name = name;
	}
	
	/** 
	 * Add an alias for the component used by this component.
	 * @param name 		Component's name
	 * @param alias		Alias's name
	 */
	public void addAlias(String name, String alias) {
		deviceNames.put(name, alias);
	}
	
	/**
	 * Get the component's name from the speficied name or alias
	 * @param name		the Component's name or a component's alias
	 * @return	The component name
	 */
	protected String alias(String name) {
		if (!deviceNames.containsKey(name))
			return name;
		return deviceNames.get(name);
	}
	
	/** 
	 * Execute a method on this component
	 * @param methodName	Name of methods
	 * @param args			Argument for this method
	 * @return	Depends of methods.
	 * @throws IllegalStateException
	 */
	public Object exec(String methodName, Object ... args) throws IllegalStateException {
		
		Class<?> classes[] = null;
		try {
			
			if (args.length == 0) {
				return this.getClass().getMethod(methodName).invoke(this);
			}
			
			/* Construct an array of Class of each parameter */
			classes = new Class<?>[args.length];
			Integer i=0;
			for (Object arg : args) {
				classes[i++] = arg.getClass();
			}

			/* Get the method and invoke it */
			return this.getClass().getMethod(methodName, classes).invoke(this, args);
			
		} catch (NoSuchMethodException | SecurityException | IllegalAccessException | IllegalArgumentException e) {
			
			StringBuilder s = new StringBuilder();
			Integer i=0;
			for (@SuppressWarnings("unused") Object a : args) {
				s.append(classes[i++].toString());
				s.append(" ");
			}
			
			throw new IllegalStateException("The method " + methodName + " in " + this.getClass() 
												+ " with parameter" + ((args.length > 1) ? "s" : "") 
												+ " typed " + s.toString() + "doesn't exist");
			
		} catch (InvocationTargetException e) {
			throw new IllegalStateException("The method " + methodName + " in " + this.getClass() 
					+ " failed with error : \n\t" + e.getCause().getMessage());
		}
	}
}
