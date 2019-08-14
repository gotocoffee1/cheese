#pragma once

#include <array>
#include <tuple>

#include "chess_piece.hpp"

enum class column
{
    A = 0,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
};

enum class row
{
    _1 = 0,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
};

#define LINE(bit, num) (UINT64_C(bit) << ((num)*8))

class chess_board
{
private:
    std::array<uint64_t, (size_t)figure::num> board;
    int en_passant = -10;
    bool white_king_moved = false;
    bool black_king_moved = false;
    bool white_a_rook_moved = false;
    bool white_h_rook_moved = false;
    bool black_a_rook_moved = false;
    bool black_h_rook_moved = false;

public:
    inline const uint64_t& operator[](figure l) const
    {
        return board[(size_t)l];
    }

    inline const uint64_t& operator[](color l) const
    {
        return board[(size_t)l];
    }

    inline uint64_t& operator[](figure l)
    {
        return board[(size_t)l];
    }

    inline uint64_t& operator[](color l)
    {
        return board[(size_t)l];
    }

    std::tuple<figure, color> get(uint64_t mask) const
    {
        color c;
        if ((*this)[color::white] & mask)
            c = color::white;
        else if ((*this)[color::black] & mask)
            c = color::black;
        else
            return { figure::none, color::none };
        for (size_t i = (size_t)figure::pawn; i < (size_t)figure::num; ++i)
            if ((*this)[(figure)i] & mask)
                return { (figure)i, c };
        return { figure::none, color::none };
    }

    static inline uint64_t get_mask(column x, row y)
    {
        return ((UINT64_C(1) << (size_t)x) << ((size_t)y * 8));
    }

    static inline uint64_t get_mask(size_t x, size_t y)
    {
        if (x <= (size_t)column::H && y <= (size_t)row::_8)
            return get_mask((column)x, (row)y);
        return 0;
    }
    /*
    std::tuple<size_t, size_t> get_field(figure f, color col) const
    {
    }
	*/
    static inline void print_bit_field(uint64_t map)
    {
        string line0 = "";
        string line1 = "";
        string line2 = "";
        string line3 = "";
        string line4 = "";
        string line5 = "";
        string line6 = "";
        string line7 = "";

        for (size_t i = 0; i < 8; i++)
        {
            line0 += get_one(map, i) + " ";
            line1 += get_one(map, i + 8) + " ";
            line2 += get_one(map, i + 16) + " ";
            line3 += get_one(map, i + 24) + " ";
            line4 += get_one(map, i + 32) + " ";
            line5 += get_one(map, i + 40) + " ";
            line6 += get_one(map, i + 48) + " ";
            line7 += get_one(map, i + 52) + " ";
        }
        string line = line7 + "\n" + line6 + "\n" + line5 + "\n" + line4 + "\n" + line3 + "\n" + line2 + "\n" + line1 + "\n" + line0;
        cout << "\n"
             << line << "\n";
    }

    static inline string get_one(uint64_t map, size_t i)
    {
        if (map & (UINT64_C(1) << (i)))
        {
            return "1";
        }
        return "0";
    }

    static inline color not_col(color col)
    {
        return (color) !(size_t)col;
    }

    inline uint64_t king_in_chess(column c, row r, color col) const
    {
        uint64_t ret = get_mask(c, r);
        uint64_t opp_board = board[(size_t)not_col(col)];

        int direction = -1;
        if (col == color::white)
        {
            direction = 1;
		}

        if ((get_mask((int)c - 1, (int)r + direction) & board[(size_t)figure::pawn] & opp_board) ||
			(get_mask((int)c + 1, (int)r + direction) & board[(size_t)figure::pawn] & opp_board))
        {
            return ret;
        }
        if (get_all_possible_fields(c, r, figure::knight, col) & board[(size_t)figure::knight] & opp_board)
        {
			return ret;
        }
        if (get_all_possible_fields(c, r, figure::bishop, col) & board[(size_t)figure::bishop] & opp_board)
        {
            return ret;
        }
        if (get_all_possible_fields(c, r, figure::rook, col) & board[(size_t)figure::rook] & opp_board)
        {
            return ret;
        }
        if (get_all_possible_fields(c, r, figure::queen, col) & board[(size_t)figure::queen] & opp_board)
        {
            return ret;
        }
        return 0;
    }

    uint64_t get_all_possible_fields(column x, row y) const
    {
        auto [f, c] = get(get_mask(x, y));
        return get_all_possible_fields(x, y, f, c);
    }

    uint64_t get_all_possible_fields(column c, row r, figure f, color col) const
    {
        auto x = (size_t)c;
        auto y = (size_t)r;
        color op_col = not_col(col);

        // clang-format off
        switch (f)
        {
        case figure::pawn:
		{
			uint64_t moves = 0;
			size_t direction = -1;
			size_t start_position = 6;
			if (col == color::white)
			{
				direction = 1;
				start_position = 1;
			}
		
			//normal move
			if (get_mask(x, y + direction) & ~board[(size_t)color::white] & ~board[(size_t)color::black])
			{
				moves |= get_mask(x, y + direction);
				if ((y == start_position) && (get_mask(x, y + 2 * direction) & ~board[(size_t)color::white] & ~board[(size_t)color::black]))
				{
					moves |= get_mask(x, y + 2 * direction);
				}
			}

			//capture with en passant
			if (get_mask(x + 1, y + direction) & board[(size_t)op_col] || ((en_passant == x + 1) && (get_mask(x + 1, y) & board[(size_t)figure::pawn] & board[(size_t)op_col])))
			{
				moves |= get_mask(x + 1, y + direction);
			}
			if (get_mask(x - 1, y + direction) & board[(size_t)op_col] || ((en_passant == x - 1) && (get_mask(x - 1, y) & board[(size_t)figure::pawn] & board[(size_t)op_col])))
			{
				moves |= get_mask(x - 1, y + direction);
			}

			//change in last row
            
            return moves & ~board[(size_t)col];
		}

        case figure::knight:
        {
            const uint64_t moves = 0
            | get_mask(x + 2, y + 1)
            | get_mask(x + 2, y - 1)
            | get_mask(x + 1, y + 2)
            | get_mask(x + 1, y - 2)
            | get_mask(x - 2, y + 1)
            | get_mask(x - 2, y - 1)
            | get_mask(x - 1, y + 2)
            | get_mask(x - 1, y - 2)
            ;
            return moves & ~board[(size_t)col];
        }

		case figure::bishop:
		{
			uint64_t moves = 0;
			size_t diff = 1;
			bool lup_way = false;
			bool rup_way = false;
			bool ldown_way = false;
			bool rdown_way = false;

			for (size_t i = x + 1; diff < 8; i++) {
				diff = i - x;
				if (!rup_way && get_mask(x + diff, y + diff) & ~board[(size_t)col]) {
					moves |= get_mask(x + diff, y + diff);
					if (get_mask(x + diff, y + diff) & board[(size_t)op_col])
					{
						rup_way = true;
					}
				}
				else {
					rup_way = true;
				}

				if (!rdown_way && get_mask(x + diff, y - diff) & ~board[(size_t)col]) {
					moves |= get_mask(x + diff, y - diff);
					if (get_mask(x + diff, y - diff) & board[(size_t)op_col])
					{
						rdown_way = true;
					}
				}
				else {
					rdown_way = true;
				}
				
				if (!lup_way && get_mask(x - diff, y + diff) & ~board[(size_t)col]) {
					moves |= get_mask(x - diff, y + diff);
					if (get_mask(x - diff, y + diff) & board[(size_t)op_col])
					{
						lup_way = true;
					}
				}
				else {
					lup_way = true;
				}
				
				if (!ldown_way && get_mask(x - diff, y - diff) & ~board[(size_t)col]) {
					moves |= get_mask(x - diff, y - diff);
					if (get_mask(x - diff, y - diff) & board[(size_t)op_col])
					{
						ldown_way = true;
					}
				}
				else {
					ldown_way = true;
				}
			}
			return moves & ~board[(size_t)col];
		}

		case figure::rook:
		{
			uint64_t moves = 0;
			size_t diff = 1;
			bool up_way = false;
			bool down_way = false;
			bool right_way = false;
			bool left_way = false;


			for (size_t i = x + 1; diff < 8; i++) {
				diff = i - x;
				if (!right_way && get_mask(x + diff, y) & ~board[(size_t)col]) {
					moves |= get_mask(x + diff, y);
					if (get_mask(x + diff, y) & board[(size_t)op_col])
					{
						right_way = true;
					}
				}
				else {
					right_way = true;
				}

				if (!left_way && get_mask(x - diff, y) & ~board[(size_t)col]) {
					moves |= get_mask(x - diff, y);
					if (get_mask(x - diff, y) & board[(size_t)op_col])
					{
						left_way = true;
					}
				}
				else {
					left_way = true;
				}
				
				if (!up_way && get_mask(x, y + diff) & ~board[(size_t)col]) {
					moves |= get_mask(x, y + diff);
					if (get_mask(x, y + diff) & board[(size_t)op_col])
					{
						up_way = true;
					}
				}
				else {
					up_way = true;
				}
				
				if (!down_way && get_mask(x, y - diff) & ~board[(size_t)col]) {
					moves |= get_mask(x, y - diff);
					if (get_mask(x, y - diff) & board[(size_t)op_col])
					{
						down_way = true;
					}
				}
				else {
					down_way = true;
				}
			}

			//castleing?

			return moves & ~board[(size_t)col];
		}

		case figure::queen:
		{
			return get_all_possible_fields(c, r, figure::bishop, col) |
				get_all_possible_fields(c, r, figure::rook, col);
		}

		case figure::king:
		{
			//move
			uint64_t moves = 0
            | get_mask(x, y + 1)
            | get_mask(x + 1, y + 1)
            | get_mask(x + 1, y)
            | get_mask(x + 1, y - 1)
            | get_mask(x, y - 1)
            | get_mask(x - 1, y - 1)
            | get_mask(x - 1, y)
            | get_mask(x - 1, y + 1)
            ;
			moves &= ~king_in_chess((column)(x), (row)(y + 1), col)
			& ~king_in_chess((column)(x + 1), (row)(y + 1), col)
			& ~king_in_chess((column)(x + 1), (row)(y), col)
			& ~king_in_chess((column)(x + 1), (row)(y - 1), col)
			& ~king_in_chess((column)(x), (row)(y - 1), col)
			& ~king_in_chess((column)(x - 1), (row)(y - 1), col)
			& ~king_in_chess((column)(x - 1), (row)(y), col)
			& ~king_in_chess((column)(x - 1), (row)(y + 1), col);

			//opposition
			uint64_t enemy_king = board[(size_t)figure::king] & board[!(size_t)col];
			size_t ex = 0;
			size_t ey = 0;
			for (size_t i = 0; i < 64; i++)
			{
				if (enemy_king & (UINT64_C(1) << i))
				{
					ex = i % 8;
                    ey = i / 8;
					break;
				}
			}
			enemy_king = 0
            | get_mask(ex, ey + 1)
            | get_mask(ex + 1, ey + 1)
            | get_mask(ex + 1, ey)
            | get_mask(ex + 1, ey - 1)
            | get_mask(ex, ey - 1)
            | get_mask(ex - 1, ey - 1)
            | get_mask(ex - 1, ey)
            | get_mask(ex - 1, ey + 1)
            ;
			moves &= ~enemy_king;


			//castleing
			if (!king_in_chess((column)(x), (row)(y), col))
			{
				if (col == color::white)
				{
					if (!white_king_moved)
					{
						if (!white_a_rook_moved &&
							get_mask(1, 0) & ~board[(size_t)col] & ~board[(size_t)op_col] &&
							!king_in_chess((column)1, (row)0, col) &&
							get_mask(2, 0) & ~board[(size_t)col] & ~board[(size_t)op_col] &&
							!king_in_chess((column)2, (row)0, col) &&
							get_mask(3, 0) & ~board[(size_t)col] & ~board[(size_t)op_col] &&
							!king_in_chess((column)3, (row)0, col)
							)
						{
							moves |= get_mask(2, 0);
						}
						if (!white_h_rook_moved &&
							get_mask(5, 0) & ~board[(size_t)col] & ~board[(size_t)op_col] &&
							!king_in_chess((column)5, (row)0, col) &&
							get_mask(6, 0) & ~board[(size_t)col] & ~board[(size_t)op_col] &&
							!king_in_chess((column)6, (row)0, col)
							)
						{
							moves |= get_mask(6, 0);
						}
					}
				}
				else {

				}
			}


			//in chess?

            return moves & ~board[(size_t)col];
			
		}


        default:
			return UINT64_C(0); // no moves are valid;
        }
        // clang-format on
    }

    void set(uint64_t mask, figure f, color col)
    {
        (*this)[f] |= mask;
        (*this)[col] |= mask;
    }

    void clear(uint64_t mask, figure f, color col)
    {
        (*this)[f] &= ~mask;
        (*this)[col] &= ~mask;
    }


    void move(column sx, row sy, column tx, row ty)
    {
        auto source = get_mask(sx, sy);
        auto target = get_mask(tx, ty);

        auto [f, c] = get(source);

        auto ok = get_all_possible_fields(sx, sy, f, c);
        if (ok & target)
        {
            auto [tf, tc] = get(target);
            if (tf != figure::none)
                clear(target, tf, tc);
            clear(source, f, c);
            set(target, f, c);

            //en passant
            if (f == figure::pawn && en_passant == (int)tx)
            {
                clear(get_mask(tx, sy), f, not_col(c));
            }

            if (f == figure::pawn && ((int)sy == 6 && (int)ty == 4) || ((int)sy == 1 && (int)ty == 3))
            {
                en_passant = (int)sx;
            }
            else
            {
                en_passant = -10;
            }
        }
    }

    chess_board()
    {
        // clang-format off
		board[(size_t)color::white] = 0
        | LINE(0b00000000, 7)
        | LINE(0b00000000, 6)
        | LINE(0b00000000, 5)
        | LINE(0b00000000, 4)
        | LINE(0b00000000, 3)
        | LINE(0b00000000, 2)
        | LINE(0b00000000, 1)
        | LINE(0b10010001, 0)
        ;
		board[(size_t)color::black] = 0
        | LINE(0b10010001, 7)
        | LINE(0b00000000, 6)
        | LINE(0b00000000, 5)
        | LINE(0b00000000, 4)
        | LINE(0b00000000, 3)
        | LINE(0b00000000, 2)
        | LINE(0b00000000, 1)
        | LINE(0b00000000, 0)
        ;
		board[(size_t)figure::pawn] = 0;
		board[(size_t)figure::knight] = 0;
		board[(size_t)figure::bishop] = 0;
		        board[(size_t)figure::rook] = 0
        | LINE(0b10000001, 7)
        | LINE(0b00000000, 6)
        | LINE(0b00000000, 5)
        | LINE(0b00000000, 4)
        | LINE(0b00000000, 3)
        | LINE(0b00000000, 2)
        | LINE(0b00000000, 1)
        | LINE(0b10000001, 0)
        ;
		board[(size_t)figure::queen] = 0;

		board[(size_t)figure::king] = 0
        | LINE(0b00010000, 7)
        | LINE(0b00000000, 6)
        | LINE(0b00000000, 5)
        | LINE(0b00000000, 4)
        | LINE(0b00000000, 3)
        | LINE(0b00000000, 2)
        | LINE(0b00000000, 1)
        | LINE(0b00010000, 0)
        ;

        // clang-format on
        //start_position();
    }

    void start_position()
    {
        // clang-format off
        board[(size_t)color::white] = 0
        | LINE(0b00000000, 7)
        | LINE(0b00000000, 6)
        | LINE(0b00000000, 5)
        | LINE(0b00000000, 4)
        | LINE(0b00000000, 3)
        | LINE(0b00000000, 2)
        | LINE(0b11111111, 1)
        | LINE(0b11111111, 0)
        ;

        board[(size_t)color::black] = 0
        | LINE(0b11111111, 7)
        | LINE(0b11111111, 6)
        | LINE(0b00000000, 5)
        | LINE(0b00000000, 4)
        | LINE(0b00000000, 3)
        | LINE(0b00000000, 2)
        | LINE(0b00000000, 1)
        | LINE(0b00000000, 0)
        ;

        board[(size_t)figure::pawn] = 0
        | LINE(0b00000000, 7)
        | LINE(0b11111111, 6)
        | LINE(0b00000000, 5)
        | LINE(0b00000000, 4)
        | LINE(0b00000000, 3)
        | LINE(0b00000000, 2)
        | LINE(0b11111111, 1)
        | LINE(0b00000000, 0)
        ;

        board[(size_t)figure::knight] = 0
        | LINE(0b01000010, 7)
        | LINE(0b00000000, 6)
        | LINE(0b00000000, 5)
        | LINE(0b00000000, 4)
        | LINE(0b00000000, 3)
        | LINE(0b00000000, 2)
        | LINE(0b00000000, 1)
        | LINE(0b01000010, 0)
        ;

        board[(size_t)figure::bishop] = 0
        | LINE(0b00100100, 7)
        | LINE(0b00000000, 6)
        | LINE(0b00000000, 5)
        | LINE(0b00000000, 4)
        | LINE(0b00000000, 3)
        | LINE(0b00000000, 2)
        | LINE(0b00000000, 1)
        | LINE(0b00100100, 0)
        ;

        board[(size_t)figure::rook] = 0
        | LINE(0b10000001, 7)
        | LINE(0b00000000, 6)
        | LINE(0b00000000, 5)
        | LINE(0b00000000, 4)
        | LINE(0b00000000, 3)
        | LINE(0b00000000, 2)
        | LINE(0b00000000, 1)
        | LINE(0b10000001, 0)
        ;

        board[(size_t)figure::queen] = 0
        | LINE(0b00001000, 7)
        | LINE(0b00000000, 6)
        | LINE(0b00000000, 5)
        | LINE(0b00000000, 4)
        | LINE(0b00000000, 3)
        | LINE(0b00000000, 2)
        | LINE(0b00000000, 1)
        | LINE(0b00001000, 0)
        ;

        board[(size_t)figure::king] = 0
        | LINE(0b00010000, 7)
        | LINE(0b00000000, 6)
        | LINE(0b00000000, 5)
        | LINE(0b00000000, 4)
        | LINE(0b00000000, 3)
        | LINE(0b00000000, 2)
        | LINE(0b00000000, 1)
        | LINE(0b00010000, 0)
        ;
        // clang-format on
    }
};
