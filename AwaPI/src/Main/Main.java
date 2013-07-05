package Main;

import com.awabot.AwaPI.AwaPI;

public class Main {

	public static void main(String[] args) {
		AwaPI.init();
		AwaPI.getComponentById("avance").exec(AwaPI.getComponentById("avance"), "start", 150);
	}
}
