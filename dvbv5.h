
#pragma once
#include <stdint.h>

#include <linux/dvb/dmx.h>
#include <linux/dvb/version.h>
#include <linux/dvb/frontend.h>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/appdomain.h>
#include <mono/metadata/object.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/mono-gc.h>
#include <mono/utils/mono-publib.h>
#include <mono/metadata/loader.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <libdvbv5/dvb-dev.h>
#include <libdvbv5/sdt.h>
#include <libdvbv5/pmt.h>
#include <libdvbv5/eit.h>
#include <libdvbv5/pat.h>
#include <libdvbv5/nit.h>

#ifdef __cplusplus
}
#endif
int neutrinoNT_dvb_table_pmt_init(struct dvb_v5_fe_parms *parms, MonoArray* buf, int buflen, struct dvb_table_pmt **table);
int neutrinoNT_dvb_table_sdt_init(struct dvb_v5_fe_parms *parms, MonoArray* buf, int buflen, struct dvb_table_sdt **table);
dvb_open_descriptor* neutrinoNT_dvb_dev_open(dvb_device *dvb, dvb_dev_list* dvb_dmx, int flags);
struct dvb_v5_fe_parms* neutrinoNT_dvb_dev_get_params(dvb_device* dvb_device);
int neutrinoNT_dvb_poll(int fd, unsigned int seconds);
int neutrinoNT_dvb_dev_dmx_set_section_filter(dvb_open_descriptor *open_dev, int pid, unsigned filtsize, MonoArray* filter,MonoArray* mask, MonoArray* mode, unsigned int flags);
int neutrinoNT_dvb_dev_read(dvb_open_descriptor *open_dev, MonoArray* buffer, unsigned count);
