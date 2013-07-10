package com.awabot.AwaPI.components.navigation;

import com.awabot.AwaPI.AwaPI;
import com.awabot.AwaPI.generic.Component;

public class Tourne extends Component {
	
	public Tourne(String name) {
		super(name);
	}

	public void rotateLeft(Integer speed) {
		this.rotate(-speed, speed);
	}
	
	public void rotateRight(Integer speed) {
		this.rotate(speed, -speed);
	}
	
	public void rotate(Integer leftSpeed, Integer rightSpeed) {
		AwaPI.getComponentById(alias("leftWheel")).exec("setSpeed", leftSpeed);
		AwaPI.getComponentById(alias("rightWheel")).exec("setSpeed", rightSpeed);
	}
}
