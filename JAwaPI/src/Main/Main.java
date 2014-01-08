package Main;

import com.dviance.AwaPI.AwaPI;
import com.dviance.AwaPI.generic.GlobalFactory;

public class Main {

	public static void main(String[] args) throws InterruptedException {
		try {
			
			if (!AwaPI.init("tcp://192.168.11.144:8687", "/Users/sylvain/Documents/Git/API/JAwaPI/components.xml")) {
			//if (!AwaPI.init("tcp://127.0.0.1:8687", "/Users/sylvain/Documents/Git/API/JAwaPI/components.xml")) {
				AwaPI.shutdown();
				return;
			}
			
		} catch (IllegalStateException e) {
			
			System.err.println(e.getMessage());
			AwaPI.shutdown();
		}
				
		try {

			AwaPI.getComponentById("avoider").exec("avoid");
			
		} catch (IllegalStateException e) {
			
			System.err.println(e.getMessage());
			AwaPI.shutdown();
		}
		
		Thread.sleep(60000);
		
		AwaPI.shutdown();
	}
}
