#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/dvb/ca.h>
#include <linux/dvb/dmx.h>
#include <linux/dvb/version.h>
#include <linux/dvb/frontend.h>

#include "ci.h"
#include <string.h>

int neutrinoNT_CA_GET_SLOT_INFO(int fd, struct ca_slot_info* info)
{
	struct ca_slot_info i;
	memcpy(&i, info, sizeof(struct ca_slot_info));
	int rc = ioctl(fd, CA_GET_SLOT_INFO, &i);
	memcpy(info, &i, sizeof(struct ca_slot_info));
	return rc;
}

int neutrinoNT_CA_RESET(int fd)
{
	return ioctl(fd, CA_RESET);
}