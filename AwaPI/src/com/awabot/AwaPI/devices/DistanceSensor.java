package com.awabot.AwaPI.devices;

import com.awabot.AwaPI.generic.Device;

public class DistanceSensor extends Device {

	public DistanceSensor(String name) {
		super(name);
	}
	
	public Integer getDistance() {
		return this.readInt("getDistance");
	}
}
