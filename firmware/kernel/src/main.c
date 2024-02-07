//*****************************************************************************
//  Turaco-DOS
//
//  src/kernel/main.c
//*****************************************************************************

#include "config.h"
#include "turaco.h"

#include "kernel/device.h"

void
main(void)
{
	device_init_all();

	for (;;) {}
}
