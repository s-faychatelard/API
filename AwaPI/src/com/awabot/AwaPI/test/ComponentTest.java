package com.awabot.AwaPI.test;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

import com.awabot.AwaPI.components.navigation.Avance;
import com.awabot.AwaPI.components.navigation.Tourne;
import com.awabot.AwaPI.generic.GlobalFactory;

public class ComponentTest {

	@Before
	public void setUp() throws Exception {
		
		GlobalFactory.addComponent("leftWheel", "devices.Motor", true);
		GlobalFactory.addComponent("rightWheel", "devices.Motor", true);
		
		GlobalFactory.addComponent("avance", "components.navigation.Avance", true);
		GlobalFactory.addComponent("tourne", "components.navigation.Tourne", true);
	}
	
	@Test
	public void getComponentsByType() {
		assertEquals(2, GlobalFactory.getComponentsByType("devices.Motor").size());
	}

	@Test
	public void execCallWithParameter() {
		GlobalFactory.getComponentById("avance").exec(GlobalFactory.getComponentById("avance"), "start", 42);
	}
	
	@Test
	public void execCallWithoutParameter() {
		GlobalFactory.getComponentById("avance").exec(GlobalFactory.getComponentById("avance"), "stop");
	}
	
	@Test
	public void directCallWithParameter() {
		Tourne tourne = (Tourne)GlobalFactory.getComponentById("tourne");
		tourne.rotateToLeftInDegree(90);
	}
	
	@Test
	public void directCallWithoutParameter() {
		Avance avance = (Avance)GlobalFactory.getComponentById("avance");
		avance.stop();
	}
	
	@Test(expected=IllegalStateException.class)
	public void classWrongMethod() {
		Tourne tourne = (Tourne)GlobalFactory.getComponentById("tourne");
		tourne.exec(tourne, "Toto", 43, "tutu");
	}
}
