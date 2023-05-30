#ifndef POWER_H
#define POWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// return mV
uint32_t get_batt_voltage(void);

#ifdef __cplusplus
}
#endif
#endif /*POWER_H */