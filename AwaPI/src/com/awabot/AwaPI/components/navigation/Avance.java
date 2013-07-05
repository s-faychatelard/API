package com.awabot.AwaPI.components.navigation;

import com.awabot.AwaPI.AwaPI;
import com.awabot.AwaPI.generic.Component;

public class Avance extends Component {
	
	public void start(Integer speed) {
		AwaPI.getComponentById("leftWheel").exec(AwaPI.getComponentById("leftWheel"), "setSpeed", speed);
		AwaPI.getComponentById("rightWheel").exec(AwaPI.getComponentById("rightWheel"), "setSpeed", speed);
	}
	
	public void stop() {
		AwaPI.getComponentById("leftWheel").exec(AwaPI.getComponentById("leftWheel"), "setSpeed", 0);
		AwaPI.getComponentById("rightWheel").exec(AwaPI.getComponentById("rightWheel"), "setSpeed", 0);
	}
}
