#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/stat.h>
/* system c */
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <errno.h>

#include "frontend.h"

int neutrinoNT_FE_GET_INFO(int fd, struct dvb_frontend_info* info)
{
	return ioctl(fd, FE_GET_INFO, info);
}

int neutrinoNT_FE_READ_STATUS(int fd, fe_status_t* status)
{
	return ioctl(fd, FE_READ_STATUS, status);
}

int neutrinoNT_FE_READ_SIGNAL_STRENGTH(int fd, uint16_t* strength)
{
	return ioctl(fd, FE_READ_SIGNAL_STRENGTH, strength);
}

int neutrinoNT_FE_READ_BER(int fd, uint32_t* ber)
{
	return ioctl(fd, FE_READ_BER, ber);
}

int neutrinoNT_FE_READ_SNR(int fd, uint16_t* snr)
{
	return ioctl(fd, FE_READ_SNR, snr);
}

int neutrinoNT_FE_READ_UNCORRECTED_BLOCKS(int fd, uint32_t* uncorrected_blocks)
{
	return ioctl(fd, FE_READ_UNCORRECTED_BLOCKS, uncorrected_blocks);
}

int neutrinoNT_FE_SET_TONE(int fd, fe_sec_tone_mode_t toneMode)
{
	return ioctl(fd, FE_SET_TONE, &toneMode);
}

int neutrinoNT_FE_SET_VOLTAGE(int fd, fe_sec_voltage_t voltage)
{
	return ioctl(fd, FE_SET_VOLTAGE, &voltage);
}

int neutrinoNT_FE_DISEQC_SEND_MASTER_CMD(int fd, struct dvb_diseqc_master_cmd cmd)
{
	return ioctl(fd, FE_DISEQC_SEND_MASTER_CMD, &cmd);
}

#define TIME_STEP 		200
#define TIMEOUT_MAX_MS		9000

int neutrinoNT_FE_RESET(int fd, int adapter, int number)
{
	int retVal = -1;
#if 1
	close(fd);

	usleep(150000);

	char filename[128];

	sprintf(filename, "/dev/dvb/adapter%d/frontend%d", adapter, number);

	printf("cFrontend(%d,%d) reset %s\n", adapter, number, filename);
	if ((retVal = open(filename, O_RDWR | O_NONBLOCK | O_SYNC)) < 0)
		perror(filename);

	usleep(150000);
#endif
	return retVal;
}

int neutrinoNT_FE_GET_EVENT(int fd, struct dvb_frontend_event* event)
{
	return ioctl(fd, FE_GET_EVENT, event);
}

#define MAXFRONTENDCMDS 16
struct dtv_property frontend[MAXFRONTENDCMDS];
struct dtv_properties cmdSeq;

void neutrinoNT_FE_CLEAR_PROPERTIES()
{
	memset(&frontend, 0, sizeof(frontend));
	memset(&cmdSeq, 0, sizeof(cmdSeq));
	cmdSeq.props = frontend;
}

void neutrinoNT_FE_SET_PROPERTY_DATA(uint32_t cmd, uint32_t value)
{
	frontend[cmdSeq.num].cmd = cmd;
	frontend[cmdSeq.num].u.data = value;
	cmdSeq.num++;
}

int neutrinoNT_FE_SET_PROPERTY(int fd)
{
	int retVal = -1;
	retVal = ioctl(fd, FE_SET_PROPERTY, &cmdSeq);
	neutrinoNT_FE_CLEAR_PROPERTIES();
	return retVal;
}
int neutrinoNT_FE_GET_FRONTEND(int fd, struct dvb_frontend_parameters* parms)
{
	struct dvb_frontend_parameters feparams = { 0 };
	parms = &feparams;
	return ioctl(fd, FE_GET_FRONTEND, &feparams);
}
int neutrinoNT_FE_SET_FRONTEND(int fd, struct dvb_frontend_parameters* feparams)
{
	return ioctl(fd, FE_SET_FRONTEND, feparams);
}
