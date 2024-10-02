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

typedef enum {
	DMX_VIDEO_CHANNEL  = 1,
	DMX_AUDIO_CHANNEL,
	DMX_PES_CHANNEL,
	DMX_PSI_CHANNEL,
	DMX_PIP_CHANNEL,
	DMX_TP_CHANNEL,
	DMX_PCR_ONLY_CHANNEL
} DMX_CHANNEL_TYPE;

bool neutrinoNT_PesFilter(int fd, DMX_CHANNEL_TYPE type, uint16_t pid, const dmx_input_t input);
bool neutrinoNT_SectionFilter(int fd, uint16_t pid, MonoArray* filter, MonoArray* mask, int len, int timeout, MonoArray* mode);
int neutrinoNT_Read(int fd, MonoArray** array, DMX_CHANNEL_TYPE type, int len, int timeout);

int neutrinoNT_DMX_SET_SOURCE(int fd, dmx_source_t number);
int neutrinoNT_DMX_SET_BUFFER_SIZE(int fd, int bufferSize);
int neutrinoNT_DMX_START(int fd);
int neutrinoNT_DMX_STOP(int fd);
int neutrinoNT_DMX_ADD_PID(int fd, uint16_t pid);
int neutrinoNT_DMX_REMOVE_PID(int fd, uint16_t pid);
int neutrinoNT_DMX_SET_PES_FILTER(int fd, struct dmx_pes_filter_params* params);
int neutrinoNT_DMX_SET_FILTER(int fd, struct dmx_sct_filter_params* params);
