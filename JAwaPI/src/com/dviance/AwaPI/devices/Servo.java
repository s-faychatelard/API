package com.dviance.AwaPI.devices;

import com.dviance.AwaPI.generic.Device;

public class Servo extends Device {

	public Servo(String name) {
		super(name);
	}

	public Integer getPosition() {
		System.out.println("Get position of " + this.name);
		return this.readInt("getPosition");
	}
	
	public void setPosition(Integer position) {
		System.out.println("Set position of " + this.name);
		this.writeInt("setPosition", position);
	}
}
