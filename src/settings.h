#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <string.h>
#include <settings/settings.h>

extern struct k_work storage_work;

int ps_settings_init(void);
void save_event0(void);
void save_event1(void);

#endif