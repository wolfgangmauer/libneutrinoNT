#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cerrno>

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


#include "ci.h"
#include "demuxer.h"
#include "decoder.h"
#include "frontend.h"
#include "dvbv5.h"

#define LED_IOCTL_BRIGHTNESS_NORMAL 0X10
#define LED_IOCTL_BRIGHTNESS_DEEPSTANDBY 0X11
#define LED_IOCTL_BLINKING_TIME 0X12
#define LED_IOCTL_SET_DEFAULT 0x13

void neutrinoNT_SET_LED(int value, int what)
{
    int lcdfd = open("/dev/dbox/lcd0", O_RDWR);
	ioctl(lcdfd, what, (unsigned char)value);
    close(lcdfd);
}

extern "C" void InitlibNeutrinoNT()
{
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_PesFilter", (void*)neutrinoNT_PesFilter);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_SectionFilter", (void*)neutrinoNT_SectionFilter);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_Read", (void*)neutrinoNT_Read);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_DMX_REMOVE_PID", (void*)neutrinoNT_DMX_REMOVE_PID);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_DMX_ADD_PID", (void*)neutrinoNT_DMX_ADD_PID);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_DMX_SET_PES_FILTER", (void*)neutrinoNT_DMX_SET_PES_FILTER);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_DMX_SET_FILTER", (void*)neutrinoNT_DMX_SET_FILTER);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_DMX_STOP", (void*)neutrinoNT_DMX_STOP);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_DMX_START", (void*)neutrinoNT_DMX_START);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_DMX_SET_SOURCE", (void*)neutrinoNT_DMX_SET_SOURCE);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_DMX_SET_BUFFER_SIZE", (void*)neutrinoNT_DMX_SET_BUFFER_SIZE);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_VIDEO_SELECT_SOURCE", (void*)neutrinoNT_VIDEO_SELECT_SOURCE);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_VIDEO_SET_STREAMTYPE", (void*)neutrinoNT_VIDEO_SET_STREAMTYPE);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_VIDEO_CLEAR_BUFFER", (void*)neutrinoNT_VIDEO_CLEAR_BUFFER);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_VIDEO_CONTINUE", (void*)neutrinoNT_VIDEO_CONTINUE);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_VIDEO_FREEZE", (void*)neutrinoNT_VIDEO_FREEZE);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_VIDEO_SLOWMOTION", (void*)neutrinoNT_VIDEO_SLOWMOTION);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_VIDEO_FAST_FORWARD", (void*)neutrinoNT_VIDEO_FAST_FORWARD);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_VIDEO_STOP", (void*)neutrinoNT_VIDEO_STOP);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_VIDEO_PLAY", (void*)neutrinoNT_VIDEO_PLAY);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_AUDIO_SELECT_SOURCE", (void*)neutrinoNT_AUDIO_SELECT_SOURCE);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_AUDIO_CHANNEL_SELECT", (void*)neutrinoNT_AUDIO_CHANNEL_SELECT);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_AUDIO_SET_AV_SYNC", (void*)neutrinoNT_AUDIO_SET_AV_SYNC);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_AUDIO_SET_STREAMTYPE", (void*)neutrinoNT_AUDIO_SET_STREAMTYPE);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_AUDIO_CLEAR_BUFFER", (void*)neutrinoNT_AUDIO_CLEAR_BUFFER);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_AUDIO_CONTINUE", (void*)neutrinoNT_AUDIO_CONTINUE);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_AUDIO_PAUSE", (void*)neutrinoNT_AUDIO_PAUSE);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_AUDIO_STOP", (void*)neutrinoNT_AUDIO_STOP);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_AUDIO_PLAY", (void*)neutrinoNT_AUDIO_PLAY);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_AUDIO_SET_MIXER", (void*)neutrinoNT_AUDIO_SET_MIXER);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_AUDIO_SET_MUTE", (void*)neutrinoNT_AUDIO_SET_MUTE);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_FE_GET_INFO", (void*)neutrinoNT_FE_GET_INFO);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_FE_READ_STATUS", (void*)neutrinoNT_FE_READ_STATUS);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_FE_READ_SNR", (void*)neutrinoNT_FE_READ_SNR);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_FE_READ_BER", (void*)neutrinoNT_FE_READ_BER);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_FE_READ_UNCORRECTED_BLOCKS", (void*)neutrinoNT_FE_READ_UNCORRECTED_BLOCKS);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_FE_GET_EVENT", (void*)neutrinoNT_FE_GET_EVENT);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_FE_GET_FRONTEND", (void*)neutrinoNT_FE_GET_FRONTEND);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_FE_SET_FRONTEND", (void*)neutrinoNT_FE_SET_FRONTEND);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_FE_READ_SIGNAL_STRENGTH", (void*)neutrinoNT_FE_READ_SIGNAL_STRENGTH);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_FE_SET_TONE", (void*)neutrinoNT_FE_SET_TONE);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_FE_CLEAR_PROPERTIES", (void*)neutrinoNT_FE_CLEAR_PROPERTIES);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_FE_SET_PROPERTY_DATA", (void*)neutrinoNT_FE_SET_PROPERTY_DATA);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_FE_SET_PROPERTY", (void*)neutrinoNT_FE_SET_PROPERTY);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_CA_GET_SLOT_INFO", (void*)neutrinoNT_CA_GET_SLOT_INFO);
	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_CA_RESET", (void*)neutrinoNT_CA_RESET);

	mono_add_internal_call("neutrinoNT.NativeMethods::neutrinoNT_SET_LED", (void*)neutrinoNT_SET_LED);

	mono_add_internal_call("dvbv5.NativeMethods::dvb_dev_open", (void*)neutrinoNT_dvb_dev_open);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_dev_dmx_set_section_filter", (void*)neutrinoNT_dvb_dev_dmx_set_section_filter);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_poll", (void*)neutrinoNT_dvb_poll);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_dev_read", (void*)neutrinoNT_dvb_dev_read);
	
	mono_add_internal_call("dvbv5.NativeMethods::dvb_table_pmt_init", (void*)neutrinoNT_dvb_table_pmt_init);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_table_sdt_init", (void*)neutrinoNT_dvb_table_sdt_init);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_table_nit_init", (void*)neutrinoNT_dvb_table_nit_init);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_table_eit_init", (void*)neutrinoNT_dvb_table_eit_init);

	mono_add_internal_call("dvbv5.NativeMethods::dvb_table_sdt_first", (void*)neutrinoNT_dvb_table_service_first);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_table_sdt_next", (void*)neutrinoNT_dvb_table_service_next);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_table_pmt_first", (void*)neutrinoNT_dvb_table_stream_first);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_table_pmt_next", (void*)neutrinoNT_dvb_table_stream_next);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_table_eit_first", (void*)neutrinoNT_dvb_table_event_first);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_table_eit_next", (void*)neutrinoNT_dvb_table_event_next);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_eit_descriptor_get", (void*)neutrinoNT_dvb_eit_descriptor_get);
	
	mono_add_internal_call("dvbv5.NativeMethods::dvb_table_nit_first", (void*)neutrinoNT_dvb_table_transport_first);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_table_nit_next", (void*)neutrinoNT_dvb_table_transport_next);

	mono_add_internal_call("dvbv5.NativeMethods::dvb_desc_next", (void*)neutrinoNT_dvb_descriptor_next);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_sdt_descriptor_first", (void*)neutrinoNT_dvb_sdt_descriptor_first);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_pmt_descriptor_first", (void*)neutrinoNT_dvb_pmt_descriptor_first);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_nit_descriptor_first", (void*)neutrinoNT_dvb_nit_descriptor_first);
	mono_add_internal_call("dvbv5.NativeMethods::dvb_eit_descriptor_first", (void*)neutrinoNT_dvb_eit_descriptor_first);

	mono_add_internal_call("dvbv5.NativeMethods::dvb_desc_get_type", (void*)neutrinoNT_dvb_desc_get_type);
}

//int main(int argc, char* argv[])
//{
//#ifdef DEBUG
//	mono_debug_init(MONO_DEBUG_FORMAT_MONO);
//#endif
//	mono_set_dirs("/usr/lib", "/etc/mono");
//	mono_config_parse("/etc/mono/config");
//	MonoDomain* domain = mono_jit_init("dvb_zapit");
//	mono_thread_attach(domain);
//	MonoAssembly* assembly = mono_domain_assembly_open(domain, "ffNeutrinoHD.exe");
//	//MonoImage* image = mono_assembly_get_image(assembly);
//	//MonoClass* my_class = mono_class_from_name(image, "ffNeutrinoHD", "Application");
//	//MonoObject* my_class_instance = mono_object_new(domain, my_class);
//	//MonoMethod* constructorMethod = mono_class_get_method_from_name(my_class, "StartUp", 0);
//
//	InitDVBWrapper();
//	//mono_runtime_object_init(my_class_instance);
//	//mono_runtime_invoke(constructorMethod, my_class_instance, NULL, NULL);
//	mono_jit_exec(domain, assembly, argc, argv);
//	mono_jit_cleanup(domain);
//
//}
