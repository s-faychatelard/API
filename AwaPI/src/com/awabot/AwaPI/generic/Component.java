package com.awabot.AwaPI.generic;

import java.lang.reflect.InvocationTargetException;

public abstract class Component {
	
	public void exec(Object caller, String methodName, Object ... args) {
		
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
