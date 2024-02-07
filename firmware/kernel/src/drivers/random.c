#include <stdlib.h>
#include <string.h>

#include "kernel/drivers/null.h"
#include "kernel/device.h"
#include "kernel/fcb.h"

static int random_init(void);

static int random_open(struct file_control_block *fcb);

static int random_close(struct file_control_block *fcb);

static int random_read(struct file_control_block *fcb,
					   void *dest,
					   size_t length);

static int random_get_file_size(struct file_control_block *fcb, size_t *size);

static int random_init_fcb(struct file_control_block *fcb);

Device RandomDevice = {
	.init = random_init,
	.open = random_open,
	.close = random_close,
	.read = random_read,
	.get_file_size = random_get_file_size,
	.init_fcb = random_init_fcb
};

static int random_init(void)
{
	srand(0);
	device_bind_name("random", 1, 0);
	return 0;
}

static int random_open(struct file_control_block *fcb)
{
	switch (fcb->minor_number) {
	case 0:
		fcb->open = true;
		return 0;
	default:
		return -1;
	}
}

static int random_close(struct file_control_block *fcb)
{
	switch (fcb->minor_number) {
	case 0:
		fcb->open = false;
		return 0;
	default:
		return -1;
	}
}

static int random_read(struct file_control_block *fcb,
					   void *dest,
					   size_t length)
{
	if (fcb->open == false) {
		return -1;
	}

	unsigned char *target = dest;

	switch (fcb->minor_number) {
	case 0:
		for (unsigned int i = 0; i < length; i += 1) {
			target[i] = (unsigned short) (rand() % 0xFF);
		}
		return length;
	default:
		return -1;
	}
}

static int random_get_file_size(struct file_control_block *fcb,
							    size_t *size)
{
	switch (fcb->minor_number) {
	case 0:
		*size = 0;
		return 0;
	default:
		return -1;
	}
}

static int random_init_fcb(struct file_control_block *fcb)
{
	if (fcb->major_number != 0) {
		return -1;
	}

	switch (fcb->minor_number) {
	case 0 ... 1:
		fcb->open = false;
		fcb->type = FILE_TYPE_DEVICE;
		return 0;
	default:
		return -1;
	}
}
