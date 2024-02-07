#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// This symbol determines the maximum number of device drivers which
// can be in memory.
#ifndef DEVICE_MAX
#define DEVICE_MAX 32
#endif

// This symbol determines the maximum number of device map entries which
// ca be in memory.
#ifndef DEVICE_MAP_MAX
#define DEVICE_MAP_MAX 32
#endif

// Forward declaration.
struct file_control_block;

// A device, in this context, is a code module which exposes a defined set
// of functions for interacting with files and file-like data. It is not specific
// as to the nature of the underlying data storage. It is equally valid for a
// device to use a block of RAM or a serial device as it is a hard drive
// or SD card.
//
// None of these functions are required to actually do anyting if it is not
// sensible for the kind of device being used; for example, it is not
// sensible for an inherently read-only device to support moving or
// renaming files.
typedef struct {
        // Initialize the device.
        int (*init)(void);

        // Opens a file, given a pathname.
        int (*open)(struct file_control_block *fcb);

        // Closes an open file, given a unique ID.
        int (*close)(struct file_control_block *fcb);

        // Seeks within an open file, given a unique ID and a length.
        int (*seek)(struct file_control_block *fcb, long length);

        // Reads data from the specified file.
        int (*read)(struct file_control_block *fcb, void *dest, size_t length);

        // Writes data to the specified file.
        int (*write)(struct file_control_block *fcb, void *src, size_t length);

		// Perform driver-specific operations.
		int (*ioctl)(struct file_control_block *fcb,
					 unsigned short operation,
					 void *arg);

        // Creates the specified file given a pathname.
        int (*create)(struct file_control_block *fcb);

        // Copies the specified file using the specified names.
        int (*copy)(struct file_control_block *src,
				    struct file_control_block *dest);

        // Moves the specified file using the specified names.
        int (*move)(struct file_control_block *src,
					struct file_control_block *dest);

        // Gets the size of the file.
        int (*get_file_size)(struct file_control_block *fcb, size_t *size);

        // Fills out the metadata in the specified FCB from the pathname
        // in the provided FCB.
        int (*init_fcb)(struct file_control_block *fcb);
} Device;

// The device map is a table that maps device names, such as SD0: or
// TTY2: to the device driver that manages the device.
struct device_map {
        char *name;
        unsigned short major_number;
        unsigned short minor_number;
};

// The global table of device drivers.
extern Device *device[DEVICE_MAX];

// The global map of device names to device modules.
extern struct device_map *device_map[DEVICE_MAP_MAX];

// Initialize all the device drivers. This is called once, at boot.
// It protects itself against being called again without a reset.
void device_init_all(void);

// Binds a device name to a device.
int device_bind_name(char *name,
					 unsigned short major_number,
					 unsigned short minor_number);

// Unbinds a bound device name.
int device_unbind_name(char *name);

// Get a bound device by its name.
int device_get_by_name(char *name, Device **device);
