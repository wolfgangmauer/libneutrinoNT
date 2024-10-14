
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

#include "libdvbv5/dvb-dev.h"
#include "libdvbv5/dvb-demux.h"
#include "libdvbv5/dvb-fe.h"
#include "libdvbv5/dvb-scan.h"
#include "libdvbv5/pat.h"
#include "libdvbv5/pmt.h"
#include "libdvbv5/nit.h"
#include "libdvbv5/sdt.h"
#include "libdvbv5/eit.h"
#include "libdvbv5/header.h"
#include "libdvbv5/descriptors.h"
#include "libdvbv5/desc_language.h"
#include "libdvbv5/desc_network_name.h"
#include "libdvbv5/desc_cable_delivery.h"
#include "libdvbv5/desc_sat.h"
#include "libdvbv5/desc_terrestrial_delivery.h"
#include "libdvbv5/desc_service.h"
#include "libdvbv5/desc_frequency_list.h"
#include "libdvbv5/desc_event_short.h"
#include "libdvbv5/desc_ca_identifier.h"
#include <libdvbv5/desc_ca.h>
#include "libdvbv5/desc_event_extended.h"
#include "libdvbv5/desc_hierarchy.h"

#ifdef __cplusplus
}
#endif
int neutrinoNT_dvb_desc_get_type(dvb_desc* descriptor);
dvb_table_sdt_service* neutrinoNT_dvb_table_service_first(dvb_table_sdt* table);
dvb_table_sdt_service* neutrinoNT_dvb_table_service_next(dvb_table_sdt_service* service);
dvb_table_pmt_stream* neutrinoNT_dvb_table_stream_first(dvb_table_pmt* table);
dvb_table_pmt_stream* neutrinoNT_dvb_table_stream_next(dvb_table_pmt_stream* stream);
dvb_table_eit_event* neutrinoNT_dvb_table_event_first(dvb_table_eit* table);
dvb_table_eit_event* neutrinoNT_dvb_table_event_next(dvb_table_eit_event* event);
int neutrinoNT_dvb_eit_descriptor_get(dvb_table_eit_event* event, MonoString** name, MonoString** language, MonoString** text, long* starttime, uint* duration);

dvb_table_nit_transport* neutrinoNT_dvb_table_transport_first(dvb_table_nit* table);
dvb_table_nit_transport* neutrinoNT_dvb_table_transport_next(dvb_table_nit_transport* transport);

dvb_desc* neutrinoNT_dvb_descriptor_next(dvb_desc* descriptor);

dvb_desc* neutrinoNT_dvb_sdt_descriptor_first(dvb_table_sdt_service* service);
dvb_desc* neutrinoNT_dvb_pmt_descriptor_first(dvb_table_pmt_stream* stream);
dvb_desc* neutrinoNT_dvb_nit_descriptor_first(dvb_table_nit_transport* transport);
dvb_desc* neutrinoNT_dvb_eit_descriptor_first(dvb_table_eit_event* event);

int neutrinoNT_dvb_table_pmt_init(dvb_v5_fe_parms *parms, MonoArray* buf, int buflen, dvb_table_pmt **table);
int neutrinoNT_dvb_table_sdt_init(dvb_v5_fe_parms *parms, MonoArray* buf, int buflen, dvb_table_sdt **table);
int neutrinoNT_dvb_table_nit_init(dvb_v5_fe_parms *parms, MonoArray* buf, int buflen, dvb_table_nit **table);
int neutrinoNT_dvb_table_eit_init(dvb_v5_fe_parms *parms, MonoArray* buf, int buflen, dvb_table_eit **table);

dvb_open_descriptor* neutrinoNT_dvb_dev_open(dvb_device *dvb, dvb_dev_list* dvb_dmx, int flags);
//int neutrinoNT_dvb_poll(int fd, unsigned int seconds);
int neutrinoNT_dvb_poll(dvb_v5_fe_parms *parms, int fd, unsigned int seconds);
int neutrinoNT_dvb_dev_dmx_set_section_filter(dvb_open_descriptor *open_dev, int pid, unsigned filtsize, MonoArray* filter,MonoArray* mask, MonoArray* mode, unsigned int flags);
int neutrinoNT_dvb_dev_read(dvb_open_descriptor *open_dev, MonoArray** buffer, unsigned count);
