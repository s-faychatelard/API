package com.dviance.AwaPI.components.navigation;

import com.dviance.AwaPI.AwaPI;
import com.dviance.AwaPI.generic.Component;

public class Avoider extends Component {

	public Avoider(String name) {
		super(name);
	}

	public void avoid() {

		new Thread(new Runnable() {
			
			@Override
			public void run() {
				
			    AwaPI.getComponentById(alias("servo")).exec("setPosition", 90);
			    
			    try {
					Thread.sleep(300);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			    
			    while(true)
			    {
			    	Integer distance = (Integer)AwaPI.getComponentById(alias("distance")).exec("getDistance");
			    	
			        if (distance < 300)
			        {
			        	AwaPI.getComponentById("avance").exec("stop");
			            
			        	AwaPI.getComponentById(alias("servo")).exec("setPosition", 0);
						
						try {
							Thread.sleep(500);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
			            
						distance = (Integer)AwaPI.getComponentById(alias("distance")).exec("getDistance");
						
			            if (distance < 300)
			            {
			            	AwaPI.getComponentById(alias("servo")).exec("setPosition", 180);
							
							try {
								Thread.sleep(500);
							} catch (InterruptedException e) {
								e.printStackTrace();
							}
			            
							distance = (Integer)AwaPI.getComponentById(alias("distance")).exec("getDistance");
							
			                if (distance < 300)
			                {
			                	AwaPI.getComponentById(alias("avance")).exec("start", -100);
			                }
			                else
			                {
			                	AwaPI.getComponentById(alias("tourne")).exec("rotateLeft", 100);
			                }
			            }
			            else
			            {
			            	AwaPI.getComponentById(alias("tourne")).exec("rotateRight", 100);
			            }
			            
			            try {
							Thread.sleep(1000);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
			            
			            AwaPI.getComponentById(alias("servo")).exec("setPosition", 90);
			           
			            try {
							Thread.sleep(500);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
			        }
			        else
			        {
			        	AwaPI.getComponentById(alias("avance")).exec("start", 100);
			            
			        	try {
							Thread.sleep(100);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
			        }
			    }
			}
		}).start();
	}
}
