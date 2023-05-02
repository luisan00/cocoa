#include "screen.h"
#include "lvgl_demo_ui.h"

// Private structures
static lv_style_t style;
static lv_style_t bgStyle;
static lv_style_t titleStyle;

static lv_obj_t *arc[3];
static lv_obj_t *img_logo;

static lv_obj_t *dis;
static lv_obj_t *meter;

lv_obj_t *tv1;
lv_obj_t *tv2;
lv_obj_t *tv3;

static lv_color_t arc_color[] =
    {
        LV_COLOR_MAKE(0xFF, 0x00, 0x28),
        LV_COLOR_MAKE(0x14, 0xFF, 0x00),
        LV_COLOR_MAKE(0xFF, 0xFF, 0xFF),
};

// private function declaration
void lvgl_demo_ui(lv_obj_t *scr);
static void bg_timer_cb(lv_timer_t *timer);
static void anim_timer_cb(lv_timer_t *timer);

/**
 * @brief   lvgl screen content termination timer callback
 * @param   timer pointer to timer settings and user parameters
 */
static void bg_timer_cb(lv_timer_t *timer)
{
    static uint8_t flipPage = 1;
    lv_obj_set_tile_id(dis, 0, flipPage, LV_ANIM_ON);
    flipPage ^= 1;
}

void set_value(void *indic, int32_t v)
{
    lv_meter_set_indicator_end_value(meter, indic, v);
}

/**
 * @brief 	lvgl screen animation timer callback
 * @param 	timer pointer to timer settings and user parameters
 */
static void anim_timer_cb(lv_timer_t *timer)
{
    my_timer_context_t *timer_ctx = (my_timer_context_t *)timer->user_data;
    int count = timer_ctx->count_val;
    lv_obj_t *scr = timer_ctx->scr;

    // Play arc animation
    if (count < 90)
    {
        lv_coord_t arc_start = count > 0 ? (1 - cosf(count / 180.0f * PI)) * 270 : 0;
        lv_coord_t arc_len = (sinf(count / 180.0f * PI) + 1) * 135;

        for (size_t i = 0; i < sizeof(arc) / sizeof(arc[0]); i++)
        {
            lv_arc_set_bg_angles(arc[i], arc_start, arc_len);
            lv_arc_set_rotation(arc[i], (count + 120 * (i + 1)) % 360);
        }
    }

    // Delete arcs when animation finished
    if (count == 90)
    {
        for (size_t i = 0; i < sizeof(arc) / sizeof(arc[0]); i++)
        {
            lv_obj_del(arc[i]);
        }
    }

    // Delete timer when all animation finished
    if ((count += 5) == 220)
    {
        lv_timer_del(timer);
        
        // use full color with the title text
        lv_timer_create(bg_timer_cb, 10000, NULL);
    }
    else
    {
        timer_ctx->count_val = count;
    }
}

void lvgl_demo_ui(lv_obj_t *scr)
{

    // Initialize 3 tiles that act as pages
    dis = lv_tileview_create(scr);
    lv_obj_align(dis, LV_ALIGN_TOP_RIGHT, 0, 0);
    tv1 = lv_tileview_add_tile(dis, 0, 0, LV_DIR_HOR);
    tv2 = lv_tileview_add_tile(dis, 0, 1, LV_DIR_HOR);
    tv3 = lv_tileview_add_tile(dis, 0, 2, LV_DIR_HOR);

    // Create image logo and put it in the center
    img_logo = lv_img_create(tv1);
    lv_img_set_src(img_logo, &esp_logo);
    lv_obj_center(img_logo);

    // create style to manipulate objects characteristics implicitly
    lv_style_init(&style);
    lv_style_init(&bgStyle);
    lv_style_init(&titleStyle);

    // lv_color_hex(rgb) 0x(red) 0x(green) 0x(blue)
    lv_color_t textColor16 = lv_color_hex(COLOR_RED);
    lv_style_set_text_color(&style, textColor16);
    lv_style_set_text_font(&style, &lv_font_montserrat_28);

    // Change background color
    textColor16 = lv_color_hex(COLOR_BLACK);
    lv_obj_add_style(dis, &bgStyle, 0);
    lv_style_set_bg_color(&bgStyle, textColor16);

    // Change title text style
    textColor16 = lv_color_hex(COLOR_BLUE);
    lv_style_set_text_color(&titleStyle, textColor16);
    lv_style_set_text_font(&titleStyle, &lv_font_montserrat_26);

    // Create arcs
    for (size_t i = 0; i < sizeof(arc) / sizeof(arc[0]); i++)
    {
        arc[i] = lv_arc_create(tv1);

        // Set arc caption
        lv_obj_set_size(arc[i], 220 - 30 * i, 220 - 30 * i);
        lv_arc_set_bg_angles(arc[i], 120 * i, 10 + 120 * i);
        lv_arc_set_value(arc[i], 0);

        // Set arc style
        lv_obj_remove_style(arc[i], NULL, LV_PART_KNOB);
        lv_obj_set_style_arc_width(arc[i], 10, 0);
        lv_obj_set_style_arc_color(arc[i], arc_color[i], 0);

        // Make arc center
        lv_obj_center(arc[i]);
    }

    // Create timer for animation
    static my_timer_context_t my_tim_ctx =
        {
            .count_val = -90,
        };
    my_tim_ctx.scr = tv1;

    /* page 2 */
    meter = lv_meter_create(tv2);
    lv_obj_center(meter);
    lv_obj_set_size(meter, 170, 170);

    /*Remove the circle from the middle*/
    lv_obj_remove_style(meter, NULL, LV_PART_INDICATOR);

    /*Add a scale first*/
    lv_meter_scale_t *scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 11, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_major_ticks(meter, scale, 1, 2, 15, lv_color_hex(COLOR_WHITE), 10);
    lv_meter_set_scale_range(meter, scale, 0, 100, 270, 90);

    // Add a three arc indicator
    // extern indicator
    lv_meter_indicator_t *indic1 = lv_meter_add_arc(meter, scale, 10, lv_color_hex(COLOR_BLUE), 0);
    // mid indicator
    lv_meter_indicator_t *indic2 = lv_meter_add_arc(meter, scale, 10, lv_color_hex(COLOR_GREEN), -10);
    // next to center indicator
    lv_meter_indicator_t *indic3 = lv_meter_add_arc(meter, scale, 10, lv_color_hex(COLOR_RED), -20);

    /*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_set_repeat_delay(&a, 100);
    lv_anim_set_playback_delay(&a, 100);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);

    lv_anim_set_time(&a, 2000);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_set_var(&a, indic1);
    lv_anim_start(&a);

    lv_anim_set_time(&a, 1000);
    lv_anim_set_playback_time(&a, 1000);
    lv_anim_set_var(&a, indic2);
    lv_anim_start(&a);

    lv_anim_set_time(&a, 1000);
    lv_anim_set_playback_time(&a, 2000);
    lv_anim_set_var(&a, indic3);
    lv_anim_start(&a);
    /* page 3 */

    lv_timer_create(anim_timer_cb, 20, &my_tim_ctx);
}
