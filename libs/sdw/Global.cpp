#include "Global.h"

float SPECULAR_LIGTHING_FACTOR = 0.5;
float INCIDENT_LIGTHING_FACTOR = 0.3;
float PROXIMITY_LIGTHING_FACTOR = 0.3;
float AMBIENT_LIGTHING_FACTOR = 0.15;

bool SOFT_SHADOWS = false;
float LIGHT_RESOLUTION = 0.1;

int MAX_REFLECTIONS = 2;
float LIGHT_REFLECTIVITY = 0.8;

float SHADOW_BIAS = 0.0001; 

Colour DEFAULT_COLOUR = Colour(255, 0, 0);

RenderMode RENDER_MODE = Rasterize;

bool LOADING_BAR_ENABLED = true;
bool PERSPECTIVE_CORRECTION_TEXTURING = false;
bool RECORDING = true;

ShadingMode SHADING_MODE = Phong;
