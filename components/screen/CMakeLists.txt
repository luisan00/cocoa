idf_component_register(
    SRCS 
        "display.c"
    INCLUDE_DIRS 
        "include"
    REQUIRES 
        cmock driver freertos esp_lcd esp_lvgl_port lvgl esp_timer soc
)
