
#include "dvbv5.h"

int neutrinoNT_dvb_eit_descriptor_get(dvb_table_eit_event* event, MonoString** name, MonoString** language, MonoString** text, long* starttime, uint* duration)
{
	*starttime = event->start.tm_gmtoff;
	*duration = event->duration;
	dvb_desc_foreach(_descriptor, event)
	{
	    switch (_descriptor->type) {
	    case short_event_descriptor:
	    {
		auto shortEventDescriptor = (dvb_desc_event_short*)_descriptor;
		*name = mono_string_new(mono_domain_get(), shortEventDescriptor->name);
		*language = mono_string_new(mono_domain_get(), (char*)shortEventDescriptor->language);
	    }
	    break;
	    case extended_event_descriptor:
		auto extendedEventDescriptor = (dvb_desc_event_extended*)_descriptor;
		if (extendedEventDescriptor->text)
		    *text = mono_string_new(mono_domain_get(), extendedEventDescriptor->text);
		break;
	    }
	}
	return 0;
}

int neutrinoNT_dvb_desc_get_type(dvb_desc* descriptor)
{
	return (int)descriptor->type;
}
dvb_table_nit_transport* neutrinoNT_dvb_table_transport_first(dvb_table_nit* table)
{
	return table->transport;
}
dvb_table_nit_transport* neutrinoNT_dvb_table_transport_next(dvb_table_nit_transport* transport)
{
	return transport->next;
}
dvb_table_sdt_service* neutrinoNT_dvb_table_service_first(dvb_table_sdt* table)
{
	return table->service;
}
dvb_table_sdt_service* neutrinoNT_dvb_table_service_next(dvb_table_sdt_service* service)
{
	return service->next;
}
dvb_table_pmt_stream* neutrinoNT_dvb_table_stream_first(dvb_table_pmt* table)
{
	return table->stream;
}
dvb_table_pmt_stream* neutrinoNT_dvb_table_stream_next(dvb_table_pmt_stream* stream)
{
	return stream->next;
}
dvb_table_eit_event* neutrinoNT_dvb_table_event_first(dvb_table_eit* table)
{
	return table->event;
}
dvb_table_eit_event* neutrinoNT_dvb_table_event_next(dvb_table_eit_event* event)
{
	return event->next;
}
dvb_desc* neutrinoNT_dvb_descriptor_next(dvb_desc* descriptor)
{
	return descriptor->next;
}
dvb_desc* neutrinoNT_dvb_sdt_descriptor_first(dvb_table_sdt_service* service)
{
	return service->descriptor;
}
dvb_desc* neutrinoNT_dvb_pmt_descriptor_first(dvb_table_pmt_stream* stream)
{
	return stream->descriptor;
}
dvb_desc* neutrinoNT_dvb_nit_descriptor_first(dvb_table_nit_transport* transport)
{
	return transport->descriptor;
}
dvb_desc* neutrinoNT_dvb_eit_descriptor_first(dvb_table_eit_event* event)
{
	return event->descriptor;
}
int neutrinoNT_dvb_table_pmt_init(dvb_v5_fe_parms *parms, MonoArray* buf, int buflen, dvb_table_pmt **table)
{
	unsigned char* _buf = mono_array_addr(buf, unsigned char, 0);
	return dvb_table_pmt_init(parms, _buf, buflen, table);
}
int neutrinoNT_dvb_table_sdt_init(dvb_v5_fe_parms *parms, MonoArray* buf, int buflen, dvb_table_sdt **table)
{
	unsigned char* _buf = mono_array_addr(buf, unsigned char, 0);
	return dvb_table_sdt_init(parms, _buf, buflen, table);
}
int neutrinoNT_dvb_table_nit_init(dvb_v5_fe_parms *parms, MonoArray* buf, int buflen, dvb_table_nit **table)
{
	unsigned char* _buf = mono_array_addr(buf, unsigned char, 0);
	return dvb_table_nit_init(parms, _buf, buflen, table);
}
int neutrinoNT_dvb_table_eit_init(dvb_v5_fe_parms *parms, MonoArray* buf, int buflen, dvb_table_eit **table)
{
	unsigned char* _buf = mono_array_addr(buf, unsigned char, 0);
	return dvb_table_eit_init(parms, _buf, buflen, table);
}
int neutrinoNT_dvb_dev_read(dvb_open_descriptor *open_dev, MonoArray** buffer, unsigned count)
{
	unsigned char* _buffer = mono_array_addr(*buffer, unsigned char, 0);
	return dvb_dev_read(open_dev, _buffer, count);
}
int neutrinoNT_dvb_dev_dmx_set_section_filter(dvb_open_descriptor *open_dev, int pid, unsigned filtsize, MonoArray* filter,MonoArray* mask, MonoArray* mode, unsigned int flags)
{
	unsigned char* _mode = NULL;
	unsigned char* _filter = mono_array_addr(filter, unsigned char, 0);
	unsigned char* _mask = mono_array_addr(mask, unsigned char, 0);
	if (mode != NULL)
		_mode = mono_array_addr(mode, unsigned char, 0);
	return dvb_dev_dmx_set_section_filter(open_dev, pid, filtsize, _filter, _mask, _mode, flags);
}
dvb_open_descriptor* neutrinoNT_dvb_dev_open(dvb_device *dvb, dvb_dev_list* dvb_dmx, int flags)
{
	return dvb_dev_open(dvb, dvb_dmx->sysname, flags);
}
int neutrinoNT_dvb_poll(struct dvb_v5_fe_parms *parms, int fd, unsigned int seconds)
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
    while (!parms->abort && ret == -1 && errno == EINTR);
    return ret;
}
