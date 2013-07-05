package com.awabot.AwaPI.components.navigation;

import com.awabot.AwaPI.generic.Component;
import com.awabot.AwaPI.generic.GlobalFactory;

public class Tourne extends Component {
	
	public void rotateToLeftInDegree(Integer degree) {
		this.rotate(-150, 150);
	}
	
	public void rotateToRightInDegree(Integer degree) {
		this.rotate(150, -150);
	}
	
	public void rotate(Integer leftSpeed, Integer rightSpeed) {
		GlobalFactory.getComponentById("leftWheel").exec(GlobalFactory.getComponentById("leftWheel"), "setSpeed", leftSpeed);
		GlobalFactory.getComponentById("rightWheel").exec(GlobalFactory.getComponentById("rightWheel"), "setSpeed", rightSpeed);
	}
}
