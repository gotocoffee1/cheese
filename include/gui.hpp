#pragma once
#include <iostream>

#include "chess_board.hpp"
#include "type.hpp"

class gui
{
public:
	chess_board& cb;
	gui(chess_board& cb) : cb(cb)
	{
	}

	virtual void print_board() = 0;
};

class console_gui : public gui
{
public:
	console_gui(chess_board& cb) : gui(cb) {}

	void print_board()
	{
		string number_helper;
		string border_helper;
		string white_field = "||||||";
		string empty_white_field = "||  ||";
		string black_field = "      ";
		string empty_black_field = "      ";
		string white_black_line;
		string white_black_line_empty;
		string black_white_line;
		string black_white_line_empty;
		string rim = "| \n";
		string whole_white_black_line;
		string whole_black_white_line;
		string board = "";

		for (int h = 0; h < 8; h++)
		{
			number_helper = "   ";
			border_helper = "   ";
			white_black_line = "  |";
			white_black_line_empty = " |";
			black_white_line = "  |";
			black_white_line_empty = " |";
			for (int i = 0; i < 8; i++)
			{
				string letter = "";
				switch (i)
				{
				case 0:
					letter = "A";
					break;
				case 1:
					letter = "B";
					break;
				case 2:
					letter = "C";
					break;
				case 3:
					letter = "D";
					break;
				case 4:
					letter = "E";
					break;
				case 5:
					letter = "F";
					break;
				case 6:
					letter = "G";
					break;
				case 7:
					letter = "H";
					break;
				}
				//number_helper += "  " + to_string(i + 1) + "   
				number_helper += "  " + letter + "   ";
				border_helper += "------";
				string short_name = (*cb.board_field[h][i].get_piece()).get_short_name();
				color color = (*cb.board_field[h][i].get_piece()).c;
				string string_color = " ";
				if (color == color::none)
				{
					string_color = " ";
					empty_white_field = "||||||";
					empty_black_field = "      ";
				} else {
					if (color == color::white)
					{
						string_color = "w";
					}
					else
					{
						string_color = "b";
					}
					empty_white_field = "||" + short_name + string_color + "||";
					empty_black_field = "  " + short_name + string_color + "  ";
				}
				

				if (i % 2 == 0)
				{

					white_black_line += white_field;
					white_black_line_empty += empty_white_field;
					black_white_line += black_field;
					black_white_line_empty += empty_black_field;
				}
				else
				{
					white_black_line += black_field;
					white_black_line_empty += empty_black_field;
					black_white_line += white_field;
					black_white_line_empty += empty_white_field;
				}
			}

			whole_white_black_line = "";
			whole_black_white_line = "";
			for (int i = 0; i < 3; i++)
			{
				if (i != 1)
				{
					whole_white_black_line += white_black_line + rim;
					whole_black_white_line += black_white_line + rim;
				}
				else
				{
					string line_number = to_string(8 - h);
					whole_white_black_line += line_number + white_black_line_empty + "| " + line_number + "\n";
					whole_black_white_line += line_number + black_white_line_empty + "| " + line_number + "\n";
				}
			}
			if (h % 2 == 0)
			{
				board += whole_white_black_line;
			}
			else
			{
				board += whole_black_white_line;
			}
		}
		cout << "\n";
		cout << number_helper << "\n";
		cout << border_helper << "\n";
		cout << board;
		cout << border_helper << "\n";
		cout << number_helper << "\n";
	}
};