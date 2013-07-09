package Main;

import com.awabot.AwaPI.AwaPI;

public class Main {

	public static void main(String[] args) {
		try {
			AwaPI.init();
		} catch (IllegalStateException e) {
			e.printStackTrace();
			AwaPI.shutdown();
		}
		
		try {
			AwaPI.getComponentById("avanceTourne").exec("start", 150);
			AwaPI.getComponentById("head").exec("startMovement");
		} catch (IllegalStateException e) {
			System.err.println(e.getMessage());
			AwaPI.shutdown();
		}
		AwaPI.shutdown();
	}
}
