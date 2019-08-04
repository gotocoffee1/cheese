#pragma once
#include "chess_piece.hpp"
#include "chess_field.hpp"

class chess_board
{
public:
    //board_field[y][x]
    chess_field board_field[8][8];

    chess_board()
    {
        //Chess starting positions
        for (int i = 0; i < 8; i++)
        {
            board_field[1][i].set_piece(new pawn(color::BLACK));
            board_field[6][i].set_piece(new pawn(color::WHITE));
            for (int j = 0; j < 8; j++)
            {

                if ((i > 1) && (i < 6))
                {
                    board_field[i][j].set_piece(new empty());
                }
            }
        }

        board_field[0][0].set_piece(new rook(color::BLACK));
        board_field[1][3].set_piece(new empty());

        board_field[0][1].set_piece(new knight(color::BLACK));
        board_field[0][2].set_piece(new bishop(color::BLACK));
        board_field[0][3].set_piece(new queen(color::BLACK));
        board_field[0][4].set_piece(new king(color::BLACK));
        board_field[0][5].set_piece(new bishop(color::BLACK));
        board_field[0][6].set_piece(new knight(color::BLACK));
        board_field[0][7].set_piece(new rook(color::BLACK));

        board_field[7][0].set_piece(new rook(color::WHITE));
        board_field[7][1].set_piece(new knight(color::WHITE));
        board_field[7][2].set_piece(new bishop(color::WHITE));
        board_field[7][3].set_piece(new queen(color::WHITE));
        board_field[7][4].set_piece(new king(color::WHITE));
        board_field[7][5].set_piece(new bishop(color::WHITE));
        board_field[7][6].set_piece(new knight(color::WHITE));
        board_field[7][7].set_piece(new rook(color::WHITE));
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
            cout << "keine Figur gewählt";
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

        //König nachher im Schach?

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