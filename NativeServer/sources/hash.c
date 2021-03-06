//
//  hash.c
//  NativeServer
//
//  Created by Sylvain Fay-Châtelard, Baptiste Burles on 08/01/14.
//  Copyright (c) 2013 Dviance, Kliplab. All rights reserved.
//

#include <stdio.h>

#define FNV1_32_INIT ((unsigned int)2166136261)
#define FNV_32_PRIME ((unsigned int)0x01000193)

unsigned int hash32(unsigned char *buf, unsigned int len)
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
