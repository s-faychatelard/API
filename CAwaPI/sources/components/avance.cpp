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

#include "../../includes/components/avance.h"

#include "../../includes/component.h"
REGISTER_CLASS(Avance);

#include "../../includes/AwaPI.h"
#include "../../includes/device.h"

void Avance::start(int speed)
{
    Device *left = (Device*)AwaPI::getComponentById(alias((char*)"avance"));
    
    printf("%s set speed %d\n", name, speed);
}