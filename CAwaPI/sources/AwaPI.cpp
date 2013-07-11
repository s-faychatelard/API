#include "../includes/AwaPI.h"

#include "../includes/globalfactory.h"
#include "../includes/networkclient.h"

bool AwaPI::init(char* serverAddress, char* componentsPath)
{
    GlobalFactory::init();
    NetworkClient::createInstance(ZMQ);
    
    NetworkClient::getInstance()->open(serverAddress);
    
    GlobalFactory::addComponent((char*)"avance", (char*)"Avance");
    //GlobalFactory::addComponent((char*)"tourne", (char*)"Tourne");
    //GlobalFactory::addComponent((char*)"avoider", (char*)"Avoider");

//TODO
    /*try {
        XmlParser.parseXmlFile(componentsPath);
    } catch(IllegalStateException e) {
        System.err.println(e.getMessage());
        return false;
    }*/
    
    return true;
}

void AwaPI::shutdown()
{
    NetworkClient::getInstance()->close();
}

List* AwaPI::getComponentsByType(char* type)
{
    return GlobalFactory::getComponentsByType(type);
}

Component* AwaPI::getComponentById(char* id)
{
    return GlobalFactory::getComponentById(id);
}
