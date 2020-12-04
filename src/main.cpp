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

void update(DrawingWindow &window, Camera &camera, ObjModel &model) {
  //window.clearPixels();
  //camera.rotate(0.06, 0.06, 0.06);
  //model.draw(window, camera, 1);
}

void handleEvent(SDL_Event event, DrawingWindow &window, Camera &camera) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT) {
          camera.rotate(0, -0.06, 0.00);
		} else if (event.key.keysym.sym == SDLK_RIGHT) {
          camera.rotate(0, 0.06, 0.00);
		} else if (event.key.keysym.sym == SDLK_UP) {
          camera.translate(0, 0, -0.6);
		} else if (event.key.keysym.sym == SDLK_DOWN) {
          camera.translate(0, 0, 0.6);
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
		}
	}
}

int main(int argc, char *argv[]) {
	DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);

	//Camera camera = Camera(0, 0, 80, 30);
	Camera camera = Camera(0, 0, 4, 2);
	SDL_Event event;

    //Light light = Light(glm::vec3(0.110042, 0.465659, 0.0556608));
    Light light = Light(glm::vec3(0.0, 0.4, 0.05));
    //Light light = Light(glm::vec3(0, 0.45, 0), 2);
    //Light light = Light(glm::vec3(0.0, 0.0, 0.6), 2.0);
    std::vector<Light> lights;
    lights.push_back(light);

    //ObjModel model = ObjModel("assets/", "textured-cornell-box.obj", 20);
    //ObjModel model = ObjModel("assets/", "textured-cornell-box.obj", 0.17);
    ObjModel model = ObjModel("assets/", "cornell-box.obj", 0.17);
    model.drawRayTracing(window, camera, lights, 500);
    //model.draw(window, camera, 1);
    

	while (true) {
		// We MUST poll for events - otherwise the window will freeze !
		if (window.pollForInputEvents(event)) handleEvent(event, window, camera);
		update(window, camera, model);
		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		window.renderFrame();
	}
}
