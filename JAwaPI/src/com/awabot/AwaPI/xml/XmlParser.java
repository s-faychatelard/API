package com.awabot.AwaPI.xml;

import java.io.File;
import java.io.IOException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import com.awabot.AwaPI.generic.Component;
import com.awabot.AwaPI.generic.GlobalFactory;

public class XmlParser {
	
	/*

	<?xml version="1.0"?>
	<robot name="POB">
	    <component name="avance" type="components.navigation.Avance" standard="true"/>
	    <component name="tourne" type="components.navigation.Tourne" standard="true"/>
	    <component name="avanceTourne" type="components.navigation.AvanceTourne" standard="true">
	        <required name="components.navigation.Avance" standard="true"/>
	    </component>
	    <component name="head" type="components.head.HeadVision" standard="true">
	        <device name="servo" alias="rantanplan"/>
	    </component>
	</robot>


	*/
	
	public static void parseXmlFile(String filename) {
		
		try {
			DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
			DocumentBuilder db = dbf.newDocumentBuilder();
			Document doc = db.parse(new File(filename));
			
			NodeList nodeList = doc.getElementsByTagName("robot");
			
			Element robot = (Element)nodeList.item(0);
			
			System.out.println("Robot name : " + robot.getAttribute("name"));
			
			for (int i=0; i<robot.getChildNodes().getLength(); i++) {
				
				Node node = robot.getChildNodes().item(i);
				if (node.hasAttributes()) {
					
					Element el = (Element)node;
					Component component = GlobalFactory.addComponent(el.getAttribute("name"), el.getAttribute("type"), Boolean.parseBoolean(el.getAttribute("standard")));
					
					System.out.println(el.getAttribute("name"));
					System.out.println(el.getAttribute("type"));
					System.out.println(el.getAttribute("standard"));
					
					for (int j=0; j<el.getChildNodes().getLength(); j++) {
						
						Node n = el.getChildNodes().item(j);
						
						if (n.hasAttributes()) {
						
							Element e = (Element)n;
							
							if (e.getNodeName().compareTo("device") == 0) {
								
								component.addAlias(e.getAttribute("name"), e.getAttribute("alias"));
								
								System.out.println(e.getAttribute("name"));
								System.out.println(e.getAttribute("alias"));
								
							}
							else if (e.getNodeName().compareTo("required") == 0) {
								
								try {
									Class.forName( ((Boolean.parseBoolean(e.getAttribute("standard"))) ? GlobalFactory.API_PREFIX : "") + e.getAttribute("name"));
									
									System.out.println("Required " + e.getAttribute("name"));
									
								} catch (ClassNotFoundException e1) {
									throw new IllegalStateException("The component " + el.getAttribute("name") + " required a " + e.getAttribute("name"));
								}
							}
						}
					}
				}
			}
			
		} catch (ParserConfigurationException | SAXException | IOException e) {
			e.printStackTrace();
		}
		
	}
}