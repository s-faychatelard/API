#include "../includes/component.h"

#include "../includes/hash.h"

#include <stdlib.h>
#include <string.h>

factory g_factory;

Component::Component(char *name)
{
    this->name = strdup(name);
    
    hashTableInit(&deviceNames, 5);
}

Component::~Component()
{
    free(this->name);
}

char* Component::alias(char* name)
{
    char* alias = (char*)hashTableLookup(&deviceNames, hash32(name, (int)strlen(name)));
    return (alias == 0) ? name : alias;
}

void Component::addAlias(char* name, char* alias)
{
    hashTableInsert(&deviceNames, hash32(name, (int)strlen(name)), alias);
}

/*void* Component::exec(char* methodName, void* ... args)
{
    printf("Call %s\n", methodName);
    /*Class<?> classes[] = null;
    try {
        
        if (args.length == 0) {
            return this.getClass().getMethod(methodName).invoke(this);
        }
        
        // Construct an array of Class of each parameter
        classes = new Class<?>[args.length];
        Integer i=0;
        for (Object arg : args) {
            classes[i++] = arg.getClass();
        }
        
        // Get the method and invoke it
        return this.getClass().getMethod(methodName, classes).invoke(this, args);
        
    } catch (NoSuchMethodException | SecurityException | IllegalAccessException | IllegalArgumentException e) {
        
        StringBuilder s = new StringBuilder();
        Integer i=0;
        for (@SuppressWarnings("unused") Object a : args) {
            s.append(classes[i++].toString());
            s.append(" ");
        }
        
        throw new IllegalStateException("The method " + methodName + " in " + this.getClass()
                                        + " with parameter" + ((args.length > 1) ? "s" : "")
                                        + " typed " + s.toString() + "doesn't exist");
        
    } catch (InvocationTargetException e) {
        throw new IllegalStateException("The method " + methodName + " in " + this.getClass() 
                                        + " failed with error : \n\t" + e.getCause().getMessage());
    }*
    
    return 0;
}*/