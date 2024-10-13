
#pragma once
#include <libdvbv5/dvb-dev.h>

dvb_open_descriptor* neutrinoNT_dvb_dev_open(dvb_device *dvb, dvb_dev_list* dvb_dmx, int flags);
struct dvb_v5_fe_parms* neutrinoNT_dvb_dev_get_params(dvb_device* dvb_device);
int neutrinoNT_dvb_poll(int fd, unsigned int seconds);
int neutrinoNT_dvb_dev_dmx_set_section_filter(dvb_open_descriptor *open_dev, pid, unsigned filtsize, MonoArray* filter,MonoArray* mask, MonoArray* mode, unsigned int flags = DMX_IMMEDIATE_START | DMX_CHECK_CRC);
