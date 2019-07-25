#pragma once
#include "chess_piece.hpp"
#include "chess_field.hpp"

class chess_board
{
public:
	//board_field[y][x]
	chess_field board_field[8][8];

	chess_board()
	{
		//Chess starting positions
		for (int i = 0; i < 8; i++)
		{
			board_field[1][i].set_piece(new pawn(color::BLACK));
			board_field[6][i].set_piece(new pawn(color::WHITE));
			for (int j = 0; j < 8; j++)
			{

				if ((i > 1) && (i < 6))
				{
					board_field[i][j].set_piece(new empty(color::NONE));
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
		board_field[7][7].set_piece(new rook(color::WHITE));
	}

	void move(int stx, int sty, int destx, int desty)
	{
		cout << "is_move_valid " << (*board_field[sty][stx].get_piece()).is_move_valid(stx, sty, destx, desty) << "\n";
		string short_name = (*board_field[sty][stx].get_piece()).get_short_name();
		cout << "piece " << short_name << "\n";
		color col = (*board_field[sty][stx].get_piece()).c;
		if ((*board_field[sty][stx].get_piece()).is_move_valid(stx, sty, destx, desty))
		{
			chess_piece* old_piece;
			if (short_name == "")
			{
				old_piece = new empty(col);
			}
			else
			{
				if (short_name == "P")
				{
					old_piece = new pawn(col);
				}
				else
				{
					if (short_name == "N")
					{
						old_piece = new knight(col);
					}
					else
					{
						if (short_name == "B")
						{
							old_piece = new bishop(col);
						}
						else
						{
							if (short_name == "R")
							{
								old_piece = new rook(col);
							}
							else
							{
								if (short_name == "Q")
								{
									old_piece = new queen(col);
								}
								else
								{
									if (short_name == "K")
									{
										old_piece = new king(col);
									}
								}
							}
						}
					}
				}
			}
			board_field[desty][destx].set_piece(old_piece); //TODO noch die eigenschaften der figur gettn
			board_field[sty][stx].set_piece(new empty(color::NONE));
			cout << "dest " << (*board_field[desty][destx].get_piece()).get_short_name() << "\n";
			cout << "st " << (*board_field[sty][stx].get_piece()).get_short_name() << "\n";
		}
	}
};