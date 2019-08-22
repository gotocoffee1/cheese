#include "chess_board.hpp"

#include "doctest.h"

TEST_CASE("cheese_board")
{
    chess_board cb;
    cb.start_position();

    CHECK(cb[figure::pawn] == UINT64_C(0x00FF00000000FF00));
    CHECK(cb[figure::rook] == UINT64_C(0x8100000000000081));

}