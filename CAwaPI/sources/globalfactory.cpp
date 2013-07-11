#include "../includes/globalfactory.h"

#include "../includes/hash.h"

#include <string.h>

static HashTable idPool;
static HashTable typePool;

List* components = NULL;

void GlobalFactory::init()
{
    hashTableInit(&idPool, 10);
    hashTableInit(&typePool, 10);
}

Component* GlobalFactory::addComponent(char* id, char* type, bool standardComponent)
{
    Component* obj = (Component*)g_factory.construct(type, id);
    
    hashTableInsert(&idPool, hash32(id, (int)strlen(id)), obj);
    
    List *l = (List*)hashTableLookup(&typePool, hash32(id, (int)strlen(id)));
    if (l == NULL)
    {
        l = (List*)malloc(sizeof(List));
        listInit(l);
        hashTableInsert(&typePool, hash32(id, (int)strlen(id)), l);
    }
    listAddElement(l, obj);
		
    return obj;
}

List* GlobalFactory::getComponentsByType(char* type)
{
    List* list = (List*)hashTableLookup(&typePool, hash32(type, (int)strlen(type)));
    if (list == NULL)
    {
        char* message = (char*)"No component typed ";
        message = stringInsert(message, type, (int)strlen(message));
        message = stringInsert(message, "exists for now", (int)strlen(message));
        
        throw message;
    }
    return list;
}

Component* GlobalFactory::getComponentById(char* id)
{
    Component* component = (Component*)hashTableLookup(&idPool, hash32(id, (int)strlen(id)));
    if (component == NULL)
    {
        char* message = (char*)"The component ";
        message = stringInsert(message, id, (int)strlen(message));
        message = stringInsert(message, " doesn't exist", (int)strlen(message));
        
        throw message;
    }
    return component;
}