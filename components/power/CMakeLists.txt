idf_component_register(
    SRCS "power.c"
    INCLUDE_DIRS "include"
    REQUIRES cmock helpers logger soc esp_adc)