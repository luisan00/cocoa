if(CONFIG_BOARD_TTGO_TDISPLAYS3)
    idf_component_register(
        SRCS "ttgo_tdisplays3/lcd.c"
        INCLUDE_DIRS "ttgo_tdisplays3/include"
        REQUIRES cmock driver freertos esp_lcd esp_lvgl_port lvgl esp_timer soc
    )
endif()

if(CONFIG_BOARD_TTGO_TDISPLAYS3_PROCAMERA)
    idf_component_register(
        SRCS "ttgo_tdisplays3_procamera/lcd.c"
        INCLUDE_DIRS "ttgo_tdisplays3_procamera/include"
        REQUIRES cmock driver freertos esp_lcd esp_lvgl_port lvgl esp_timer soc
    )
endif()

if(CONFIG_BOARD_ESP32C3_DEVKIT)
    idf_component_register(
        SRCS "esp32c3_devkit/lcd.c"
        INCLUDE_DIRS "esp32c3_devkit/include"
        REQUIRES cmock
    )
endif()
