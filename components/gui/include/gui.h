#ifndef GUI_H
#define GUI_H

#define SCREEN_H_RES 320
#define SCREEN_V_RES 170

void gui_init(lv_obj_t *screen);

void gui_task(void *args);

void show_mnemonic(lv_obj_t *scr, const char **mnemonic, size_t mnemonic_size);

#endif /* GUI_H */