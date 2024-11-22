#ifndef TDISPLAYS3PRO_POWER_H
#define TDISPLAYS3PRO_POWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "esp_err.h"

/**
 * @brief
 */
esp_err_t power_init(void);

/**
 * @brief
 */
int power_get_vbat(void);

#ifdef __cplusplus
}
#endif

#endif /* TDISPLAYS3PRO_POWER_H */