idf_component_register(
    SRCS "test_storage.c"
    INCLUDE_DIRS "include"
    REQUIRES cmock storage helpers logger)