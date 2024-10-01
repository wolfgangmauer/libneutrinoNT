#pragma once
#include <stdint.h>

#include <linux/dvb/dmx.h>
#include <linux/dvb/version.h>
#include <linux/dvb/frontend.h>

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
bool neutrinoNT_SectionFilter(int fd, uint16_t pid, uint8_t* filter, uint8_t* mask, int len, int timeout, uint8_t* mode);
int neutrinoNT_Read(int fd, uint8_t* array, DMX_CHANNEL_TYPE type, int len, int timeout);

int neutrinoNT_DMX_SET_SOURCE(int fd, dmx_source_t number);
int neutrinoNT_DMX_SET_BUFFER_SIZE(int fd, int bufferSize);
int neutrinoNT_DMX_START(int fd);
int neutrinoNT_DMX_STOP(int fd);
int neutrinoNT_DMX_ADD_PID(int fd, uint16_t pid);
int neutrinoNT_DMX_REMOVE_PID(int fd, uint16_t pid);
int neutrinoNT_DMX_SET_PES_FILTER(int fd, struct dmx_pes_filter_params* params);
int neutrinoNT_DMX_SET_FILTER(int fd, struct dmx_sct_filter_params* params);
