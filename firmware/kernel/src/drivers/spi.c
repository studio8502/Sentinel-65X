#include <string.h>

#include "kernel/drivers/spi.h"
#include "kernel/device.h"
#include "kernel/fcb.h"

static int spi_init(void);

Device SPIDevice = {
	.init = spi_init
};

static int spi_init(void)
{
	device_bind_name("spi0", 2, 0);
	device_bind_name("spi1", 2, 1);
	device_bind_name("spi2", 2, 2);
	device_bind_name("spi3", 2, 3);
	device_bind_name("spi4", 2, 4);
	device_bind_name("spi5", 2, 5);
	device_bind_name("spi6", 2, 6);
	device_bind_name("spi7", 2, 7);
	return 0;
}
