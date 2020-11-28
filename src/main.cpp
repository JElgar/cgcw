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

    CanvasLine(CanvasPoint(0,0, -1), CanvasPoint(100,100, -1)).draw(Colour(255, 0, 0), window);
    
    CanvasTriangle(CanvasPoint(0,0, -1), CanvasPoint(300,100, -1), CanvasPoint(100, 50, -1)).draw(Colour(255, 0, 0), window);
    
    TextureMap texture = TextureMap("assets/texture.ppm");

    TexturePoint texture1 = TexturePoint(195, 5);
    TexturePoint texture2 = TexturePoint(395, 380);
    TexturePoint texture3 = TexturePoint(65, 330);

    CanvasTriangle(CanvasPoint(160,10, -1, texture1), CanvasPoint(300,230, -1, texture2), CanvasPoint(10, 150, -1, texture3)).mapTexture(texture, window);

    // glm::vec2 from = glm::vec2(195, 5);
    // glm::vec2 to = glm::vec2(65, 330);
    // std::vector<glm::vec2> interpolatedStuff = interpolate(from, to, 140);
    // for (int i = 0; i < interpolatedStuff.size(); i++) {
    //   std::cout << "Value " << i << ": " << interpolatedStuff[i].x << ", " <<  interpolatedStuff[i].y << std::endl;
    // }


	while (true) {
		// We MUST poll for events - otherwise the window will freeze !
		if (window.pollForInputEvents(event)) handleEvent(event, window);
		//update(window, camera, model);
		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		window.renderFrame();
	}
}
