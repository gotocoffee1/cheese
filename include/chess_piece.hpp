#pragma once
#include "type.hpp"

#include <limits>


enum class color
{
    white = 0,
    black,
    num,
    none,
};

enum class figure
{
    pawn = (int)color::num,
    knight,
    bishop,
    rook,
    queen,
    king,
    num,
    none,
};

struct chess_piece_info
{
    const char* name;
    const char* short_name;
    float value;
};

inline chess_piece_info get_info(figure f)
{
    switch (f)
    {
    case figure::pawn:
        return {
            "pawn",
            "P",
            1.f,
        };
    case figure::knight:
        return {
            "knight",
            "N",
            3.f,
        };
    case figure::bishop:
        return {
            "bishop",
            "B",
            3.f,
        };
    case figure::rook:
        return {
            "rook",
            "R",
            5.f,
        };
    case figure::queen:
        return {
            "queen",
            "Q",
            9.f,
        };
    case figure::king:
        return {
            "king",
            "K",
            0.f,
        };
    default:
        return {};
    }
}
