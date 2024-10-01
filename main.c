#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#include "linux/fb.h"
#include <linux/dvb/dmx.h>
#include <linux/dvb/version.h>
#include <linux/dvb/frontend.h>

//#include <nexus_config.h>
//#include <nexus_core_utils.h>
//#include <nxclient.h>
//#include <default_nexus.h>

//#include <mono/jit/jit.h>
//#include <mono/metadata/assembly.h>
//#include <mono/metadata/mono-debug.h>
//#include <mono/metadata/mono-config.h>
//#include <mono/metadata/debug-helpers.h>
//#include <mono/metadata/appdomain.h>
//#include <mono/metadata/object.h>
//#include <mono/metadata/threads.h>
//#include <mono/metadata/environment.h>
//#include <mono/metadata/mono-gc.h>
//#include <mono/utils/mono-publib.h>
//#include <mono/metadata/loader.h>


#include "demuxer.h"
#include "decoder.h"
#include "frontend.h"

//void InitDVBWrapper()
//{
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::PesFilter", (void*)_PesFilter);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::SectionFilter", (void*)_SectionFilter);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::Read", (void*)_Read);
//
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::DMX_REMOVE_PID", (void*)_DMX_REMOVE_PID);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::DMX_ADD_PID", (void*)_DMX_ADD_PID);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::DMX_SET_PES_FILTER", (void*)_DMX_SET_PES_FILTER);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::DMX_SET_FILTER", (void*)_DMX_SET_FILTER);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::DMX_STOP", (void*)_DMX_STOP);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::DMX_START", (void*)_DMX_START);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::DMX_SET_SOURCE", (void*)_DMX_SET_SOURCE);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::DMX_SET_BUFFER_SIZE", (void*)_DMX_SET_BUFFER_SIZE);
//
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::VIDEO_SELECT_SOURCE", (void*)_VIDEO_SELECT_SOURCE);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::VIDEO_SET_STREAMTYPE", (void*)_VIDEO_SET_STREAMTYPE);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::VIDEO_CLEAR_BUFFER", (void*)_VIDEO_CLEAR_BUFFER);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::VIDEO_CONTINUE", (void*)_VIDEO_CONTINUE);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::VIDEO_FREEZE", (void*)_VIDEO_FREEZE);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::VIDEO_SLOWMOTION", (void*)_VIDEO_SLOWMOTION);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::VIDEO_FAST_FORWARD", (void*)_VIDEO_FAST_FORWARD);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::VIDEO_STOP", (void*)_VIDEO_STOP);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::VIDEO_PLAY", (void*)_VIDEO_PLAY);
//
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::AUDIO_SELECT_SOURCE", (void*)_AUDIO_SELECT_SOURCE);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::AUDIO_CHANNEL_SELECT", (void*)_AUDIO_CHANNEL_SELECT);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::AUDIO_SET_AV_SYNC", (void*)_AUDIO_SET_AV_SYNC);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::AUDIO_SET_STREAMTYPE", (void*)_AUDIO_SET_STREAMTYPE);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::AUDIO_CLEAR_BUFFER", (void*)_AUDIO_CLEAR_BUFFER);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::AUDIO_CONTINUE", (void*)_AUDIO_CONTINUE);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::AUDIO_PAUSE", (void*)_AUDIO_PAUSE);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::AUDIO_STOP", (void*)_AUDIO_STOP);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::AUDIO_PLAY", (void*)_AUDIO_PLAY);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::AUDIO_SET_MIXER", (void*)_AUDIO_SET_MIXER);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::AUDIO_SET_MUTE", (void*)_AUDIO_SET_MUTE);
//
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::FE_GET_INFO", (void*)_FE_GET_INFO);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::FE_READ_STATUS", (void*)_FE_READ_STATUS);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::FE_READ_SNR", (void*)_FE_READ_SNR);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::FE_READ_BER", (void*)_FE_READ_BER);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::FE_READ_UNCORRECTED_BLOCKS", (void*)_FE_READ_UNCORRECTED_BLOCKS);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::FE_GET_EVENT", (void*)_FE_GET_EVENT);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::FE_GET_FRONTEND", (void*)_FE_GET_FRONTEND);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::FE_SET_FRONTEND", (void*)_FE_SET_FRONTEND);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::FE_READ_SIGNAL_STRENGTH", (void*)_FE_READ_SIGNAL_STRENGTH);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::FE_SET_TONE", (void*)_FE_SET_TONE);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::FE_CLEAR_PROPERTIES", (void*)_FE_CLEAR_PROPERTIES);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::FE_SET_PROPERTY_DATA", (void*)_FE_SET_PROPERTY_DATA);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::FE_SET_PROPERTY", (void*)_FE_SET_PROPERTY);
//
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::CA_GET_SLOT_INFO", (void*)_CA_GET_SLOT_INFO);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::CA_RESET", (void*)_CA_RESET);
//	mono_add_internal_call("ffNeutrinoHD.NativeMethods::FBIOPUT_VSCREENINFO", (void*)_FBIOPUT_VSCREENINFO);
//}

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
