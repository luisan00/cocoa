set(
    SOURCES 
        "gui.c" 
)
set(IMAGE_SRCS "lv_theme_custom.c" "images/bitcoin.c")

idf_component_register(
    SRCS ${SOURCES} ${IMAGE_SRCS}
    INCLUDE_DIRS "include"
    REQUIRES cmock helpers screen lvgl
)