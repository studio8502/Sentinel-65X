#include <stdlib.h>
#include <string.h>

#include "fcb.h"
#include "device.h"

// Using the pathname string, identify the major/minor device for
// the file, and have that device initialize the file control
// block.
int fcb_init(char *pathname, struct file_control_block *fcb)
{
	// First thing, we need to identify the device. The pathname
	// is to be fully-qualified; this means it must have the
	// device name, followed by a colon, followed by an optional
	// file path. If the file path part is empty, then the FBC
	// refers to the device itself. We perform the identification
	// by first copying the pathname, then tokenizing the copy on
	// the ":" character. The first token must be a string which
	// matches a registered device in the device map.
	// Then we populate the located major and minor numbers and copy
	// the pathname into the FCB, and pass it along to the device
	// driver for more initialization.

	char *path = strdup(pathname);
	if (path == NULL) {
		return -1;
	}

	char *dev = strtok(path, ":");

	for (unsigned short i = 0; i < DEVICE_MAP_MAX; i += 1) {
		if (strcmp(dev, device_map[i]->name) == 0) {
			fcb->pathname = strdup(pathname);
			free(path);

			if (fcb->pathname == NULL) {
				return -1;
			}

			fcb->device_number = device_map[i]->major_number;

			return device[fcb->major_number]->init_fcb(fcb);
		}
	}

	free(path);

	return -1;
}
