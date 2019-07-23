#pragma once
#include <iostream>

#include "chess_board.hpp"
#include "type.hpp"

class gui {
public:
	chess_board cb;
	gui(chess_board cb) {
		this->cb = cb;
	}
	virtual void print_board() = 0;
};

class console_gui : public gui {
public:
	console_gui(chess_board cb) : gui(cb) {}

	void print_board() {
		string border_helper = "";
		string white_field = "|||||";
		string empty_white_field = "|| ||";
		string black_field = "     ";
		string white_black_line = "|";
		string white_black_line_empty = "|";
		string black_white_line = "|";
		string black_white_line_empty = "|";
		for (int i = 1; i < 9; i++) {
			border_helper += "--" + to_string(i) + "--";
			if (i % 2 == 1) {
				white_black_line += white_field;
				white_black_line_empty += empty_white_field;
				black_white_line += black_field;
				black_white_line_empty += black_field;
			}
			else {
				white_black_line += black_field;
				white_black_line_empty += black_field;
				black_white_line += white_field;
				black_white_line_empty += empty_white_field;
			}
		}
		string rim = "| \n";
		string whole_white_black_line = "";
		string whole_black_white_line = "";

		for (int j = 8; j > 0; j--) {
			for (int i = 0; i < 3; i++) {
				if (i != 1) {
					whole_white_black_line += white_black_line + rim;
					whole_black_white_line += black_white_line + rim;
				}
				else {
					whole_white_black_line += white_black_line_empty + "| " + to_string(j) "\n";
					whole_black_white_line += black_white_line_empty + rim;
				}
			}
		}


		string board = "";
		for (int i = 0; i < 4; i++) {
			board += whole_white_black_line + whole_black_white_line;
		}

		cout << "|" << border_helper << "| \n";
		cout << board;
		cout << "|" << border_helper << "| \n";
	}
};