


add_library(${LIB_NAME})

target_sources(${LIB_NAME} PRIVATE "lib.cpp")

target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${LIB_NAME} PRIVATE ${CONAN_LIBS})
