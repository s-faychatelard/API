//
//  hal.h
//  NativeServer
//
//  Created by bburles on 09/07/13.
//  Copyright (c) 2013 Awabot. All rights reserved.
//

#ifndef NativeServer_hal_h
#define NativeServer_hal_h

/** @brief Add an user callback
 *
 * @param callback      Function
 * @param name          Name of function, same as Java method
 * @param type          Type of devices (for example "devices.Motor")
 */
extern void addUserDeviceAction(ActionCallback callback, char *name, char * type);

/** @brief Initialize the user callback action
 *
 * YOU HAVE TO IMPLEMENT THIS FUNCTION YOURSELF, see test repertory for examples.
 */
extern void initUserCallback(void);




#endif
