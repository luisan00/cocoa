idf_component_register(
    SRCS "hmi.c"
    INCLUDE_DIRS "include"
    REQUIRES cmock driver helpers logger)