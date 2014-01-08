package com.dviance.AwaPI.devices;

import com.dviance.AwaPI.generic.Device;

public class DistanceSensor extends Device {

	public DistanceSensor(String name) {
		super(name);
	}
	
	public Integer getDistance() {
		return this.readInt("getDistance");
	}
}
