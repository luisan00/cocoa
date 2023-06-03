#ifndef GUI_H
#define GUI_H
#define PI (3.14159f)
typedef struct {
    lv_obj_t *scr;
    int count_val;
} my_timer_context_t;

LV_IMG_DECLARE(esp_logo);

void gui_init(lv_obj_t *scr);
void gui_deinit(void);

#endif /* GUI_H */