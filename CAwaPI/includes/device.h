#include "component.h"

class Device : protected Component {
public:
    Device(char* name);
    
    enum Value
	{
		VALUE_UNKNONW = 0x00,
	    VALUE_INTEGER = 0x01,
	    VALUE_ARRAY = 0x02
	};
    
	enum Action
	{
	    ACTION_UNKNONW = 0x00,
	    ACTION_READ = 0x01,
	    ACTION_WRITE = 0x02
	};
    
    void addAction(char* actionName, Action action, Value value);
    
    int readInt(char* actionName);
    void writeInt(char* actionName, int value);
    
private:
    HashTable actions;
    
    char* mergeActionValue(Action action, Value value);
    bool canPerformAction(char* actionName, Action action, Value value);
};
