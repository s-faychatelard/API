package com.awabot.AwaPI.test;


import com.awabot.AwaPI.network.client.*;

public class NetworkTest {

	public static void main(String[] args) {
		
		
		System.out.println("TEST OF NETWORK");
		
		ZmqNetworkClient client = new ZmqNetworkClient();

		client.open();
		
		client.test();
		
		client.close();
		
		
		System.out.println("End of test...");
	}

}
