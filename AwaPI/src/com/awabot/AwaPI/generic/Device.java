package com.awabot.AwaPI.generic;

import com.awabot.AwaPI.network.client.NetworkClient;

/**
 * Device is a specific component with network access
 */
public abstract class Device extends Component {
	
	public Integer readInt(Object caller, String actionName) {
		return NetworkClient.getInstance().readInt(caller, actionName);
	}
	
	public void writeInt(Object caller, String actionName, Integer value) {
		NetworkClient.getInstance().writeInt(caller, actionName, value);
	}
	
	/*public Float readFloat(Object caller, String actionName) {
		return NetworkClient.getInstance().readFloat(caller, actionName);
	}
	
	public void writeFloat(Object caller, String actionName, Float value) {
		NetworkClient.getInstance().writeFloat(caller, actionName, value);
	}*/
}
