#include "DrawingWindow.h"
// On some platforms you may need to include <cstring> (if you compiler can't find memset !)

DrawingWindow::DrawingWindow() {}
DrawingWindow::DrawingWindow(int w, int h, bool fullscreen) : width(w), height(h), pixelBuffer(w*h), depthBuffer(w*h, std::numeric_limits<float>::infinity())  {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) printMessageAndQuit("Could not initialise SDL: ", SDL_GetError());
	uint32_t flags = SDL_WINDOW_OPENGL;
	if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	int ANYWHERE = SDL_WINDOWPOS_UNDEFINED;
	window = SDL_CreateWindow("COMS30020", ANYWHERE, ANYWHERE, width, height, flags);
	if (!window) printMessageAndQuit("Could not set video mode: ", SDL_GetError());
	// Set rendering to software (hardware acceleration doesn't work on all platforms)
	flags = SDL_RENDERER_SOFTWARE;
	// You could try hardware acceleration if you like - by uncommenting the below line
	// flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	renderer = SDL_CreateRenderer(window, -1, flags);
	if (!renderer) printMessageAndQuit("Could not create renderer: ", SDL_GetError());
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, width, height);
	int PIXELFORMAT = SDL_PIXELFORMAT_ARGB8888;
	texture = SDL_CreateTexture(renderer, PIXELFORMAT, SDL_TEXTUREACCESS_STATIC, width, height);
	if (!texture) printMessageAndQuit("Could not allocate texture: ", SDL_GetError());
}

void DrawingWindow::renderFrame() {
	SDL_UpdateTexture(texture, nullptr, pixelBuffer.data(), width * sizeof(uint32_t));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

void DrawingWindow::saveBMP(const std::string &filename) const {
	auto surface = SDL_CreateRGBSurfaceFrom((void *) pixelBuffer.data(), width, height, 32,
	                                        width * sizeof(uint32_t),
	                                        0xFF << 16, 0xFF << 8, 0xFF << 0, 0xFF << 24);
	SDL_SaveBMP(surface, filename.c_str());
}

void DrawingWindow::savePPM(const std::string &filename) const {
	std::ofstream outputStream(filename, std::ofstream::out);
	outputStream << "P6\n";
	outputStream << width << " " << height << "\n";
	outputStream << "255\n";

	for (size_t i = 0; i < width * height; i++) {
		std::array<char, 3> rgb {{
				static_cast<char> ((pixelBuffer[i] >> 16) & 0xFF),
				static_cast<char> ((pixelBuffer[i] >> 8) & 0xFF),
				static_cast<char> ((pixelBuffer[i] >> 0) & 0xFF)
		}};
		outputStream.write(rgb.data(), 3);
	}
	outputStream.close();
}

bool DrawingWindow::pollForInputEvents(SDL_Event &event) {
	if (SDL_PollEvent(&event)) {
		if ((event.type == SDL_QUIT) || ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))) {
			SDL_DestroyTexture(texture);
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			printMessageAndQuit("Exiting", nullptr);
		}
		SDL_Event dummy;
		// Clear the event queue by getting all available events
		// This seems like bad practice (because it will skip some events) however preventing backlog is paramount !
		while (SDL_PollEvent(&dummy));
		return true;
	}
	return false;
}

void DrawingWindow::setPixelColour(size_t x, size_t y, Colour &colour) {
	if (pixelOnScreen(x, y)) {
      pixelBuffer[(y * width) + x] = colour.pack();
	} 
}

Colour DrawingWindow::getPixelColour(size_t x, size_t y) {
	if (!pixelOnScreen(x, y)) {
		return Colour();
	} 
    return Colour(pixelBuffer[(y * width) + x]);
}

void DrawingWindow::setPixelDepth(size_t x, size_t y, float depth) {
	if (pixelOnScreen(x, y)) {
      depthBuffer[(y * width) + x] = depth;
	} 
}

float DrawingWindow::getPixelDepth(size_t x, size_t y) {
	if (!pixelOnScreen(x, y)) {
	  return -1;
	} 
    return depthBuffer[(y * width) + x];
}

void DrawingWindow::setPixel(size_t x, size_t y, float z, Colour &colour) {
	float oldDepth = getPixelDepth(x, y);
	if (z >= 0) {
	} else if (oldDepth >= 1/z) {
		setPixelColour(x, y, colour);
		setPixelDepth(x, y, 1/z);
	}
}

void DrawingWindow::clearPixels() {
	std::fill(pixelBuffer.begin(), pixelBuffer.end(), 0);
	std::fill(depthBuffer.begin(), depthBuffer.end(), std::numeric_limits<float>::infinity());
}

void printMessageAndQuit(const std::string &message, const char *error) {
	if (error == nullptr) {
		std::cout << message << std::endl;
		exit(0);
	} else {
		std::cout << message << " " << error << std::endl;
		exit(1);
	}
}

bool DrawingWindow::pixelOnScreen(size_t x, size_t y) {
  return !((x >= width) || (x < 0) || (y >= height) || (y < 0));
}
