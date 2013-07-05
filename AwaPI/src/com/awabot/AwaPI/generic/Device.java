package com.awabot.AwaPI.generic;

import com.awabot.AwaPI.network.client.NetworkClient;

/**
 * Device is a specific component with network access
 */
public abstract class Device extends Component {
	
	protected NetworkClient network;
	
	public Integer readInt(Object caller, String actionName, Integer value) {
		return 0;//return network.readInt(caller, actionName, value);
	}
	
	public void writeInt(Object caller, String actionName, Integer value) {
		//network.writeInt(caller, actionName, value);
	}
	
	public Float readFloat(Object caller, String actionName, Float value) {
		return (float) 0.0;//network.readFloat(caller, actionName, value);
	}
	
	public void writeFloat(Object caller, String actionName, Float value) {
		//network.writeFloat(caller, actionName, value);
	}
}
