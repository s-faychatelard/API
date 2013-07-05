package com.awabot.AwaPI.components.navigation;

import com.awabot.AwaPI.AwaPI;
import com.awabot.AwaPI.generic.Component;

public class Tourne extends Component {
	
	public Tourne(String name) {
		super(name);
	}

	public void rotateToLeftInDegree(Integer degree) {
		this.rotate(-150, 150);
	}
	
	public void rotateToRightInDegree(Integer degree) {
		this.rotate(150, -150);
	}
	
	public void rotate(Integer leftSpeed, Integer rightSpeed) {
		AwaPI.getComponentById("leftWheel").exec("setSpeed", leftSpeed);
		AwaPI.getComponentById("rightWheel").exec("setSpeed", rightSpeed);
	}
}
