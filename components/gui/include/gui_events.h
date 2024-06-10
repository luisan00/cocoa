#ifndef GUI_EVENTS_H
#define GUI_EVENTS_H

#include "esp_event.h"


#ifdef __cplusplus
extern "C" {
#endif



typedef enum {
    SHOW_SPLASH_SCR,
    QUIT_SPLASH_SCR,
    SHOW_MNEMONIC_SCR,
    QUIT_MNEMONIC_SCR,
} gui_events_t;

#ifdef __cplusplus
}
#endif

#endif /* GUI_EVENTS_H */