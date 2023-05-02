#ifndef STORAGE_H
#define STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"

esp_err_t storage_init(void);

#ifdef __cplusplus
}
#endif
#endif // STORAGE_H