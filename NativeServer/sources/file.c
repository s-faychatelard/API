//
//  file.c
//  NativeServer
//
//  Created by bburles on 09/07/13.
//  Copyright (c) 2013 Awabot. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <errno.h>

static long int getFileSize( int fp )
{
    long int save_pos, size_of_file;
    
    save_pos = lseek(fp,0,SEEK_CUR);
    
	lseek( fp, 0L, SEEK_SET );
    
	size_of_file = lseek(fp, 0L,SEEK_END);
    
	lseek( fp, save_pos, SEEK_SET);
    
	return( size_of_file );
}

unsigned char *fileRead( char *filename, unsigned int *len )
{
	unsigned int size ;
	unsigned char *buffer ;
	int file ;
    
	//open the file
	file = open(filename,O_RDONLY);
	if( file == -1 )
	{
		printf("error: open file %s\n", filename );
		return NULL ;
	}
    
	//get its size
	size=(unsigned int)getFileSize(file);
    
	//alloc the size to a target buffer
	buffer =(unsigned char*) malloc(size);
	if( buffer == NULL )
	{
		printf("error : malloc\n");
		return NULL ;
	}
    
	//read the file and put the data in the target buffer
	if( read( file, buffer, size ) == -1 )
	{
		printf("error : read %s\n", filename);
		return NULL ;
	}
    
	//close the file
	close(file);
    
	*len = size ;
	return buffer;
}
