#ifndef CAWAPI_GLOBALFACTORY
#define CAWAPI_GLOBALFACTORY

#include <babcode.h>

#include "component.h"

class GlobalFactory {
public:
    static void init();
    static Component* addComponent(char* id, char* type, bool standardComponent = true);
    static List* getComponentsByType(char* type);
    static Component* getComponentById(char* id);
};

#endif