#include "Colour.h"

// Lighitng
extern float SPECULAR_LIGTHING_FACTOR;
extern float INCIDENT_LIGTHING_FACTOR;
extern float PROXIMITY_LIGTHING_FACTOR;
extern float AMBIENT_LIGTHING_FACTOR;

// Reflections 
extern int MAX_REFLECTIONS;
extern float SHADOW_BIAS;

// Defaults 
extern Colour DEFAULT_COLOUR;

// Rending mode
enum RenderMode {Wireframe, Rasterize, RayTracing};
extern RenderMode RENDER_MODE;
