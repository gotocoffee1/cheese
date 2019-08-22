#pragma once

#include "compressed_board.hpp"

namespace cheese
{
    class brain
    {
    private:
        chess_board& cb;

    public:
        brain(chess_board& cb) : cb(cb) {}

        void create_all_possible_boards()
        {
            
        }
    };
}