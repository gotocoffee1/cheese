#pragma once
#include "chess_piece.hpp"

class chess_field {
public:
	chess_piece *piece;


	chess_field() {
		piece = nullptr;
	}

	void set_piece(chess_piece *cp){
		piece = cp;
	}
};