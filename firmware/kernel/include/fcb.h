#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "device.h"
#include "drivers/fatfs/ff.h"

enum file_type {
        FILE_TYPE_NORMAL,
        FILE_TYPE_DIRECTORY,
		FILE_TYPE_DEVICE
};

struct file_control_block {
        // The full path of the file, including its volume and basename.
        char *pathname;

        // The basename of the file. This usually points to
        // the begining of the basename of the file in the
        // pathname string.
        char *basename;

        // The type of the file.
        enum file_type type;

		bool open;

		union {
			// In the case of a file on a FATFS filesystem, this
			// points to the FIL structure the driver uses to manage
			// the file.
			FIL *fat_info;

			// Generic driver-specific data pointer
			void *userdata;
		};

		// The device number identifies the device driver responsible for
		// the file.
		unsigned short device_number;
};

// Using the pathname in the provided FCB, identify the device which manages
// the file and have that device populate the FCB.
int fcb_init(char *pathname, struct file_control_block *fcb);

// Opens a file
static inline int fcb_open(struct file_control_block *fcb)
{
        if (fcb == NULL) {
                return -1;
        }

        if (device[fcb->device_number]->open != NULL) {
                return device[fcb->device_number]->open(fcb);
        } else {
                return -1;
        }
}

// Closes an open file, given a unique ID.
static inline int fcb_close(struct file_control_block *fcb)
{
        if (fcb == NULL) {
                return -1;
        }

        if (device[fcb->device_number]->close != NULL) {
                return device[fcb->device_number]->close(fcb);
        } else {
                return -1;
        }
}

// Seeks within an open file, given a unique ID and a length.
static inline int fcb_seek(struct file_control_block *fcb, int32_t length)
{
        if (fcb == NULL) {
                return -1;
        }

        if (device[fcb->device_number]->seek != NULL) {
                return device[fcb->device_number]->seek(fcb, length);
        } else {
                return -1;
        }
}

// Reads data from the specified file.
static inline int fcb_read(struct file_control_block *fcb, void *dest, size_t length)
{
        if (fcb == NULL || dest == NULL) {
                return -1;
        }

        if (device[fcb->device_number]->read != NULL) {
                return device[fcb->device_number]->read(fcb, dest, length);
        } else {
                return -1;
        }
}

// Writes data to the specified file.
static inline int fcb_write(struct file_control_block *fcb, void *src, size_t length)
{
        if (fcb == NULL || src == NULL) {
                return -1;
        }

        if (device[fcb->device_number]->write != NULL) {
                return device[fcb->device_number]->write(fcb, src, length);
        } else {
                return -1;
        }
}

// Creates the specified file given a pathname.
static inline int fcb_create(struct file_control_block *fcb)
{
        if (fcb == NULL) {
                return -1;
        }

        if (device[fcb->device_number]->create != NULL) {
                return device[fcb->device_number]->create(fcb);
        } else {
                return -1;
        }
}

// Copies the specified file using the specified names.
static inline int fcb_copy(struct file_control_block *src, struct file_control_block *dest)
{
        if (src == NULL || dest == NULL) {
                return -1;
        }

        if (device[src->device_number]->copy != NULL) {
                return device[src->device_number]->copy(src, dest);
        } else {
                return -1;
        }
}

// Moves the specified file using the specified names.
static inline int fcb_move(struct file_control_block *src, struct file_control_block *dest)
{
        if (src == NULL || dest == NULL) {
                return -1;
        }

        if (device[src->device_number]->move != NULL) {
                return device[src->device_number]->move(src, dest);
        } else {
                return -1;
        }
}

// Gets the size of the file.
static inline int fcb_get_file_size(struct file_control_block *fcb, size_t *size)
{
        if (fcb == NULL) {
                return -1;
        }

        if (device[fcb->device_number]->get_file_size != NULL) {
                return device[fcb->device_number]->get_file_size(fcb, size);
        } else {
                return -1;
        }
}
