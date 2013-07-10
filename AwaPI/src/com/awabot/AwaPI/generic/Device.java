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
	
	/* Actions */
	public void addAction(String actionName, Action action, Value value) {
		actions.put(actionName, String.valueOf(action) + "_" + String.valueOf(value));
	}
	
	private boolean canPerformAction(String actionName, Action action, Value value) {
		if (actions.get(actionName) != null && actions.get(actionName).compareTo(String.valueOf(action) + "_" + String.valueOf(value)) == 0) {
			return true;
		}
		return false;
	}
	
	/* Integer */
	public Integer readInt(String actionName) throws IllegalStateException {
		if (!canPerformAction(actionName, Action.ACTION_READ, Value.VALUE_INTEGER)) {
			throw new IllegalStateException("\treadInt in " + this.name + " is not supported");
		}
		return NetworkClient.getInstance().readInt(this.name, actionName);
	}
	
	public void writeInt(String actionName, Integer value) throws IllegalStateException {
		if (!canPerformAction(actionName, Action.ACTION_WRITE, Value.VALUE_INTEGER)) {
			throw new IllegalStateException("\twriteInt in " + this.name + " is not supported");
		}
		NetworkClient.getInstance().writeInt(this.name, actionName, value);
	}
	
	/* Enum */
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
