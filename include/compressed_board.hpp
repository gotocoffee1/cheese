#pragma once

#include <memory>
#include <cstring>
#include <cstddef>

#include "type.hpp"
#include "chess_board.hpp"

class compressed_board
{
private:
    std::unique_ptr<std::byte[]> bytes;

public:
    compressed_board(const chess_board& cb)
    {
        uint64_t all = cb[color::white] | cb[color::black];
        std::array<std::byte, 184U> max_mem = {};
        size_t size = 0;
        for (size_t i = 0; i < 64; ++i)
        {
            uint64_t mask = UINT64_C(1) << i;
            auto [f, c] = cb.get(mask);
            if (c != color::none)
            {
                //if (f == figure::king)

                max_mem[size / 2] |= ((((std::byte)c) << 3) | ((std::byte)f)) << (4 * (size % 2));
                size++;
            }
        }
        size = (size + 1) / 2;

        bytes = std::make_unique<std::byte[]>(size + sizeof(all));
        std::memcpy(bytes.get(), &all, sizeof(all));
        std::memcpy(bytes.get() + sizeof(all), &max_mem[0], size);
    }
    
    void uncompress(chess_board& cb)
    {
        uint64_t all;
        std::memcpy(&all, bytes.get(), sizeof(all));
        size_t pos = 16;
        for (size_t i = 0; i < 64; ++i)
        {
            uint64_t mask = UINT64_C(1) << i;
            if (all & mask)
            {
                //if (f == figure::king)
                auto b = bytes[pos / 2];
                if (pos % 2)
                    b >>= 4;
                else
                    b &= std::byte{0b1111};
                    
                cb.set(mask, (figure)(b & std::byte{0b0111}), (color)((b & std::byte{0b1000}) >> 4));
                pos++;
            }
        }
    }

    //Hex Description
    //+---+---------------------------------------------+
    //| 0 | King; White to move next              |
    //| 1 | Rook (pre castle) / Pawn (en Passant) |
    //| 2 | Pawn (normal)                         |
    //| 3 | Knight                                |
    //| 4 | Bishop                                |
    //| 5 | Rook (has moved)                      |
    //| 6 | Queen                                 |
    //| 7 | King                                  |
    // bit 4 -> color
    //+---+---------------------------------------------+
};
