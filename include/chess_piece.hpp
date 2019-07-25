#pragma once
#include "type.hpp"
enum class color
{
	WHITE = 1,
	NONE = 0,
	BLACK = -1
};

class chess_piece
{
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
	string short_name = "";
	double value = 0.0;

	chess_piece(color c)
	{
		this->c = c;
	}
	/*
	color get_color()
	{
		//return color; //color nicht zulässig?
	}
	*/

	string get_short_name()
	{
		return short_name;
	}

	double get_value() {
		return value;
	}

	virtual bool is_move_valid(int stx, int sty, int destx, int desty) = 0;
};

class empty : public chess_piece
{
public:
	empty(color c) : chess_piece(c)
	{
		short_name = " ";
		value = 0;
	}

	bool is_move_valid(int stx, int sty, int destx, int desty) override
	{
		return false;
	}
};

class pawn : public chess_piece
{
public:
	pawn(color c) : chess_piece(c)
	{
		short_name = "P";
		value = 1;
	}

	bool is_move_valid(int stx, int sty, int destx, int desty) override
	{
		if (((stx == destx) && (((int)c * (desty - sty)) == 1 || ((int)c * (desty - sty) == 2))) ||
			((desty - sty) == (int)c && abs(destx - stx) == 1))
		{
			return true;
		}
		return false;
	}
};

class knight : public chess_piece
{
public:
	knight(color c) : chess_piece(c)
	{
		short_name = "H";
		value = 3;
	}

	bool is_move_valid(int stx, int sty, int destx, int desty) override
	{
		if (((abs(destx - stx) == 2) && (abs(desty - sty) == 1)) ||
			((abs(destx - stx) == 1) && (abs(desty - sty) == 2)))
		{
			return true;
		}
		return false;
	}
};

class bishop : public chess_piece
{
public:
	bishop(color c) : chess_piece(c)
	{
		short_name = "B";
		value = 3;
	}

	bool is_move_valid(int stx, int sty, int destx, int desty) override
	{
		if (abs(destx - stx) == abs(destx - sty) &&
			(abs(destx - stx) != 0) && (abs(desty - sty) != 0))
		{
			return true;
		}
		return false;
	}
};

class rook : public chess_piece
{
public:
	rook(color c) : chess_piece(c)
	{
		short_name = "R";
		value = 5;
	}

	bool is_move_valid(int stx, int sty, int destx, int desty) override
	{
		if (((destx == stx) && (desty != sty)) ||
			((destx != stx) && (desty != sty)))
		{
			return true;
		}
		return false;
	}
};

class queen : public chess_piece
{
public:
	queen(color c) : chess_piece(c)
	{
		short_name = "Q";
		value = 9;
	}

	bool is_move_valid(int stx, int sty, int destx, int desty) override
	{
		//if (bishop::is_move_valid(stx, sty, destx, desty) || rook::is_move_valid(stx, sty, destx, desty)) {
		//return true;
		//}
		return false;
	}
};

class king : public chess_piece
{
public:
	king(color c) : chess_piece(c)
	{
		short_name = "K";
		value = std::numeric_limits<float>::infinity();
	}

	bool is_move_valid(int stx, int sty, int destx, int desty) override
	{
		if (((abs(destx - stx) == 1) && (abs(desty - sty) <= 1)) ||
			((abs(destx - stx) <= 1) && (abs(desty - sty) == 1)))
		{
			return true;
		}
		return false;
	}
};