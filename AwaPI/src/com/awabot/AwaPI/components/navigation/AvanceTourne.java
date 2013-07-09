package com.awabot.AwaPI.components.navigation;

import com.awabot.AwaPI.AwaPI;
import com.awabot.AwaPI.generic.Component;

public class AvanceTourne extends Component {
	
	public AvanceTourne(String name) {
		super(name);
	}
	
	public void start(final Integer time) {

		new Thread(new Runnable() {
			
			private final Integer t = time;
			
			@Override
			public void run() {
				AwaPI.getComponentById("avance").exec("start", 150);
				try {
					Thread.sleep(t);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				AwaPI.getComponentById("tourne").exec("rotateToLeftInDegree", 90);
			}
		}).start();
	}
}
