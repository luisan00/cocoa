idf_component_register(
    SRCS "storage.c"
    INCLUDE_DIRS "include"
    REQUIRES cmock nvs_flash logger)