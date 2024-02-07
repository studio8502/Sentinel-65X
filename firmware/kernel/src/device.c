/******************************************************************************
ESPER 65X Kernel

Copyright © 2023 Kyle J Cardoza. All rights reserved.

Released under the terms of the MIT license. See COPYING.md for the full text
of this license.
******************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "device.h"
#include "fcb.h"
#include "drivers/null.h"
#include "drivers/random.h"
#include "drivers/spi.h"

static bool init_all_run = false;

Device *device[DEVICE_MAX] = {
	&NullDevice,
	&RandomDevice,
	&SPIDevice
};

struct device_map *device_map[DEVICE_MAP_MAX] = {0};

static short get_lowest_free_device(void);

void device_init_all(void)
{
	if (init_all_run == true) {
		return;
	}

	for (int i = 0; i < DEVICE_MAX; i += 1) {
		if (device[i] != NULL) {
			if (device[i]->init != NULL) {
				device[i]->init();
			}
		}
	}

	init_all_run = true;
}

int device_bind_name(char *name,
					 unsigned short major_number,
					 unsigned short minor_number)
{
	if (name == NULL) {
		return -1;
	}

	// It is not permissible to have the same name attached to two
	// devices.
	for (int i = 0; i < DEVICE_MAP_MAX; i += 1) {
		if (strcmp(device_map[i]->name, name) == 0) {
			return -1;
		}
	}

	short device_index = get_lowest_free_device();
	if (device_index == -1) {
		return -1;
	}

	char *device_name = strdup(name);
	if (name == NULL) {
		return -1;
	}

	device_map[device_index] = calloc(1, sizeof(struct device_map));
	if (device_map[device_index] == NULL) {
		free(device_name);
		return -1;
	} else {
		device_map[device_index]->major_number = major_number;
		device_map[device_index]->minor_number = minor_number;
		device_map[device_index]->name = device_name;
		return 0;
	}
}

int device_unbind_name(char *name)
{
	if (name == NULL) {
		return -1;
	}

	for (int i = 0; i < DEVICE_MAP_MAX; i += 1) {
		if (strcmp(device_map[i]->name, name) == 0) {
			free(device_map[i]->name);
			free(device_map[i]);
			device_map[i] = NULL;
			return 0;
		}
	}

	return -1;
}

int device_get_by_name(char *name, Device **device)
{
	if (name == NULL || device == NULL) {
		return -1;
	}

	for (int i = 0; i < DEVICE_MAP_MAX; i += 1) {
		if (strcmp(device_map[i]->name, name) == 0) {
			unsigned short major_number = device_map[i]->major_number;
			*device = device[major_number];
			return 0;
		}
	}
	return -1;
}

static short get_lowest_free_device(void)
{
	for (int i =  0; i < DEVICE_MAP_MAX; i += 1) {
		if (device_map[i] == NULL) {
			return i;
		}
	}
	return -1;
}
