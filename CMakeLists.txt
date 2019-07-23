# CMakeList.txt: CMake-Projektdatei der obersten Ebene. Führen Sie hier die globale Konfiguration aus,
# und schließen Sie Unterprojekte ein.
#
cmake_minimum_required (VERSION 3.8)

project ("cheese" VERSION 1.0 LANGUAGES CXX)

set(LIB_NAME "libcheese")
set(EXE_NAME "cheese")

# Schließen Sie Unterprojekte ein.
add_subdirectory ("app")
add_subdirectory ("src")
