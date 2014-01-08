package com.dviance.AwaPI.components.head;

import com.dviance.AwaPI.AwaPI;
import com.dviance.AwaPI.generic.Component;

public class HeadVision extends Component {

	public HeadVision(String name) {
		super(name);
	}

	public void startMovement() {
		System.out.println(AwaPI.getComponentById(alias("servo")).exec("getPosition"));
	}
}
