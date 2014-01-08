//
//  robot-hal.c
//  NativeServer
//
//  Created by Sylvain Fay-Châtelard, Baptiste Burles on 08/01/14.
//  Copyright (c) 2013 Dviance, Kliplab. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../includes/list.h"
#include "../../includes/devices.h"
#include "../../includes/robot-hal.h"

//----------------------------- private objects

static List userDeviceList;


//----------------------------- private functions


//----------------------------- public functions

void initRobotHal(void)
{
    listInit(&userDeviceList);
    initUserCallback();
}

void addUserDeviceAction(ActionCallback callback, char *name, char * type)
{
    UserDeviceAction * user = (UserDeviceAction *)malloc(sizeof(UserDeviceAction));
    
    user->action = callback;
    user->name = malloc(strlen(name));
    strcpy(user->name,name);
    
    user->type = malloc(strlen(type));
    strcpy(user->type,type);
    
    listAddElement(&userDeviceList, user);
}

ActionCallback getUserCallbackByName(char * name, char * type)
{
    UserDeviceAction * ptr;
    ListNode *n = userDeviceList.first;
    while (n != NULL)
    {
        ptr = (UserDeviceAction *)n->data;
        
        if (strcmp(ptr->name, name)==0 && strcmp(ptr->type, type)==0)
        {
            return ptr->action;
        }
        
        n = n->next;
    }
    
    return 0;
}
