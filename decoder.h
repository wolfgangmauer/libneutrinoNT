#pragma once
#include <stdint.h>

#include <linux/dvb/audio.h>
#include <linux/dvb/video.h>
#include <linux/dvb/frontend.h>

int neutrinoNT_VIDEO_PLAY(int fd);
int neutrinoNT_VIDEO_STOP(int fd, int blank);
int neutrinoNT_VIDEO_FREEZE(int fd);
int neutrinoNT_VIDEO_CONTINUE(int fd);
int neutrinoNT_VIDEO_CLEAR_BUFFER(int fd);
int neutrinoNT_VIDEO_SLOWMOTION(int fd, int repeat);
int neutrinoNT_VIDEO_FAST_FORWARD(int fd, int skip);
int neutrinoNT_VIDEO_SET_STREAMTYPE(int fd, int type);
int neutrinoNT_VIDEO_GET_BLANK(int fd, struct video_status* status);
int neutrinoNT_VIDEO_SET_BLANK(int fd, int blank);
int neutrinoNT_VIDEO_SELECT_SOURCE(int fd, int source);
int neutrinoNT_VIDEO_GET_PTS(int fd, int64_t* pts);
int neutrinoNT_AUDIO_SET_MUTE(int fd, int enable);
int neutrinoNT_AUDIO_SET_MIXER(int fd, struct audio_mixer* mixer);
int neutrinoNT_AUDIO_PLAY(int fd);
int neutrinoNT_AUDIO_STOP(int fd);
int neutrinoNT_AUDIO_PAUSE(int fd);
int neutrinoNT_AUDIO_CONTINUE(int fd);
int neutrinoNT_AUDIO_SET_STREAMTYPE(int fd, int type);
int neutrinoNT_AUDIO_CLEAR_BUFFER(int fd);
int neutrinoNT_AUDIO_SET_AV_SYNC(int fd, int mode);
int neutrinoNT_AUDIO_CHANNEL_SELECT(int fd, int channel);
int neutrinoNT_AUDIO_SELECT_SOURCE(int fd, int source);
