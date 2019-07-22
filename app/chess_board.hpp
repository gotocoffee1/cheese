#pragma once
#include "chess_piece.hpp"
#include "chess_field.hpp"

class chess_board {
private:
	int board_size = 8;

public:
	chess_field board_field[8][8];

	chess_board() {
		for (auto& row : board_field) {
			for (auto& column : row) {
				//column.piece;
			}
		}
	}

	bool move(int stx, int sty, int destx, int desty) {

	}

	bool move_bishop(int stx, int sty, int destx, int desty) {
		if (abs(stx - destx) == abs(stx - destx)) {
			return true;
		}
		return false;
	}
};