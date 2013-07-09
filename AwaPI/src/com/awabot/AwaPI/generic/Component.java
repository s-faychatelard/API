package com.awabot.AwaPI.generic;

import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map;

public abstract class Component {
	
	protected final String name;
	private final Map<String, String> deviceNames = new HashMap<>();
	
	public Component(String name) {
		this.name = name;
	}
	
	public void addAlias(String name, String alias) {
		deviceNames.put(name, alias);
	}
	
	protected String alias(String name) {
		if (!deviceNames.containsKey(name))
			return name;
		return deviceNames.get(name);
	}
	
	public Object exec(String methodName, Object ... args) throws IllegalStateException {
		
		Class<?> classes[] = null;
		try {
			System.out.println(args.length);
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
