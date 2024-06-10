#include "lv_theme_custom.h"

static lv_style_t style_scr;
static lv_style_t style_btn;
static lv_style_t style_qrcode;

static void custom_theme_cb(lv_theme_t *th, lv_obj_t *obj);

void custom_theme_init(void) {

    /* Initialize the styles */
    lv_style_init(&style_scr);
    lv_style_set_bg_opa(&style_scr, LV_OPA_COVER);
    lv_style_set_bg_color(&style_scr, COLOR_BLACK);

#if LV_USE_BTN
    lv_style_init(&style_btn);
    lv_style_set_bg_color(&style_btn, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_text_color(&style_btn, lv_palette_darken(LV_PALETTE_GREY, 80));
#endif
#if LV_USE_QRCODE
    lv_style_init(&style_qrcode);
    lv_style_set_bg_color(&style_qrcode, lv_palette_main(LV_PALETTE_GREY));
#endif
    /*Initialize the new theme from the current theme*/
    lv_theme_t *current_theme = lv_disp_get_theme(NULL);
    static lv_theme_t custom_theme;
    custom_theme = *current_theme;

    /*Set the parent theme and the style apply callback for the new theme*/
    lv_theme_set_parent(&custom_theme, current_theme);
    lv_theme_set_apply_cb(&custom_theme, custom_theme_cb);

    /*Assign the new theme to the current display*/
    lv_disp_set_theme(NULL, &custom_theme);
}

static void custom_theme_cb(lv_theme_t *th, lv_obj_t *obj) {
    LV_UNUSED(th);

    if (lv_obj_get_parent(obj) == NULL) {
        lv_obj_add_style(obj, &style_scr, 0);
    }
#if LV_USE_BTN
    if (lv_obj_check_type(obj, &lv_btn_class)) {
        lv_obj_add_style(obj, &style_btn, 0);
    }
#endif
#if LV_USE_QRCODE
    if (lv_obj_check_type(obj, &lv_qrcode_class)) {
        lv_obj_add_style(obj, &style_qrcode, 0);
    }
#endif
}