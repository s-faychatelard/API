#include <babcode.h>

class Component {
public:
    Component(char *name);
    ~Component();
    
private:
	HashTable deviceNames;

protected:
    char* name;
    
    char* alias(char* name);
	unsigned int hash32(char* buf, unsigned int len);
    
public:
    void addAlias(char* name, char* alias);
    void* exec(char* methodName/*, void* ... args*/);
};
