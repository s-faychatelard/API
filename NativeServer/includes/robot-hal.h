//
//  hal.h
//  NativeServer
//
//  Created by bburles on 09/07/13.
//  Copyright (c) 2013 Awabot. All rights reserved.
//

#ifndef NativeServer_hal_h
#define NativeServer_hal_h


extern void addUserDeviceAction(ActionCallback callback, char *name, char * type);

extern ActionCallback getUserCallbackByName(char * name, char * type);

extern void initRobotHal(void);

extern void initUserCallback(void);


#endif
