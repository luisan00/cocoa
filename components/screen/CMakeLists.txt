file(GLOB_RECURSE SOURCES *.c)
file(GLOB_RECURSE IMAGE_SOURCES images/*.c)

idf_component_register(
    SRCS ${SOURCES} ${IMAGE_SOURCES}
    INCLUDE_DIRS "include"
    REQUIRES cmock  esp_lcd lvgl logger
)