package com.awabot.AwaPI.components.navigation;

import com.awabot.AwaPI.generic.Component;
import com.awabot.AwaPI.generic.GlobalFactory;

public class Avance extends Component {
	
	public void start(Integer speed) {
		GlobalFactory.getComponentById("leftWheel").exec(GlobalFactory.getComponentById("leftWheel"), "setSpeed", speed);
		GlobalFactory.getComponentById("rightWheel").exec(GlobalFactory.getComponentById("rightWheel"), "setSpeed", speed);
	}
	
	public void stop() {
		GlobalFactory.getComponentById("leftWheel").exec(GlobalFactory.getComponentById("leftWheel"), "setSpeed", 0);
		GlobalFactory.getComponentById("rightWheel").exec(GlobalFactory.getComponentById("rightWheel"), "setSpeed", 0);
	}
}
