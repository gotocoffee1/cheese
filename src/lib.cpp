#include "lib.hpp"

#include "chess_board.hpp"
#include "gui.hpp"
#include "renderer.hpp"

int run(int argc, char** argv)
{
    chess_board board;

    cheese::renderer(board).launch(argc, argv);

    console_gui cg(board);

    while (false)
    {
        cg.print_board();

        int stx = -1, sty = -1, destx = -1, desty = -1;
        cin >> stx;
        cin >> sty;
        cin >> destx;
        cin >> desty;

        if (stx > -1 && sty > -1 && destx > -1 && desty > -1 &&
            stx < 8 && sty < 8 && destx < 8 && desty < 8)
        {
            board.move((column)stx, (row)sty, (column)destx, (row)desty);
        }
        else
        {
            cout << "Werte nicht g�ltig \n";
        }
    }
    return 0;
}