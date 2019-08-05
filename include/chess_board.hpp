#pragma once

#include <array>

#include "chess_piece.hpp"
#include "chess_field.hpp"


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
public:
    //board_field[y][x]
    chess_field board_field[8][8];
    std::array<uint64_t, (size_t)color::num> board;

    bool is(figure l, row x, column y) const
    {
        return board[(size_t)l] & ((UINT64_C(1) << (size_t)x) << ((size_t)y * 8));
    }

    bool is(color l, row x, column y) const
    {
        return board[(size_t)l] & ((UINT64_C(1) << (size_t)x) << ((size_t)y * 8));
    }

    std::tuple<figure, color> get(row x, column y) const
    {
        const uint64_t mask = ((UINT64_C(1) << (size_t)x) << ((size_t)y * 8));

        color c;
        if (apply(color::white, mask))
            c = color::white;
        else if (apply(color::black, mask))
            c = color::black;
        else
            return { figure::none, color::none };
        for (size_t i = 0; i < (size_t)figure::num; ++i)
            if (apply(i, mask))
                return { (figure)i, c };
        return { figure::none, color::none };
    }

    uint64_t apply(figure layer, uint64_t mask) const
    {
        return board[(size_t)layer] & mask;
    }

    uint64_t apply(color layer, uint64_t mask) const
    {
        return board[(size_t)layer] & mask;
    }

    uint64_t apply(size_t layer, uint64_t mask) const
    {
        return board[layer] & mask;
    }

    chess_board()
    {
        // clang-format off
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
		| LINE(0b00010000, 7)
		| LINE(0b00000000, 6)
		| LINE(0b00000000, 5)
		| LINE(0b00000000, 4)
		| LINE(0b00000000, 3)
		| LINE(0b00000000, 2)
		| LINE(0b00000000, 1)
		| LINE(0b00010000, 0)
		;

		board[(size_t)figure::king] = 0
		| LINE(0b00001000, 7)
		| LINE(0b00000000, 6)
		| LINE(0b00000000, 5)
		| LINE(0b00000000, 4)
		| LINE(0b00000000, 3)
		| LINE(0b00000000, 2)
		| LINE(0b00000000, 1)
		| LINE(0b00001000, 0)
		;

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
        // clang-format on
        //Chess starting positions
        for (int i = 0; i < 8; i++)
        {
            board_field[1][i].set_piece(new pawn(color::black));
            board_field[6][i].set_piece(new pawn(color::white));
            for (int j = 0; j < 8; j++)
            {

                if ((i > 1) && (i < 6))
                {
                    board_field[i][j].set_piece(new empty());
                }
            }
        }

        board_field[0][0].set_piece(new rook(color::black));
        board_field[1][3].set_piece(new empty());

        board_field[0][1].set_piece(new knight(color::black));
        board_field[0][2].set_piece(new bishop(color::black));
        board_field[0][3].set_piece(new queen(color::black));
        board_field[0][4].set_piece(new king(color::black));
        board_field[0][5].set_piece(new bishop(color::black));
        board_field[0][6].set_piece(new knight(color::black));
        board_field[0][7].set_piece(new rook(color::black));

        board_field[7][0].set_piece(new rook(color::white));
        board_field[7][1].set_piece(new knight(color::white));
        board_field[7][2].set_piece(new bishop(color::white));
        board_field[7][3].set_piece(new queen(color::white));
        board_field[7][4].set_piece(new king(color::white));
        board_field[7][5].set_piece(new bishop(color::white));
        board_field[7][6].set_piece(new knight(color::white));
        board_field[7][7].set_piece(new rook(color::white));
    }

    void move(int stx, int sty, int destx, int desty)
    {
        string short_name = (*board_field[sty][stx].get_piece()).get_short_name();
        cout << short_name;
        if (short_name != " " && valid_pre_conditions(stx, sty, destx, desty))
        {
            if (short_name == "P" && move_pawn(stx, sty, destx, desty))
            {
                move_piece(stx, sty, destx, desty);
            }
            else
            {
                if (short_name == "H" && move_knight(stx, sty, destx, desty))
                {
                    move_piece(stx, sty, destx, desty);
                }
                else
                {
                    if (short_name == "B" && move_bishop(stx, sty, destx, desty))
                    {
                        move_piece(stx, sty, destx, desty);
                    }
                    else
                    {
                        if (short_name == "R" && move_rook(stx, sty, destx, desty))
                        {
                            move_piece(stx, sty, destx, desty);
                        }
                        else
                        {
                            if (short_name == "Q" && move_queen(stx, sty, destx, desty))
                            {
                                move_piece(stx, sty, destx, desty);
                            }
                            else
                            {
                                if (short_name == "K")
                                {
                                    move_king(stx, sty, destx, desty);
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            cout << "keine Figur gew�hlt";
        }
    }

    void move_piece(int stx, int sty, int destx, int desty)
    {
        string short_name = (*board_field[sty][stx].get_piece()).get_short_name();
        cout << "piece to move" << short_name << "\n";
        color col = (*board_field[sty][stx].get_piece()).c;
        if ((*board_field[sty][stx].get_piece()).is_move_valid(stx, sty, destx, desty))
        {

            chess_piece* old_piece;
            //board_field[desty][destx].set_piece(board_field[sty][stx].get_piece());

            if (short_name == "P")
            {
                old_piece = new pawn(col);
            }
            else
            {
                if (short_name == "H")
                {
                    old_piece = new knight(col);
                }
                else
                {
                    if (short_name == "B")
                    {
                        old_piece = new bishop(col);
                    }
                    else
                    {
                        if (short_name == "R")
                        {
                            old_piece = new rook(col);
                        }
                        else
                        {
                            if (short_name == "Q")
                            {
                                old_piece = new queen(col);
                            }
                            else
                            {
                                if (short_name == "K")
                                {
                                    old_piece = new king(col);
                                }
                            }
                        }
                    }
                }
            }

            board_field[desty][destx].set_piece(old_piece); //TODO noch die eigenschaften der figur gettn
            board_field[sty][stx].set_piece(new empty());
        }
    }

    bool move_pawn(int stx, int sty, int destx, int desty)
    {
        color c = (*board_field[sty][stx].get_piece()).c;
        bool figure_in_the_way = false;
        //if ((*board_field[sty + 1][stx].get_piece()))
        if (((stx == destx) && (((int)c * (desty - sty)) == 1 || ((int)c * (desty - sty) == 2))) ||
            ((desty - sty) == (int)c && abs(destx - stx) == 1))
        {
            return true;
        }
        return false;
    }

    bool move_knight(int stx, int sty, int destx, int desty)
    {
        if (((abs(destx - stx) == 2) && (abs(desty - sty) == 1)) ||
            ((abs(destx - stx) == 1) && (abs(desty - sty) == 2)))
        {
            return true;
        }
        return false;
    }

    bool move_bishop(int stx, int sty, int destx, int desty)
    {
        bool figure_in_the_way = false;
        int y_adder = 1;
        int x_adder = 1;
        int counter = 1;
        if (desty < sty)
        {
            y_adder = -1;
        }
        cout << y_adder;
        for (int i = stx; i < abs(destx - stx) + stx; (destx > stx) ? i++ : (i--, x_adder = -1))
        {
            cout << (sty + y_adder * counter) << " sty i " << (i + x_adder);
            chess_piece* piece = board_field[sty + y_adder * counter][i + x_adder].get_piece();
            if ((*piece).get_short_name() != " ")
            {
                cout << "\n piece in da way" + (*piece).get_short_name() + "\n";
                figure_in_the_way = true;
                break;
            }
            counter++;
        }
        if (!figure_in_the_way)
        {
            move_piece(stx, sty, destx, desty);
            return true;
        }
        return false;
    }

    bool move_rook(int stx, int sty, int destx, int desty)
    {
        bool figure_in_the_way = false;
        int direction = sty;
        int direction_max = desty;
        int addition = 1;
        if (stx != destx)
        {
            direction = stx;
            direction_max = destx;
        }
        cout << direction << direction_max;
        for (int i = direction; i < direction_max; (direction_max > direction) ? i++ : (i--, addition = -1))
        {
            chess_piece* piece;
            if (stx != destx)
            {
                piece = board_field[sty][i + addition].get_piece();
            }
            else
            {
                piece = board_field[i + addition][stx].get_piece();
            }

            if ((*piece).get_short_name() != " ")
            {
                cout << "\n" + (*piece).get_short_name() + "\n";
                figure_in_the_way = true;
                break;
            }
        }
        if (!figure_in_the_way)
        {
            return true;
        }
        else
        {
            cout << "rook in da way";
        }
        return false;
    }

    bool move_queen(int stx, int sty, int destx, int desty)
    {
		if (move_bishop(stx, sty, destx, desty) || move_rook(stx, sty, destx, desty))
		{
            return true;
		}
        return false;
    }

	bool move_king(int stx, int sty, int destx, int desty)
    {
        return true;
    }

    bool valid_pre_conditions(int stx, int sty, int destx, int desty)
    {
        if (!coord_valid(stx, sty, destx, desty))
        {
            cout << "gleiche Koordinaten";
            return false;
        }
        if (same_color(stx, sty, destx, desty))
        {
            cout << "gleiche Farbe";
            return false;
        }

        //K�nig nachher im Schach?

        return true;
    }

    bool coord_valid(int stx, int sty, int destx, int desty)
    {
        if (stx == destx && sty == desty)
        {
            return false;
        }
        /*
		if (stx > 7 || stx < 0)
		{
			return false;
		}
		if (sty > 7 || sty < 0)
		{
			return false;
		}
		if (destx > 7 || destx < 0)
		{
			return false;
		}
		if (desty > 7 || desty < 0)
		{
			return false;
		}
		*/

        return true;
    }

    bool same_color(int stx, int sty, int destx, int desty)
    {
        color cst = (*board_field[sty][stx].get_piece()).c;
        color cdest = (*board_field[desty][destx].get_piece()).c;
        if (cst == cdest)
        {
            return true;
        }

        return false;
    }

    bool figure_on_field(int stx, int sty)
    {
        string short_name = (*board_field[sty][stx].get_piece()).get_short_name();
        if (short_name == " ")
        {
            return false;
        }

        return true;
    }
};
