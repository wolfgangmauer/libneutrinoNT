#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <poll.h>
#include <errno.h>

#include "demuxer.h"

bool neutrinoNT_PesFilter(int fd, DMX_CHANNEL_TYPE type, uint16_t pid, const dmx_input_t input)
{
	if (fd <= 0)
		return false;

	if ((pid >= 0x0002 && pid <= 0x000f) || pid >= 0x1fff)
		return false;

	struct dmx_pes_filter_params pes;
	memset(&pes, 0, sizeof(struct dmx_pes_filter_params));

	pes.pid = pid;
	pes.input = input;
	pes.output = DMX_OUT_DECODER;
	pes.flags = 0;
	switch (type)
	{
	case DMX_VIDEO_CHANNEL:
		pes.pes_type = DMX_PES_VIDEO;
		break;

	case DMX_AUDIO_CHANNEL:
		pes.pes_type = DMX_PES_AUDIO;
		break;

	case DMX_PCR_ONLY_CHANNEL:
		pes.pes_type = DMX_PES_PCR;
		break;

	case DMX_PES_CHANNEL:
		pes.output = DMX_OUT_TAP; 		/* to memory */
		pes.pes_type = DMX_PES_OTHER;
		break;

	case DMX_TP_CHANNEL:
		pes.output = DMX_OUT_TSDEMUX_TAP;     /* to demux */	/* Output multiplexed into a new TS  */
		pes.pes_type = DMX_PES_OTHER;
		break;

	case DMX_PIP_CHANNEL:
		pes.pes_type = DMX_PES_VIDEO1; //for pip channel we need only video
		break;

	default:
		return false;
	}
	if (ioctl(fd, DMX_SET_PES_FILTER, &pes) < 0)
	{
		perror("DMX_SET_PES_FILTER");
		return false;
	}
	return true;
}

static const char* aDMXCHANNELTYPE[] = {
	"",
	"DMX_VIDEO_CHANNEL",
	"DMX_AUDIO_CHANNEL",
	"DMX_PES_CHANNEL",
	"DMX_PSI_CHANNEL",
	"DMX_PIP_CHANNEL",
	"DMX_TP_CHANNEL",
	"DMX_PCR_ONLY_CHANNEL"
};

bool neutrinoNT_SectionFilter(int fd, uint16_t pid, MonoArray* filter, MonoArray* mask, int len, int timeout, MonoArray* mode)
{
	if (fd < 0)
		return false;
	
	unsigned char* _mode = NULL;
	unsigned char* _filter = mono_array_addr(filter, unsigned char, 0);
	unsigned char* _mask = mono_array_addr(mask, unsigned char, 0);
	if (mode != NULL)
		_mode = mono_array_addr(mode, unsigned char, 0);

	struct dmx_sct_filter_params sct;
	memset(&sct, 0, sizeof(struct dmx_sct_filter_params));

	if (len > DMX_FILTER_SIZE)
	{
		len = DMX_FILTER_SIZE;
	}

	/* Pid */
	sct.pid = pid;

	/* filter */
	memcpy(sct.filter.filter, _filter, len);

	/* mask */
	memcpy(sct.filter.mask, _mask, len);

	/* mode */
	if (mode)
		memcpy(sct.filter.mode, _mode, len);

	/* flag */
	sct.flags = DMX_IMMEDIATE_START | DMX_CHECK_CRC;

	/* timeout */
	int to = 0;
	switch (sct.filter.filter[0])
	{
	case 0x00: /* program_association_section */
		to = 2000;
		break;

	case 0x01: /* conditional_access_section */
		to = 6000;
		break;

	case 0x02: /* program_map_section */
		to = 1500;
		break;

	case 0x03: /* transport_stream_description_section */
		to = 10000;
		break;

		/* 0x04 - 0x3F: reserved */

	case 0x40: /* network_information_section - actual_network */
		to = 10000;
		break;

	case 0x41: /* network_information_section - other_network */
		to = 15000;
		break;

	case 0x42: /* service_description_section - actual_transport_stream */
		to = 10000;
		break;

		/* 0x43 - 0x45: reserved for future use */

	case 0x46: /* service_description_section - other_transport_stream */
		to = 10000;
		break;

		/* 0x47 - 0x49: reserved for future use */

	case 0x4A: /* bouquet_association_section */
		to = 11000;
		break;

		/* 0x4B - 0x4D: reserved for future use */

	case 0x4E: /* event_information_section - actual_transport_stream, present/following */
		to = 2000;
		break;

	case 0x4F: /* event_information_section - other_transport_stream, present/following */
		to = 10000;
		break;

	case 0x70: /* time_date_section */ /* UTC */
		sct.flags &= (~DMX_CHECK_CRC); /* section has no CRC */
		sct.flags |= DMX_ONESHOT;
		//sct.pid     = 0x0014;
		to = 30000;
		break;

	case 0x71: /* running_status_section */
		sct.flags &= (~DMX_CHECK_CRC); /* section has no CRC */
		to = 0;
		break;

	case 0x72: /* stuffing_section */
		sct.flags &= (~DMX_CHECK_CRC); /* section has no CRC */
		to = 0;
		break;

	case 0x73: /* time_offset_section */ /* UTC */
		sct.flags |= DMX_ONESHOT;
		//sct.pid     = 0x0014;
		to = 30000;
		break;

		/* 0x74 - 0x7D: reserved for future use */

	case 0x7E: /* discontinuity_information_section */
		sct.flags &= (~DMX_CHECK_CRC); /* section has no CRC */
		to = 0;
		break;

	case 0x7F: /* selection_information_section */
		to = 0;
		break;

		/* 0x80 - 0x8F: ca_message_section */
		/* 0x90 - 0xFE: user defined */
		/*        0xFF: reserved */
	default:
		//return -1;
		break;
	}

	if (timeout == 0 && mode == NULL)
		sct.timeout = to;

	//printf("Pid=0x%x Len=%d Timeout=%d\n", pid, len, sct.timeout);
	/* Set Demux Section Filter() */
	if (ioctl(fd, DMX_SET_FILTER, &sct) < 0)
	{
		perror("DMX_SET_FILTER");
		return false;
	}
	return true;
}

int neutrinoNT_Read(int fd, MonoArray** array, DMX_CHANNEL_TYPE type, int len, int timeout)
{
	int rc;
	struct pollfd ufds;
	ufds.fd = fd;
	ufds.events = POLLIN;
	ufds.revents = 0;

	if (fd < 0)
		return -1;

	if (type == DMX_PSI_CHANNEL && timeout <= 0)
		timeout = 60 * 1000;

	if (timeout > 0)
	{
	retry:
		rc = poll(&ufds, 1, timeout);
		if (!rc)
		{
			return 0; // timeout
		}
		else if (rc < 0)
		{
			if (errno == EINTR)
				goto retry;
			/* we consciously ignore EINTR, since it does not happen in practice */
			return -1;
		}

		if (ufds.revents & POLLHUP) /* we get POLLHUP if e.g. a too big DMX_BUFFER_SIZE was set */
		{
			return -1;
		}

		if (!(ufds.revents & POLLIN)) /* we requested POLLIN but did not get it? */
		{
			return 0;
		}
	}
	uint8_t* buffer = mono_array_addr(*array, uint8_t, 0);
	rc = read(fd, buffer, len);
	if (rc < 0)
		perror("Read");
	return rc;
}
int neutrinoNT_DMX_SET_SOURCE(int fd, dmx_source_t number)
{
	return ioctl(fd, DMX_SET_SOURCE, &number);
}
int neutrinoNT_DMX_SET_BUFFER_SIZE(int fd, int bufferSize)
{
	return ioctl(fd, DMX_SET_BUFFER_SIZE, bufferSize);
}
int neutrinoNT_DMX_START(int fd)
{
	return ioctl(fd, DMX_START);
}
int neutrinoNT_DMX_STOP(int fd)
{
	return ioctl(fd, DMX_STOP);
}
int neutrinoNT_DMX_ADD_PID(int fd, uint16_t pid)
{
	return ioctl(fd, DMX_ADD_PID, pid);
}
int neutrinoNT_DMX_REMOVE_PID(int fd, uint16_t pid)
{
	return ioctl(fd, DMX_REMOVE_PID, pid);
}
int neutrinoNT_DMX_SET_PES_FILTER(int fd, struct dmx_pes_filter_params* params)
{
	return ioctl(fd, DMX_SET_PES_FILTER, params);
}
int neutrinoNT_DMX_SET_FILTER(int fd, struct dmx_sct_filter_params* params)
{
	return ioctl(fd, DMX_SET_PES_FILTER, params);
}
