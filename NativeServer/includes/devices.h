//
//  devices.h
//  NativeServer
//
//  Created by bburles on 05/07/13.
//  Copyright (c) 2013 Dviance. All rights reserved.
//

#ifndef NativeServer_devices_h
#define NativeServer_devices_h

typedef enum _value_type_
{
    VALUE_UNKNONW = 0x00,
    VALUE_INTEGER = 0x01,
    VALUE_ARRAY = 0x02
} ValueType;

typedef union _value_
{
    int     integer;
    void *  array;
} Value;

typedef struct _device_ Device;

typedef void (*ActionCallback)(Device * device, Value * value);

typedef enum _action_type_
{
    ACTION_UNKNONW = 0x00,
    ACTION_READ = 0x01,
    ACTION_WRITE = 0x02
} ActionType;

typedef struct _action_
{
    ActionType      type;
    ValueType       valueType;
    char *          name;
    unsigned int    hash;
    ActionCallback  action;
} DeviceAction;


typedef struct _device_physical_
{
    char *          type;
    unsigned int    hash;
    unsigned int    number;
    DeviceAction * actions;
} DevicePhysical;


struct _device_
{
    char *          name;
    unsigned int    hash;
    DevicePhysical *  device;
};

extern unsigned int hash32(unsigned char *buf, unsigned int len);

extern Device robotDevices[];

extern unsigned int initDevicesTable(Device device[]);

extern unsigned int initDeviceAction(DeviceAction *actions);

extern Device * getDeviceByName(Device * devices, unsigned char * name, unsigned int nameSize);

extern DeviceAction * getDeviceActionByName(Device * device, unsigned char * name, unsigned int nameSize);

#endif
