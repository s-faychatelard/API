#ifndef CAWAPI_COMPONENT
#define CAWAPI_COMPONENT

#include <babcode.h>

#include <map>
#include <string>

class Component {
public:
    Component(char *name);
    ~Component();
    
private:
	HashTable deviceNames;

protected:
    char* name;
    
    char* alias(char* name);
    
public:
    void addAlias(char* name, char* alias);
    //void* exec(char* methodName, void* ... args);

    template<typename Class>
    static void* registerComponent(char* name, Class c);
};



/* Generate dynamic object */

template <class T> void* constructor(char* name) { return (void*)new T(name); }

struct factory
{
    typedef void*(*constructor_t)(char *name);
    typedef std::map<std::string, constructor_t> map_type;
    map_type m_classes;
    
    template <class T>
    void* register_class(std::string const& n)
    { m_classes.insert(std::make_pair(n, &constructor<T>)); return NULL; }
    
    void* construct(std::string const& n, char* id)
    {
        map_type::iterator i = m_classes.find(n);
        if (i == m_classes.end()) return 0; // or throw or whatever you want
        return i->second(id);
    }
};

extern factory g_factory;

#define REGISTER_CLASS(n) void * class_ ## n = g_factory.register_class<n>(#n);

#endif