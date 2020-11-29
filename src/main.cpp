#include <DrawingWindow.h>
#include <fstream>
#include <vector>
#include <math.h>
#include <cmath>
#include "CanvasLine.h"
#include "CanvasTriangle.h"
#include "TextureMap.h"
#include "ModelTriangle.h"
#include "ObjModel.h"

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

	Camera camera = Camera(0, 0, 2, 15);
	SDL_Event event;

    ModelTriangle triangle = ModelTriangle(ModelPoint(100, 100, -10), ModelPoint(100, 200, -10), ModelPoint(400, 300, -10));

    Colour colour = Colour(255, 0, 0);
    triangle.draw(colour, window, camera, 10);

    ObjModel model = ObjModel("assets/", "cornell-box.obj", 0.17);
    model.draw(window, camera, 40);

	while (true) {
		// We MUST poll for events - otherwise the window will freeze !
		if (window.pollForInputEvents(event)) handleEvent(event, window);
		//update(window, camera, model);
		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		window.renderFrame();
	}
}
