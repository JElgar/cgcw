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
#include "CircularLight.h"

#define WIDTH 640
#define HEIGHT 480

//#define WIDTH 256
//#define HEIGHT 256

void update(DrawingWindow &window, Camera &camera, ObjModel &model, std::vector<Light*> lights, CameraTransition &transition) {
  //if (RENDER_MODE != RayTracing) {
    //camera.rotate(0.06, 0.06, 0.06);
  window.clearPixels();
  //camera.translate(0, 0, -0.05);
  //}
  lights[0]->translate(glm::vec3(0, 0.1, 0));
  camera.transition(transition, window.frame());
  model.draw(window, camera, lights, 500);
  //camera.rotate(0, 0.1, 0);
}

void handleEvent(SDL_Event event, DrawingWindow &window, Camera &camera) {
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_LEFT) {
          camera.translate(-0.6, 0, 0.00);
		} else if (event.key.keysym.sym == SDLK_RIGHT) {
          camera.translate(0.6, 0, 0.00);
		} else if (event.key.keysym.sym == SDLK_UP) {
          camera.translate(0, -0.6, 0);
		} else if (event.key.keysym.sym == SDLK_DOWN) {
          camera.translate(0, 0.6, 0);
        } else if (event.key.keysym.sym == SDLK_z) {
          std::cout << "Raytracing" << std::endl;
          window.clearPixels();
          RENDER_MODE = RayTracing; 
        } else if (event.key.keysym.sym == SDLK_w) {
          RENDER_MODE = Wireframe; 
        } else if (event.key.keysym.sym == SDLK_r) {
          RENDER_MODE = Rasterize; 
        } else if (event.key.keysym.sym == SDLK_m) {
          camera.translate(0, 0, -0.6);
        } else if (event.key.keysym.sym == SDLK_n) {
          camera.translate(0, 0, 0.6);
        } else if (event.key.keysym.sym == SDLK_a) {
          camera.rotateInPlace(-0.06, 0, 0);
        } else if (event.key.keysym.sym == SDLK_d) {
          camera.rotateInPlace(0.06, 0, 0);
        } else if (event.key.keysym.sym == SDLK_f) {
          camera.rotate(0, 0, -0.06);
        } else if (event.key.keysym.sym == SDLK_g) {
          camera.rotate(0, 0, 0.06);
        } else if (event.key.keysym.sym == SDLK_l) {
          camera.lookAt(glm::vec3(0, 0, 0));
        } else if (event.key.keysym.sym == SDLK_j) {
          camera.rotate(0, 0.06, 0);
        } else if (event.key.keysym.sym == SDLK_k) {
          camera.rotate(0.06, 0, 0);
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
		}
	}
}

int main(int argc, char *argv[]) {
	DrawingWindow window = DrawingWindow(WIDTH, HEIGHT, false);

	//Camera camera = Camera(0, 0, 80, 30);
	Camera camera = Camera(0, 0, 4, 2);

    CameraWayPoint cameraWayPoint0 = CameraWayPoint(glm::vec3(0, 2, 4), glm::vec3(0, 0, 0.4), 0);
    CameraWayPoint cameraWayPoint1 = CameraWayPoint(glm::vec3(0, 0, 6), glm::vec3(0.1, 0.1, -2), 36);

    std::vector<CameraWayPoint> wayPoints = {cameraWayPoint0, cameraWayPoint1};
    CameraTransition transition = CameraTransition(wayPoints, 0);

	SDL_Event event;

    //Light light = Light(glm::vec3(0.110042, 0.465659, 0.0556608));
    //Light light = Light(glm::vec3(0.0, 0.4, 0.05));
    //Light light = Light(glm::vec3(0, 0.45, 0), 2);
    CircularLight light = CircularLight(glm::vec3(0.0, -2.0, 1.0), 2.0, 0.22);
    std::vector<Light*> lights;
    lights.push_back(&light);

    //ObjModel model = ObjModel("assets/", "textured-cornell-box.obj", 20);
    //ObjModel model = ObjModel("assets/", "textured-cornell-box.obj", 0.17);
    ObjModel cornell = ObjModel("assets/", "textured-cornell-box.obj", 0.17);
    ObjModel sphere = ObjModel("assets/", "sphere.obj", 0.17);
    ObjModel hackSpaceLogo = ObjModel("assets/logo/", "logo.obj", 0.0005);
    hackSpaceLogo.translate(glm::vec3(0, -110, 130), 500);

    ObjModel model = cornell + sphere + hackSpaceLogo;
    //ObjModel model = cornell + sphere;
    //ObjModel model = hackSpaceLogo;
    std::cout << hackSpaceLogo.getFaces().size() << std::endl;
    //model.draw(window, camera, lights, 500);
    //model.draw(window, camera, 500);
    

	while (true) {
		// We MUST poll for events - otherwise the window will freeze !
		if (window.pollForInputEvents(event)) handleEvent(event, window, camera);
		update(window, camera, model, lights, transition);
		// Need to render the frame at the end, or nothing actually gets shown on the screen !
		window.renderFrame();
	}
}
