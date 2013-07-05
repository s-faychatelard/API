package com.awabot.AwaPI;

import java.util.ArrayList;

import com.awabot.AwaPI.generic.Component;
import com.awabot.AwaPI.generic.GlobalFactory;

public class AwaPI {
	
	public static boolean init() {
		return true;
	}
	
	public static ArrayList<Component> getComponentsByType(String type) {
		return GlobalFactory.getComponentsByType(type);
	}

	public static Component getComponentById(String id) {
		return GlobalFactory.getComponentById("avance");
	}

	/* For testing */
	public static void main(String[] args) {
		
	}
}
