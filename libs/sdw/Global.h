#pragma once
#include "Colour.h"

// Lighitng
extern float SPECULAR_LIGTHING_FACTOR;
extern float INCIDENT_LIGTHING_FACTOR;
extern float PROXIMITY_LIGTHING_FACTOR;
extern float AMBIENT_LIGTHING_FACTOR;

extern float LIGHT_RESOLUTION;
extern bool SOFT_SHADOWS;

// Reflections 
extern int MAX_REFLECTIONS;
extern float SHADOW_BIAS;
extern float LIGHT_REFLECTIVITY;

// Defaults 
extern Colour DEFAULT_COLOUR;

// Rending mode
enum RenderMode {Wireframe, Rasterize, RayTracing};
extern RenderMode RENDER_MODE;

// Settings
extern bool LOADING_BAR_ENABLED;
extern bool PERSPECTIVE_CORRECTION_TEXTURING;
extern bool RECORDING;

// Shading mode
enum ShadingMode {Gouraud, Phong, None};
extern ShadingMode SHADING_MODE;
