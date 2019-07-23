#pragma once
#include "chess_board.hpp"
#include "gui.hpp"

int main(int argc, char** argv) {
	chess_board board;
	console_gui cg(board);
	cg.print_board();

	return 0;
}


