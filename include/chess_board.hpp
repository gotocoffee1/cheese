#pragma once
#include "chess_piece.hpp"
#include "chess_field.hpp"

class chess_board
{
public:
	chess_field board_field[8][8];

	chess_board()
	{
		for (int i = 0; i < 8; i++)
		{
			board_field[1][i].set_piece(new pawn(color::BLACK));
			board_field[6][i].set_piece(new pawn(color::WHITE));
			for (int j = 0; j < 8; j++)
			{

				if ((i > 1) && (i < 6))
				{
					board_field[i][j].set_piece(new empty(color::WHITE));
				}
			}
		}

		board_field[0][0].set_piece(new rook(color::BLACK));
		board_field[0][1].set_piece(new knight(color::BLACK));
		board_field[0][2].set_piece(new bishop(color::BLACK));
		board_field[0][3].set_piece(new queen(color::BLACK));
		board_field[0][4].set_piece(new king(color::BLACK));
		board_field[0][5].set_piece(new bishop(color::BLACK));
		board_field[0][6].set_piece(new knight(color::BLACK));
		board_field[0][7].set_piece(new rook(color::BLACK));

		board_field[7][0].set_piece(new rook(color::WHITE));
		board_field[7][1].set_piece(new knight(color::WHITE));
		board_field[7][2].set_piece(new bishop(color::WHITE));
		board_field[7][3].set_piece(new queen(color::WHITE));
		board_field[7][4].set_piece(new king(color::WHITE));
		board_field[7][5].set_piece(new bishop(color::WHITE));
		board_field[7][6].set_piece(new knight(color::WHITE));
		board_field[7][7].set_piece(new rook(color::BLACK));
	}
};