#pragma once
#include "chess_piece.hpp"
#include "chess_field.hpp"

class chess_board
{
private:
	int board_size = 8;

public:
	chess_field board_field[8][8];

	chess_board()
	{
		for (auto& row : board_field)
		{
			for (auto& column : row)
			{
				pawn p(color::WHITE);
				column.set_piece(p);
			}
		}
	}
};