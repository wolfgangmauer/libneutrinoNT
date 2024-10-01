#pragma once

#include <linux/dvb/video.h>
#include <linux/dvb/frontend.h>

#define TIMER_INIT()					\
	static unsigned int tmin = 2000, tmax = 0;	\
	struct timeval tv, tv2;				\
	unsigned int timer_msec = 0;

#define TIMER_START()					\
	gettimeofday(&tv, NULL);

#define TIMER_STOP(label)				\
	gettimeofday(&tv2, NULL);			\
	timer_msec = ((tv2.tv_sec-tv.tv_sec) * 1000) +	\
		     ((tv2.tv_usec-tv.tv_usec) / 1000); \
	if(tmin > timer_msec) tmin = timer_msec;	\
	if(tmax < timer_msec) tmax = timer_msec;	\
	 printf("%s: %u msec (min %u max %u)\n",	\
		 label, timer_msec, tmin, tmax);

#define FEC_S2_QPSK_1_2 (fe_code_rate_t)(FEC_AUTO+1)			//10
#define FEC_S2_QPSK_2_3 (fe_code_rate_t)(FEC_S2_QPSK_1_2+1)		//11
#define FEC_S2_QPSK_3_4 (fe_code_rate_t)(FEC_S2_QPSK_2_3+1)		//12
#define FEC_S2_QPSK_5_6 (fe_code_rate_t)(FEC_S2_QPSK_3_4+1)		//13
#define FEC_S2_QPSK_7_8 (fe_code_rate_t)(FEC_S2_QPSK_5_6+1)		//14
#define FEC_S2_QPSK_8_9 (fe_code_rate_t)(FEC_S2_QPSK_7_8+1)		//15
#define FEC_S2_QPSK_3_5 (fe_code_rate_t)(FEC_S2_QPSK_8_9+1)		//16
#define FEC_S2_QPSK_4_5 (fe_code_rate_t)(FEC_S2_QPSK_3_5+1)		//17
#define FEC_S2_QPSK_9_10 (fe_code_rate_t)(FEC_S2_QPSK_4_5+1)		//18

#define FEC_S2_8PSK_1_2 (fe_code_rate_t)(FEC_S2_QPSK_9_10+1)		//19
#define FEC_S2_8PSK_2_3 (fe_code_rate_t)(FEC_S2_8PSK_1_2+1)		//20
#define FEC_S2_8PSK_3_4 (fe_code_rate_t)(FEC_S2_8PSK_2_3+1)		//21
#define FEC_S2_8PSK_5_6 (fe_code_rate_t)(FEC_S2_8PSK_3_4+1)		//22
#define FEC_S2_8PSK_7_8 (fe_code_rate_t)(FEC_S2_8PSK_5_6+1)		//23
#define FEC_S2_8PSK_8_9 (fe_code_rate_t)(FEC_S2_8PSK_7_8+1)		//24
#define FEC_S2_8PSK_3_5 (fe_code_rate_t)(FEC_S2_8PSK_8_9+1)		//25
#define FEC_S2_8PSK_4_5 (fe_code_rate_t)(FEC_S2_8PSK_3_5+1)		//26
#define FEC_S2_8PSK_9_10 (fe_code_rate_t)(FEC_S2_8PSK_4_5+1)		//27
#define FEC_S2_AUTO      (fe_code_rate_t)(FEC_S2_8PSK_9_10+1)		//28

static inline fe_modulation_t dvbs_get_modulation(fe_code_rate_t fec)
{
	if( (fec < FEC_S2_QPSK_1_2) || (fec < FEC_S2_8PSK_1_2) )
		return QPSK;
	else
		return PSK_8;
}

static inline fe_delivery_system_t dvbs_get_delsys(fe_code_rate_t fec)
{
	if(fec < FEC_S2_QPSK_1_2)
		return SYS_DVBS;
	else
		return SYS_DVBS2;
}

static inline fe_rolloff_t dvbs_get_rolloff(fe_delivery_system_t delsys)
{
	if(delsys == SYS_DVBS2)
		return ROLLOFF_25;
	else
		return ROLLOFF_35;
}

int neutrinoNT_FE_GET_INFO(int fd, struct dvb_frontend_info* info);
int neutrinoNT_FE_READ_STATUS(int fd, fe_status_t* status);
int neutrinoNT_FE_GET_FRONTEND(int fd, struct dvb_frontend_parameters* feparams);
int neutrinoNT_FE_SET_FRONTEND(int fd, struct dvb_frontend_parameters* feparams);
int neutrinoNT_FE_READ_SIGNAL_STRENGTH(int fd, uint16_t* strength);
int neutrinoNT_FE_READ_BER(int fd, uint32_t* ber);
int neutrinoNT_FE_READ_SNR(int fd, uint16_t* snr);
int neutrinoNT_FE_READ_UNCORRECTED_BLOCKS(int fd, uint32_t* uncorrected_blocks);
int neutrinoNT_FE_SET_TONE(int fd, fe_sec_tone_mode_t toneMode);
int neutrinoNT_FE_SET_VOLTAGE(int fd, fe_sec_voltage_t voltage);
int neutrinoNT_FE_DISEQC_SEND_MASTER_CMD(int fd, struct dvb_diseqc_master_cmd cmd);
int neutrinoNT_FE_RESET(int fd, int adapter, int number);
int neutrinoNT_FE_GET_EVENT(int fd, struct dvb_frontend_event* event);
void neutrinoNT_FE_CLEAR_PROPERTIES();
void neutrinoNT_FE_SET_PROPERTY_DATA(uint32_t cmd, uint32_t value);
int neutrinoNT_FE_SET_PROPERTY(int fd);
