package com.awabot.AwaPI.devices;

import com.awabot.AwaPI.generic.Device;

public class Motor extends Device {
	
	public Motor(String name) {
		super(name);
	}

	public void setSpeed(Integer speed) {
		System.out.println("Speed of " + this.name + " set to " + speed);
		this.writeInt("setSpeed", speed);
	}
}
