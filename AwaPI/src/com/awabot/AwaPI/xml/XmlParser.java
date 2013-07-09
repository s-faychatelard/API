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

	<root>
	<robot name="POB">
		<component name="avance" type="components.navigation.Avance">
			<device alias="leftWheel" name="toto"/>
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
							component.addAlias(e.getAttribute("name"), e.getAttribute("alias"));
							
							System.out.println(e.getAttribute("name"));
							System.out.println(e.getAttribute("alias"));
						}
					}
				}
			}
			
		} catch (ParserConfigurationException | SAXException | IOException e) {
			e.printStackTrace();
		}
		
	}
}