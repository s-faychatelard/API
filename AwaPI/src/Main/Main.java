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
		
		AwaPI.getComponentById("avance").exec("start", 150);
		
		AwaPI.shutdown();
	}
}
