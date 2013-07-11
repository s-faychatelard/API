#include "../includes/device.h"

#include <string.h>

Device::Device(char* name) : Component(name)
{
    hashTableInit(&actions, 4);
}

char* Device::mergeActionValue(Action action, Value value)
{
    char *ac = (char*)malloc(1);
    int size = binToDecimalAscii(action, ac);
    stringInsert(ac, "_", size);
    
    char *va = (char*)malloc(1);
    size = binToDecimalAscii(value, ac);
    stringInsert(ac, va, (int)strlen(ac) + size);
    
    return ac;
}

void Device::addAction(char* actionName, Action action, Value value)
{
    char *ac = mergeActionValue(action, value);
    hashTableInsert(&actions, hash32(actionName, (int)strlen(actionName)), ac);
}

bool Device::canPerformAction(char* actionName, Action action, Value value)
{
    char* act = (char*)hashTableLookup(&actions, hash32(actionName, (int)strlen(actionName)));
    if (act == NULL)
    {
        return false;
    }
    
    char *ac = mergeActionValue(action, value);
    
    if (strcmp(act, ac) == 0)
    {
        return true;
    }
    
    return false;
}

int Device::readInt(char* actionName)
{
    if (!canPerformAction(actionName, ACTION_READ, VALUE_INTEGER))
    {
        char *message = (char*)"\treadInt in ";
        message = stringInsert(message, name, (int)strlen(message));
        message = stringInsert(message, " is not supported", (int)strlen(message));
        
        throw message;
    }
    
    //return NetworkClient.getInstance().readInt(this.name, actionName);
    return 0;
}

void Device::writeInt(char* actionName, int value)
{
    if (!canPerformAction(actionName, ACTION_WRITE, VALUE_INTEGER))
    {
        char *message = (char*)"\twriteInt in ";
        message = stringInsert(message, name, (int)strlen(message));
        message = stringInsert(message, " is not supported", (int)strlen(message));
        
        throw message;
    }
    
    //NetworkClient.getInstance().writeInt(this.name, actionName, value);
}
