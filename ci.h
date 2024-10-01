#pragma once
#include <stdint.h>

#include <linux/dvb/dmx.h>
#include <linux/dvb/version.h>
#include <linux/dvb/frontend.h>
#include <linux/dvb/ca.h>

int neutrinoNT_CA_GET_SLOT_INFO(int fd, struct ca_slot_info* info);
int neutrinoNT_CA_RESET(int fd);
