package com.awabot.AwaPI.network.client;

public class Hash {
	
	private static final int FNV1_32_INIT = (0x811C9DC5);
	private static final int FNV_32_PRIME = (0x01000193);

	public static int get(byte []buf)
	{
	    int hval = FNV1_32_INIT ;
	    int bp = 0;	/* start of buffer */
	    int be = buf.length;		/* beyond end of buffer */
	    
	    /*
	     * FNV-1 hash each octet in the buffer
	     */
	    while (bp < be)
	    {
	        
			/* multiply by the 32 bit FNV magic prime mod 2^32 */
			//hval += (hval<<1) + (hval<<4) + (hval<<7) + (hval<<8) + (hval<<24);
			hval *= FNV_32_PRIME;
	        
			/* xor the bottom with the current octet */
			hval ^= (int)buf[bp++];
	    }
	    
	    /* return our new hash value */
	    return hval;
	}
}
