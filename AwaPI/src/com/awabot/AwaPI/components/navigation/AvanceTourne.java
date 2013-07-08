package com.awabot.AwaPI.components.navigation;

import com.awabot.AwaPI.AwaPI;
import com.awabot.AwaPI.generic.Component;

public class AvanceTourne extends Component {
	
	public AvanceTourne(String name) {
		super(name);
	}
	
	public void start(Integer time) {
		AwaPI.getComponentById("avance").exec("start", 150);
		//Thread.sleep(time);
		AwaPI.getComponentById("tourne").exec("rotateToLeftInDegree", 90);
	}
}
