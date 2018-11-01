/*
	main.c

	Classic Pong game clone.

	Written by Alberto Cairo.
*/

#include <stdbool.h>
#include "SDL.h"

static const int WINDOW_WIDTH = 640;	// Pixels
static const int WINDOW_HEIGHT = 480;

static const int RACKET_WIDTH = 16;		// Pixels
static const int RACKET_HEIGHT = 64;

static void reset_rackets(
	SDL_Rect rackets[2]
);

static void update_rackets(
	SDL_Rect rackets[2],
	int mouse_y
);

static void render_rackets(
	SDL_Surface* surface,
	const SDL_Rect rackets[2]
);

int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow(
		"Gonp",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0
	);
	if (window == NULL) {
		SDL_Quit();
		return 1;
	}

	SDL_ShowCursor(0);

	SDL_Surface* window_surface = SDL_GetWindowSurface(window);

	SDL_Rect rackets[2];
	reset_rackets(rackets);

	int mouse_x;
	int mouse_y;
	SDL_Event event;
	bool quit = false;
	while (!quit) {
		SDL_FillRect(
			window_surface,
			NULL,
			SDL_MapRGB(
				window_surface->format,
				0, 0, 0
			)
		);
		render_rackets(window_surface, rackets);
		SDL_UpdateWindowSurface(window);

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;
				default:
					break;
			}
		}

		SDL_GetMouseState(&mouse_x, &mouse_y);
		update_rackets(rackets, mouse_y);
	}

	SDL_Quit();

	return 0;
}

static void render_rackets(
	SDL_Surface* surface,
	const SDL_Rect rackets[2]
) {
	for (int i = 0; i < 2; ++i) {
		SDL_FillRect(
			surface,
			&rackets[i],
			SDL_MapRGB(
				surface->format,
				255, 255, 255
			)
		);
	}
}

static void reset_rackets(
	SDL_Rect rackets[2]
) {
	rackets[0].x = 0;
	rackets[1].x = WINDOW_WIDTH - RACKET_WIDTH;

	for (int i = 0; i < 2; ++i) {
		rackets[i].y = 0;
		rackets[i].w = RACKET_WIDTH;
		rackets[i].h = RACKET_HEIGHT;
	}
}

static void update_rackets(
	SDL_Rect rackets[2],
	int mouse_y
) {
	int new_y = mouse_y - RACKET_HEIGHT / 2;

	if (new_y < 0) {
		new_y = 0;
	} else if (new_y + RACKET_HEIGHT > WINDOW_HEIGHT) {
		new_y = WINDOW_HEIGHT - RACKET_HEIGHT;
	}

	rackets[0].y = new_y;
	rackets[1].y = new_y;
}
