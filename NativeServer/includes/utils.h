//
//  utils.h
//  NativeServer
//
//  Created by bburles on 10/07/13.
//  Copyright (c) 2013 Dviance. All rights reserved.
//

#ifndef NativeServer_utils_h
#define NativeServer_utils_h

extern unsigned int hash32(unsigned char *buf, unsigned int len);

extern unsigned char *fileRead(char *filename, unsigned int *len );

#endif
