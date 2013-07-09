package com.awabot.AwaPI.devices;

import com.awabot.AwaPI.generic.Device;

public class Servo extends Device {

	public Servo(String name) {
		super(name);
	}

	public Integer getPosition() {
		System.out.println("Get position of " + this.name);
		return this.readInt(this.name, "getPosition");
	}
}
