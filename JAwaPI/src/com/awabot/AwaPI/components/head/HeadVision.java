package com.awabot.AwaPI.components.head;

import com.awabot.AwaPI.AwaPI;
import com.awabot.AwaPI.generic.Component;

public class HeadVision extends Component {

	public HeadVision(String name) {
		super(name);
	}

	public void startMovement() {
		System.out.println(AwaPI.getComponentById(alias("servo")).exec("getPosition"));
	}
}
