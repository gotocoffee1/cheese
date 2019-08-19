add_executable(all_tests main.cpp cheese_brain.cpp)
target_include_directories(all_tests PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(all_tests PRIVATE ${LIB_NAME})
add_test(NAME all_tests COMMAND all_tests)
