#include "lib.hpp"

#include "chess_board.hpp"
#include "gui.hpp"
#include "renderer.hpp"

int run(int argc, char** argv)
{
    chess_board board;
    console_gui cg(board);
    cg.print_board();

    {
        cheese::renderer().launch(argc, argv);
    }

    while (true)
    {
        int stx = -1, sty = -1, destx = -1, desty = -1;
        cin >> stx;
        cin >> sty;
        cin >> destx;
        cin >> desty;

        if (stx > -1 && sty > -1 && destx > -1 && desty > -1 &&
            stx < 8 && sty < 8 && destx < 8 && desty < 8)
        {
            board.move(stx, sty, destx, desty);
            cg.print_board();
        }
        else
        {
            cout << "Werte nicht g�ltig \n";
        }
    }
    return 0;
}