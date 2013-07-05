package com.awabot.AwaPI.test;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import com.awabot.AwaPI.AwaPI;
import com.awabot.AwaPI.components.navigation.Avance;
import com.awabot.AwaPI.components.navigation.Tourne;
import com.awabot.AwaPI.generic.GlobalFactory;

public class ComponentTest {

	@Before
	public void setUp() throws Exception {
		AwaPI.init();
		
		GlobalFactory.clearComponents();
		GlobalFactory.addComponent("leftWheel", "devices.Motor", true);
		GlobalFactory.addComponent("rightWheel", "devices.Motor", true);
		
		GlobalFactory.addComponent("avance", "components.navigation.Avance", true);
		GlobalFactory.addComponent("tourne", "components.navigation.Tourne", true);
	}
	
	@Test
	public void getComponentsByType() {
		assertEquals(2, AwaPI.getComponentsByType("devices.Motor").size());
	}

	@Test
	public void execCallWithParameter() {
		AwaPI.getComponentById("avance").exec(AwaPI.getComponentById("avance"), "start", 42);
	}
	
	@Test
	public void execCallWithoutParameter() {
		AwaPI.getComponentById("avance").exec(AwaPI.getComponentById("avance"), "stop");
	}
	
	@Test
	public void directCallWithParameter() {
		Tourne tourne = (Tourne)AwaPI.getComponentById("tourne");
		tourne.rotateToLeftInDegree(90);
	}
	
	@Test
	public void directCallWithoutParameter() {
		Avance avance = (Avance)AwaPI.getComponentById("avance");
		avance.stop();
	}
	
	@Test(expected=IllegalStateException.class)
	public void classWrongMethod() {
		Tourne tourne = (Tourne)AwaPI.getComponentById("tourne");
		tourne.exec(tourne, "Toto", 43, "tutu");
	}
}
