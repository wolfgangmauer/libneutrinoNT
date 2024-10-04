#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/stat.h>

#include "decoder.h"

int neutrinoNT_VIDEO_PLAY(int fd)
{
	return ioctl(fd, VIDEO_PLAY);
}

int neutrinoNT_VIDEO_STOP(int fd, int blank)
{
	return ioctl(fd, VIDEO_STOP, blank);
}

int neutrinoNT_VIDEO_FREEZE(int fd)
{
	return ioctl(fd, VIDEO_FREEZE);
}

int neutrinoNT_VIDEO_CONTINUE(int fd)
{
	return ioctl(fd, VIDEO_CONTINUE);
}

int neutrinoNT_VIDEO_CLEAR_BUFFER(int fd)
{
	return ioctl(fd, VIDEO_CLEAR_BUFFER);
}

int neutrinoNT_VIDEO_SLOWMOTION(int fd, int repeat)
{
	return ioctl(fd, VIDEO_SLOWMOTION, repeat);
}

int neutrinoNT_VIDEO_FAST_FORWARD(int fd, int skip)
{
	return ioctl(fd, VIDEO_FAST_FORWARD, skip);
}

int neutrinoNT_VIDEO_SET_STREAMTYPE(int fd, int type)
{
	return ioctl(fd, VIDEO_SET_STREAMTYPE, type);
}

int neutrinoNT_VIDEO_GET_BLANK(int fd, struct video_status* status)
{
	return ioctl(fd, VIDEO_GET_STATUS, status);
}

int neutrinoNT_VIDEO_SET_BLANK(int fd, int blank)
{
	return ioctl(fd, VIDEO_SET_BLANK, blank);
}

int neutrinoNT_VIDEO_SELECT_SOURCE(int fd, int source)
{
	return ioctl(fd, VIDEO_SELECT_SOURCE, source);
}

int neutrinoNT_VIDEO_GET_PTS(int fd, int64_t* pts)
{
	return ioctl(fd, VIDEO_GET_PTS, pts);
}

int neutrinoNT_AUDIO_SET_MUTE(int fd, int enable)
{
	return ioctl(fd, AUDIO_SET_MUTE, enable);
}

int neutrinoNT_AUDIO_SET_MIXER(int fd, struct audio_mixer* mixer)
{
	return ioctl(fd, AUDIO_SET_MIXER, mixer);
}

int neutrinoNT_AUDIO_PLAY(int fd)
{
	return ioctl(fd, AUDIO_PLAY);
}

int neutrinoNT_AUDIO_STOP(int fd)
{
	return ioctl(fd, AUDIO_STOP);
}

int neutrinoNT_AUDIO_PAUSE(int fd)
{
	return ioctl(fd, AUDIO_PAUSE, 1);
}

int neutrinoNT_AUDIO_CONTINUE(int fd)
{
	return ioctl(fd, AUDIO_CONTINUE);
}

int neutrinoNT_AUDIO_SET_STREAMTYPE(int fd, int type)
{
	return ioctl(fd, AUDIO_SET_BYPASS_MODE, type);
}

int neutrinoNT_AUDIO_CLEAR_BUFFER(int fd)
{
	return ioctl(fd, AUDIO_CLEAR_BUFFER);
}

int neutrinoNT_AUDIO_SET_AV_SYNC(int fd, int mode)
{
	return ioctl(fd, AUDIO_SET_AV_SYNC, mode);
}

int neutrinoNT_AUDIO_CHANNEL_SELECT(int fd, int channel)
{
	return ioctl(fd, AUDIO_CHANNEL_SELECT, (audio_channel_select_t)channel);
}

int neutrinoNT_AUDIO_SELECT_SOURCE(int fd, int source)
{
	return ioctl(fd, AUDIO_SELECT_SOURCE, (audio_stream_source_t)source);
}
