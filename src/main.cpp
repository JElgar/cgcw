#include <DrawingWindow.h>
#include <fstream>
#include <vector>
#include <math.h>
#include <cmath>
#include "CanvasLine.h"
#include "CanvasTriangle.h"
#include "TextureMap.h"

#define WIDTH 512
#define HEIGHT 512

//void update(DrawingWindow &window, Camera &camera, ObjModel &model) {
//	window.clearPixels();
//	camera.rotate(0.06, 0.06, 0.06);
//  model.draw(window, camera, 20);
//}

void handleEvent(SDL_Event event, DrawingWindow &window) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT) {
		} else if (event.key.keysym.sym == SDLK_RIGHT) {
		} else if (event.key.keysym.sym == SDLK_UP) {
		} else if (event.key.keysym.sym == SDLK_DOWN) {
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
		}
	}
}

int main(int argc, char *argv[]) {
	DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);

	//Camera camera = Camera(0, 0, 10, 15);
	SDL_Event event;

    //CanvasLine(CanvasPoint(0,0, -1), CanvasPoint(100,100, -1)).draw(Colour(255, 0, 0), window);
    //
    Colour colour = Colour(0, 255, 255);
    CanvasTriangle(CanvasPoint(0,0, -1), CanvasPoint(255,400, -1), CanvasPoint(200, 200, -1)).fill(colour, window);

    window.savePixelBufferToFile("tests/fixtures/fill_triangle-512x512.txt");

	while (true) {
		// We MUST poll for events - otherwise the window will freeze !
		if (window.pollForInputEvents(event)) handleEvent(event, window);
		//update(window, camera, model);
		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		window.renderFrame();
	}
}
