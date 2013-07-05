package com.awabot.AwaPI.generic;

import com.awabot.AwaPI.network.client.NetworkClient;

/**
 * Device is a specific component with network access
 */
public abstract class Device extends Component {
	
	public Device(String name) {
		super(name);
	}

	public Integer readInt(Object caller, String actionName) {
		return 0;//NetworkClient.getInstance().readInt(caller, actionName);
	}
	
	public void writeInt(String deviceName, String actionName, Integer value) {
		NetworkClient.getInstance().writeInt(this.name, actionName, value);
	}
	
	/*public Float readFloat(Object caller, String actionName) {
		return NetworkClient.getInstance().readFloat(caller, actionName);
	}
	
	public void writeFloat(Object caller, String actionName, Float value) {
		NetworkClient.getInstance().writeFloat(caller, actionName, value);
	}*/
}
