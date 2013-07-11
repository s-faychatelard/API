#ifndef CAWAPI_AWAPI
#define CAWAPI_AWAPI

#include <babcode.h>

#include "component.h"

class AwaPI {
public:
    static bool init(char* serverAddress, char* componentsPath) ;
    static void shutdown() ;
    static List* getComponentsByType(char* type);
    static Component* getComponentById(char* id);
};

#endif