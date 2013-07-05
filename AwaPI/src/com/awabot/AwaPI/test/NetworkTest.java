package com.awabot.AwaPI.test;


import com.awabot.AwaPI.network.client.*;

public class NetworkTest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		
		System.out.println("TEST OF NETWORK");
		
		NetworkClient client = new NetworkClient();

		client.test();
		
		client.close();
		
	}

}
