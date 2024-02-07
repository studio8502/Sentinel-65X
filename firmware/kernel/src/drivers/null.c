#include <string.h>

#include "kernel/drivers/null.h"
#include "kernel/device.h"
#include "kernel/fcb.h"

static int null_init(void);

static int null_open(struct file_control_block *fcb);

static int null_close(struct file_control_block *fcb);

static int null_read(struct file_control_block *fcb, void *dest, size_t length);

static int null_write(struct file_control_block *fcb, void *src, size_t length);

static int null_get_file_size(struct file_control_block *fcb, size_t *size);

static int null_init_fcb(struct file_control_block *fcb);

Device NullDevice = {
	.init = null_init,
	.open = null_open,
	.close = null_close,
	.read = null_read,
	.write = null_write,
	.get_file_size = null_get_file_size,
	.init_fcb = null_init_fcb
};

static int null_init(void)
{
	device_bind_name("zero", 0, 0);
	device_bind_name("null", 0, 1);
	return 0;
}

static int null_open(struct file_control_block *fcb)
{
	switch (fcb->minor_number) {
	case 0 ... 1:
		fcb->open = true;
		return 0;
	default:
		return -1;
	}
}

static int null_close(struct file_control_block *fcb)
{
	switch (fcb->minor_number) {
	case 0 ... 1:
		fcb->open = false;
		return 0;
	default:
		return -1;
	}
}

static int null_read(struct file_control_block *fcb,
					 void *dest,
					 size_t length)
{
	if (fcb->open == false) {
		return -1;
	}

	switch (fcb->minor_number) {
	case 0:
		memset(dest, 0x00, length);
		return length;
	default:
		return -1;
	}
}

static int null_write(struct file_control_block *fcb,
					  void *src,
					  size_t length)
{
	if (fcb->open == false) {
		return -1;
	}

	(void) src;
	if (fcb->minor_number != 1) {
		return -1;
	} else {
		return length;
	}
}

static int null_get_file_size(struct file_control_block *fcb,
							  size_t *size)
{
	switch (fcb->minor_number) {
	case 0 ... 1:
		*size = 0;
		return 0;
	default:
		return -1;
	}
}

static int null_init_fcb(struct file_control_block *fcb)
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
