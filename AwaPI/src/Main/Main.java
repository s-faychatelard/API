package Main;

import com.awabot.AwaPI.AwaPI;

public class Main {

	public static void main(String[] args) throws InterruptedException {
		try {
			
			if (!AwaPI.init("tcp://192.168.11.144:8687", "/Users/sylvain/Documents/Git/API/AwaPI/components.xml")) {
			//if (!AwaPI.init("tcp://127.0.0.1:8687", "/Users/sylvain/Documents/Git/API/AwaPI/components.xml")) {
				AwaPI.shutdown();
				return;
			}
			
		} catch (IllegalStateException e) {
			
			System.err.println(e.getMessage());
			AwaPI.shutdown();
		}
		
		try {
			
			AwaPI.getComponentById("avanceTourne").exec("start", 5000);
			AwaPI.getComponentById("avanceTourne").exec("start", 5000);
			AwaPI.getComponentById("head").exec("startMovement");
		} catch (IllegalStateException e) {
			
			System.err.println(e.getMessage());
			AwaPI.shutdown();
		}
		
		Thread.sleep(10000);
		
		AwaPI.shutdown();
	}
}
