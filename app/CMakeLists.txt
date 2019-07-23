add_executable(${EXE_NAME})

target_sources(${EXE_NAME} PRIVATE "main.cpp")
target_link_libraries(${EXE_NAME} PUBLIC ${LIB_NAME})