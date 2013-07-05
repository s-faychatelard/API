package com.awabot.AwaPI.components.navigation;

import com.awabot.AwaPI.AwaPI;
import com.awabot.AwaPI.generic.Component;

public class Avance extends Component {
	
	public Avance(String name) {
		super(name);
	}

	public void start(Integer speed) {
		AwaPI.getComponentById("leftWheel").exec("setSpeed", speed);
		AwaPI.getComponentById("rightWheel").exec("setSpeed", speed);
	}
	
	public void stop() {
		AwaPI.getComponentById("leftWheel").exec("setSpeed", 0);
		AwaPI.getComponentById("rightWheel").exec("setSpeed", 0);
	}
}
