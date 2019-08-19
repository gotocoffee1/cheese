add_library(${LIB_NAME})

target_sources(${LIB_NAME} PRIVATE "lib.cpp" "renderer.cpp" "cheese_brain.cpp")

target_include_directories(${LIB_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${LIB_NAME} PRIVATE guinea)
target_compile_features(${LIB_NAME} PUBLIC cxx_std_17)
#target_link_libraries(${LIB_NAME} PRIVATE ${CONAN_LIBS})
