//
//  devices.h
//  NativeServer
//
//  Created by Sylvain Fay-Châtelard, Baptiste Burles on 08/01/14.
//  Copyright (c) 2013 Dviance, Kliplab. All rights reserved.
//

#ifndef NativeServer_devices_h
#define NativeServer_devices_h

/** @brief Type of value */
typedef enum _value_type_
{
    VALUE_UNKNONW = 0x00,       /**< an unknown value */
    VALUE_INTEGER = 0x01,       /**< this is an integer */
    VALUE_ARRAY = 0x02          /**< this is an array */
} ValueType;

/** @brief An array */
typedef struct _value_array_
{
    unsigned int len;           /**< size of array */
    unsigned char * buffer;     /**< array's data */
} ArrayValue;

/** @brief A value */
typedef union _value_
{
    int             wantedSize; /**< size we want when we read a value */
    int             integer;    /**< an integer value */
    ArrayValue *    array;      /**< a pointer to an array */
    void *          unknown;    /**< a generic pointer for whatever we have */
} Value;

typedef struct _device_object_ DeviceObject;

typedef void (*ActionCallback)(DeviceObject * device, Value * value);

/** @brief Type of action */
typedef enum _action_type_
{
    ACTION_UNKNONW  = 0x00,     /**< an unknown action */
    ACTION_READ     = 0x01,     /**< read action */
    ACTION_WRITE    = 0x02      /**< write action */
} ActionType;

/** @brief An user action
 *
 * This structure is used internally, you don't have access to this object.
 */
typedef struct _user_action_
{
    char *          name;   /**< name of action (must be the same as the Java method) */
    char *          type;   /**< type of devices ("devices.Motor" for example) */
    ActionCallback  action; /**< user callback */
} UserDeviceAction;

/** @brief An action for a device */
typedef struct _action_
{
    ActionType      type;       /**< type of this action (read or write) */
    ValueType       valueType;  /**< type of value (integer, array of bytes, float...) */
    char *          name;       /**< name of this action */
    unsigned int    hash;       /**< internal hash of name */
    ActionCallback  action;     /**< user callback */
} DeviceAction;

/** @brief A specific device's hardware */
typedef struct _device_hardware_
{
    char *          type;       /**< type of this devices ("devices.Motor" for example) */
    unsigned int    hash;       /**< internal hash of type */
    List            actions;    /**< list of actions for this device */
} DeviceHardware;

/** @brief An instance of the device's hardware */
struct _device_object_
{
    char *          name;       /**< identifier for this device ("myNuclearProvidedMotor" for example) */
    unsigned int    hash;       /**< internal hash of name */
    DeviceHardware *  hardware; /**< hardware device */
};


// next functions are for private usage.

extern unsigned int initDevicesTable(List * devices);

extern unsigned int initDeviceAction(List *actions);

extern DeviceHardware * getDevicePhysicalByName(List * physicals, const char * name);

extern DeviceObject * getDeviceByName(List * devices, unsigned char * name, unsigned int nameSize);

extern DeviceAction * getDeviceActionByName(DeviceObject * device, unsigned char * name, unsigned int nameSize);

#endif
