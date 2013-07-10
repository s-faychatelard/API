package Main;

import com.awabot.AwaPI.AwaPI;

public class Main {

	public static void main(String[] args) throws InterruptedException {
		try {
			if (!AwaPI.init())
				return;
		} catch (IllegalStateException e) {
			e.printStackTrace();
			AwaPI.shutdown();
		}
		
		try {
			AwaPI.getComponentById("avanceTourne").exec("start", 5000);
			AwaPI.getComponentById("avanceTourne").exec("start", 5000);
			//AwaPI.getComponentById("head").exec("startMovement");
		} catch (IllegalStateException e) {
			System.err.println(e.getMessage());
			AwaPI.shutdown();
		}
		
		Thread.sleep(10000);
		
		AwaPI.shutdown();
	}
}
