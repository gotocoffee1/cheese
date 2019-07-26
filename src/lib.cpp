#include "chess_board.hpp"
#include "gui.hpp"

#include <SDL.h>

int run(int argc, char** argv)
{
	chess_board board;
	console_gui cg(board);
	cg.print_board();





	SDL_Window* window; // Declare a pointer

	SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2

	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"An SDL2 window",		 // window title
		SDL_WINDOWPOS_UNDEFINED, // initial x position
		SDL_WINDOWPOS_UNDEFINED, // initial y position
		640,					 // width, in pixels
		480,					 // height, in pixels
		SDL_WINDOW_OPENGL		 // flags - see below
	);

	// Check that the window was successfully created
	if (window == NULL)
	{
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}


	// The window is open: could enter program loop here (see SDL_PollEvent())

	//SDL_Delay(3000); // Pause execution for 3000 milliseconds, for example

	// Close and destroy the window
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();

	while (true) {
		int stx = -1, sty = -1, destx = -1, desty = -1;
		cin >> stx;
		cin >> sty;
		cin >> destx;
		cin >> desty;

		if (stx > -1 && sty > -1 && destx > -1 && desty > -1) {
			board.move(stx, sty, destx, desty);
			cg.set_board(board);
			cg.print_board();
		}
		
		
	}
	return 0;
}