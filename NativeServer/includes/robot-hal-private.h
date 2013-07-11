//
//  robot-hal-private.h
//  NativeServer
//
//  Created by bburles on 11/07/13.
//  Copyright (c) 2013 Awabot. All rights reserved.
//

#ifndef NativeServer_robot_hal_private_h
#define NativeServer_robot_hal_private_h


// Warning, this file is private, dont call directly the functions !


/** @brief Get an action callback from a name and type
 *
 * @param name      Name of action ("setPosition" for example)
 * @param type      Type of device ("devices.Servo" for example)
 * @return An action callback object.
 */
extern ActionCallback getUserCallbackByName(char * name, char * type);

/** @brief Initialize the robot hal structure and object.
 */
extern void initRobotHal(void);


#endif
