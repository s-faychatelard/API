package com.awabot.AwaPI.components.navigation;

import com.awabot.AwaPI.AwaPI;
import com.awabot.AwaPI.generic.Component;

public class Tourne extends Component {
	
	public void rotateToLeftInDegree(Integer degree) {
		this.rotate(-150, 150);
	}
	
	public void rotateToRightInDegree(Integer degree) {
		this.rotate(150, -150);
	}
	
	public void rotate(Integer leftSpeed, Integer rightSpeed) {
		AwaPI.getComponentById("leftWheel").exec(AwaPI.getComponentById("leftWheel"), "setSpeed", leftSpeed);
		AwaPI.getComponentById("rightWheel").exec(AwaPI.getComponentById("rightWheel"), "setSpeed", rightSpeed);
	}
}
