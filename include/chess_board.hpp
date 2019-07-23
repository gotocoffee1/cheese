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
		/*
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (i < 2 || i > 6)
				{
					board_field[0][0].set_piece(rook(color::BLACK));
					board_field[0][1].set_piece(knight(color::BLACK));
					board_field[0][2].set_piece(bishop(color::BLACK));
					board_field[0][3].set_piece(queen(color::BLACK));
					board_field[0][4].set_piece(king(color::BLACK));
					board_field[0][5].set_piece(bishop(color::BLACK));
					board_field[0][6].set_piece(knight(color::BLACK));
					board_field[0][7].set_piece(rook(color::BLACK));

					board_field[7][0].set_piece(rook(color::BLACK));
					board_field[7][1].set_piece(knight(color::BLACK));
					board_field[7][2].set_piece(bishop(color::BLACK));
					board_field[7][3].set_piece(queen(color::BLACK));
					board_field[7][4].set_piece(king(color::BLACK));
					board_field[7][5].set_piece(bishop(color::BLACK));
					board_field[7][6].set_piece(knight(color::BLACK));
					board_field[7][7].set_piece(rook(color::BLACK));

				}
				else
				{
					board_field[i][j].set_piece(empty(color::BLACK));
				}
			}
		}
		*/
	}
};