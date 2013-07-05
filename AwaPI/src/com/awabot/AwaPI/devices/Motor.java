package com.awabot.AwaPI.devices;

import com.awabot.AwaPI.generic.Device;

public class Motor extends Device {
	
	public void setSpeed(Integer speed) {
		System.out.println("Speed of set to " + speed);
		
		this.writeInt(this, "setSpeed", speed);
	}
	
	public void setSpeed(Float speed) {
		System.out.println("Speed set to " + speed);
		
		this.writeFloat(this, "setSpeed", speed);
	}
	
	@Override
	public String toString() {
		
		return "I'm a motor";
	}
}
