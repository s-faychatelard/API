package com.dviance.AwaPI.components.navigation;

import com.dviance.AwaPI.AwaPI;
import com.dviance.AwaPI.generic.Component;

public class Avance extends Component {
	
	public Avance(String name) {
		super(name);
	}

	public void start(Integer speed) {
		AwaPI.getComponentById(alias("leftWheel")).exec("setSpeed", speed);
		AwaPI.getComponentById(alias("rightWheel")).exec("setSpeed", speed);
	}
	
	public void stop() {
		AwaPI.getComponentById(alias("leftWheel")).exec("setSpeed", 0);
		AwaPI.getComponentById(alias("rightWheel")).exec("setSpeed", 0);
	}
}