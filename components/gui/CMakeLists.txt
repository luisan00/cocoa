set(
    SOURCES 
        "gui.c" 
)
set(IMAGE_SRCS "images/bitcoin.c")

idf_component_register(
    SRCS ${SOURCES} ${IMAGE_SRCS}
    INCLUDE_DIRS "include"
    REQUIRES cmock screen lvgl
)