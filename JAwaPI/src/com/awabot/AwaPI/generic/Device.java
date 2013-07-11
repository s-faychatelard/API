package com.awabot.AwaPI.generic;

import java.util.HashMap;
import java.util.Map;

import com.awabot.AwaPI.network.client.NetworkClient;

/**
 * Device is a specific component with network access
 */
public abstract class Device extends Component {
	
	private final Map<String, String> actions = new HashMap<>();
	
	public Device(String name) {
		super(name);
	}
	
	/**
	 * Add an action for this device.
	 * @param actionName	Name of action (for example "setPosition")
	 * @param action		Action type (read or write)
	 * @param value			Value type (integer, array...)
	 */
	public void addAction(String actionName, Action action, Value value) {
		actions.put(actionName, String.valueOf(action) + "_" + String.valueOf(value));
	}
	
	/** 
	 * Check if we can invoke an action on this device.
	 * @param actionName	Name of action
	 * @param action		Action type
	 * @param value			Value type
	 * @return	true if we can call this device's action.
	 */
	private boolean canPerformAction(String actionName, Action action, Value value) {
		if (actions.get(actionName) != null && actions.get(actionName).compareTo(String.valueOf(action) + "_" + String.valueOf(value)) == 0) {
			return true;
		}
		return false;
	}
	
	/**
	 * Read an integer value from this action's device.
	 * @param actionName	Name of action
	 * @return The integer read on the Native Server.
	 * @throws IllegalStateException
	 */
	public Integer readInt(String actionName) throws IllegalStateException {
		if (!canPerformAction(actionName, Action.ACTION_READ, Value.VALUE_INTEGER)) {
			throw new IllegalStateException("\treadInt in " + this.name + " is not supported");
		}
		return NetworkClient.getInstance().readInt(this.name, actionName);
	}
	
	/**
	 * Write an integer on this action's device.
	 * @param actionName	Name of action
	 * @param value			Value to be written
	 * @throws IllegalStateException
	 */
	public void writeInt(String actionName, Integer value) throws IllegalStateException {
		if (!canPerformAction(actionName, Action.ACTION_WRITE, Value.VALUE_INTEGER)) {
			throw new IllegalStateException("\twriteInt in " + this.name + " is not supported");
		}
		NetworkClient.getInstance().writeInt(this.name, actionName, value);
	}
	
	/**
	 * Type of value for a device's action.
	 */
	public enum Value
	{
		VALUE_UNKNONW(0x00),
	    VALUE_INTEGER(0x01),
	    VALUE_ARRAY(0x02);
		
		private Integer type;
		
		Value(Integer type) {
			this.type = type;
		}
		
		public static Value getValue(byte b) {
			for (Value v : Value.values()) {
				if (v.type == b)
					return v;
			}
			return null;
		}
	}

	/**
	 * Type of action for a device's action.
	 *
	 */
	public enum Action
	{
	    ACTION_UNKNONW(0x00),
	    ACTION_READ(0x01),
	    ACTION_WRITE(0x02);
	    
	    private Integer action;
	    
		Action(Integer action) {
			this.action = action;
		}
		
		public static Action getAction(byte b) {
			for (Action a : Action.values()) {
				if (a.action == b)
					return a;
			}
			return null;
		}
	}
}
