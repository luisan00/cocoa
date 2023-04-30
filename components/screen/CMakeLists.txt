file(GLOB_RECURSE SOURCES *.c)

idf_component_register(
    SRCS ${SOURCES}
    INCLUDE_DIRS "include"
    REQUIRES cmock driver esp_lcd esp_timer lvgl
)