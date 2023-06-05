idf_component_register(
    SRCS "screen.c" "backlight.c"
    INCLUDE_DIRS "include"
    REQUIRES cmock logger esp_timer esp_lcd lvgl gui
)