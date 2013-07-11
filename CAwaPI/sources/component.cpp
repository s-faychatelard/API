#include "../includes/component.h"

#include <stdlib.h>
#include <string.h>

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

void* Component::exec(char* methodName/*, void* ... args*/)
{
    printf("Call %s", methodName);
    return 0;
}

/** Utils */

#define FNV1_32_INIT ((unsigned int)2166136261)
#define FNV_32_PRIME ((unsigned int)0x01000193)

unsigned int Component::hash32(char* buf, unsigned int len)
{
    unsigned int hval = FNV1_32_INIT ;
    unsigned char *bp = (unsigned char *)buf;	/* start of buffer */
    unsigned char *be = bp + len;		/* beyond end of buffer */
    
    /*
     * FNV-1 hash each octet in the buffer
     */
    while (bp < be)
    {
        
		/* multiply by the 32 bit FNV magic prime mod 2^32 */
		//hval += (hval<<1) + (hval<<4) + (hval<<7) + (hval<<8) + (hval<<24);
		hval *= FNV_32_PRIME;
        
		/* xor the bottom with the current octet */
		hval ^= (unsigned int)*bp++;
    }
    
    /* return our new hash value */
    return hval;
}
