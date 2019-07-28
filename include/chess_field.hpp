#pragma once
#include "chess_piece.hpp"
#include <memory>

class chess_field
{
public:
	std::unique_ptr < chess_piece > piece;


	chess_field()
	{
		piece = nullptr;
	}

	void set_piece(chess_piece* cp)
	{
		piece.reset(cp);
	}

	chess_piece* get_piece()
	{
		return piece.get();
	}
};