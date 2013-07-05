package com.awabot.AwaPI.generic;

import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map;

public abstract class Component {
	
	private Map<String, Boolean> availability = new HashMap<>();
	
	public void addActionAvailable(String actionName, Boolean available) {
		availability.put(actionName, available);
	}
	
	public void exec(Object caller, String methodName, Object ... args) {
		
		if (this.availability.get(methodName) != null && this.availability.get(methodName).booleanValue() == false) {
			throw new IllegalStateException("Method " + methodName + " not available on your device");
		}
		
		Class<?> classes[] = null;
		try {
			
			if (args == null) {
				caller.getClass().getMethod(methodName).invoke(caller);
				return;
			}
			
			/* Construct an array of Class of each parameter */
			classes = new Class<?>[args.length];
			Integer i=0;
			for (Object arg : args) {
				classes[i++] = arg.getClass();
			}

			/* Get the method and invoke it */
			caller.getClass().getMethod(methodName, classes).invoke(caller, args);
			
		} catch (NoSuchMethodException | SecurityException | IllegalAccessException | IllegalArgumentException | InvocationTargetException e) {
			
			StringBuilder s = new StringBuilder();
			Integer i=0;
			for (@SuppressWarnings("unused") Object a : args) {
				s.append(classes[i++].toString());
				s.append(" ");
			}
			
			throw new IllegalStateException("The method " + methodName + " in " + caller.getClass() 
												+ " with parameter" + ((args.length > 1) ? "s" : "") 
												+ " typed " + s.toString() + "doesn't exist");
		}
	}
}
