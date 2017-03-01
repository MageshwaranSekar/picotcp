#ifndef PICO_DEV_SLIP
#define PICO_DEV_SLIP
#include "pico_config.h"
#include "pico_device.h"

struct pico_device *pico_slip_create(const char *name);

#endif