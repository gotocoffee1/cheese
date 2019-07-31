# CMakeList.txt: CMake-Projektdatei der obersten Ebene. Führen Sie hier die globale Konfiguration aus,
# und schließen Sie Unterprojekte ein.
#
cmake_minimum_required (VERSION 3.8)

project ("cheese" VERSION 1.0 LANGUAGES CXX)

set(LIB_NAME "cheese")
set(EXE_NAME "cheesy")

# Download automatically, you can also just copy the conan.cmake file
#if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
#message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
#    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.14/conan.cmake"
#                "${CMAKE_BINARY_DIR}/conan.cmake")
#endif()
#
#include(${CMAKE_BINARY_DIR}/conan.cmake)
#
#conan_cmake_run(CONANFILE conanfile.txt
#                BASIC_SETUP)
#
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup()

# Schließen Sie Unterprojekte ein.
add_subdirectory ("ext")
add_subdirectory ("src")
add_subdirectory ("app")
