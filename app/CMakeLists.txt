
set(EXE_NAME "cheese")

add_executable(${EXE_NAME})

target_sources(${EXE_NAME} PRIVATE "main.cpp" "chess_board.hpp" "chess_piece.hpp" "chess_field.hpp" "type.hpp")
