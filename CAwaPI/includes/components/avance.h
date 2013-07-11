/*package com.awabot.AwaPI.components.navigation;

import com.awabot.AwaPI.AwaPI;
import com.awabot.AwaPI.generic.Component;

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
}*/

#ifndef CAWAPI_AVANCE
#define CAWAPI_AVANCE

#include "../component.h"

class Avance : public Component {
public:
    Avance(char* name) : Component(name) {}
    
    void start(int speed);
};

#endif