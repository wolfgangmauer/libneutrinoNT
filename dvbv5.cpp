
#include "dvbv5.h"

dvb_open_descriptor* neutrinoNT_dvb_dev_open(dvb_device *dvb, dvb_dev_list* dvb_dmx, int flags)
{
	return dvb_dev_open(dvb, dvb_dmx->sysname, flags);
}

struct dvb_v5_fe_parms* neutrinoNT_dvb_dev_get_params(dvb_device* dvb_device)
{
	return dvb_device->fe_parms;
}
int neutrinoNT_dvb_poll(int fd, unsigned int seconds)
{
    fd_set set;
    struct timeval timeout;
    int ret;

    /* Initialize the file descriptor set. */
    FD_ZERO(&set);
    FD_SET(fd, &set);

    /* Initialize the timeout data structure. */
    //timeout.tv_sec = milliseconds / 1000;
    //timeout.tv_usec = (milliseconds % 1000) * 1000;
    timeout.tv_sec = seconds;
    timeout.tv_usec = 0;

    /* `select' logfuncreturns 0 if timeout, 1 if input available, -1 if error. */
    do ret = select(FD_SETSIZE, &set, NULL, NULL, &timeout);
    while (ret == -1 && errno == EINTR);

    return ret;
}
