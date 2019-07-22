#pragma once
#include "type.hpp"
enum class color {
	WHITE = 1,
	BLACK = -1
};

class chess_piece {
	/*
	EMPTY,
	PAWN,
	KNIGHT,
	BISHOP,
	ROOK,
	QUEEN,
	KING
	*/
public:
	color c;
	chess_piece(color c) {
		this->c = c;
	}
	virtual bool is_move_valid(int stx, int sty, int destx, int desty) = 0;
};

class pawn : public chess_piece {
public:
	pawn(color c) {
		super(c);
	}
	bool is_move_valid(int stx, int sty, int destx, int desty) override{
		if (((stx == destx) && (((int)c * (desty - sty)) == 1 || ((int)c * (desty - sty) == 2))) ||
			((desty - sty) == c && abs(destx - stx) == 1)
		) {
			return true;
		}
		return false;
	}
};