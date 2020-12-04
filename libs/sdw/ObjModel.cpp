#include "ObjModel.h"

ObjModel::ObjModel(std::string fileLocation, std::string filename, float scalar) {
  std::vector<ModelPoint> vertices;
  std::vector<TexturePoint> texturePoints;
  std::vector<ObjMaterial> materials;

  std::ifstream infile(fileLocation + filename);
  std::string line;
  bool currentObjectIsEmpty = true;
  ObjObject currentObj;
  while (std::getline(infile, line)) {
    std::vector<std::string> tokens = split(line, ' ');
    std::string command = tokens[0];
    
    // Load in a material 
    if (tokens[0] == "mtllib") {
      std::vector<ObjMaterial> newMaterials = loadMaterials(fileLocation, tokens[1]);
      for (ObjMaterial &material : newMaterials) {
        materials.push_back(material);
      }
      
    // Save current object and start a new one 
    } else if (tokens[0] == "o") {
      if (!currentObjectIsEmpty) {
        _objects.push_back(currentObj);
      }
      currentObj = ObjObject(tokens[1]);
      currentObjectIsEmpty = false;
    
    // Set the material of the object
    } else if (tokens[0] == "usemtl") {
      std::string materialName = tokens[1];

      // Find material with the give name
      auto materialIterator = find_if(materials.begin(), materials.end(), [&materialName](ObjMaterial& material) {return material.getName() == materialName;});
      // If the material cannot be found then throw an error
      if (materialIterator == materials.end()) {
        std::runtime_error("Could not find named material");
      }
      // Otherwise set the material of the object
      currentObj.setMaterial(*materialIterator);

    // Load in vertex
    } else if (tokens[0] == "v") {
      ModelPoint newPoint = ModelPoint(std::stof(tokens[1])*scalar, std::stof(tokens[2])*scalar, std::stof(tokens[3])*scalar);
      vertices.push_back(newPoint);
    
    // Load in texture points
    } else if (tokens[0] == "vt") {
      TexturePoint newTextPoint = TexturePoint((std::stof(tokens[1]))*480, (std::stof(tokens[2]))*395);
      texturePoints.push_back(newTextPoint);
    
    // Load in a face with texture points/ material
    } else if (tokens[0] == "f") {
      std::vector<std::string> vertex0 = split(tokens[1], '/');
      std::vector<std::string> vertex1 = split(tokens[2], '/');
      std::vector<std::string> vertex2 = split(tokens[3], '/');

      ModelPoint pointA = vertices[std::stoi(vertex0[0])-1];
      ModelPoint pointB = vertices[std::stoi(vertex1[0])-1];
      ModelPoint pointC = vertices[std::stoi(vertex2[0])-1];

      // If there are texture points i.e. there is a value after the '/' then
      // set the texture points for each vertex
      if (vertex0[1] != "") {
        pointA.setTexturePoint(texturePoints[std::stoi(vertex0[1])-1]);
        pointB.setTexturePoint(texturePoints[std::stoi(vertex1[1])-1]);
        pointC.setTexturePoint(texturePoints[std::stoi(vertex2[1])-1]);
      }

      // Add the face to the current working object
      ObjMaterial currentObjMaterial = currentObj.getMaterial();
      currentObj.addFace(pointA, pointB, pointC, currentObjMaterial);
    }
  }

  // If we havae reached the end and there is a working object add that to the
  // model.
  if (!currentObjectIsEmpty) {
    _objects.push_back(currentObj);
  }
}

std::vector<ObjMaterial> loadMaterials(std::string fileLocation, std::string filename) {
  
  std::vector<ObjMaterial> materials;

  std::ifstream infile(fileLocation + filename);
  std::string line;
  bool currentMaterialIsEmpty = true;
  ObjMaterial currentMtl;

  while (std::getline(infile, line)) {
    std::vector<std::string> tokens = split(line, ' ');

    // Save working material and start on new one
    if (tokens[0] == "newmtl") {
      if (!currentMaterialIsEmpty) {
        materials.push_back(currentMtl);
      }
      currentMtl = ObjMaterial(tokens[1]);
      if(tokens[1] == "Blue") {
        currentMtl.setReflectivity(1.0);
      }
      currentMaterialIsEmpty = false;

    // Set colour value
    } else if (tokens[0] == "Kd") {
      std::vector<std::string> kdTokens = split(line, ' ');
      Colour materialColour = Colour(std::stof(kdTokens[1])*255, std::stof(kdTokens[2])*255, std::stof(kdTokens[3])*255);
      currentMtl.setColour(materialColour);

    // Set texture 
    } else if (tokens[0] == "map_Kd"){
      currentMtl.setTexture(TextureMap(fileLocation + tokens[1]));
    }
  }

  // If working material at end add that material to the list
  if (!currentMaterialIsEmpty) {
    materials.push_back(currentMtl);
  }

  return materials;
}

void ObjModel::drawRayTracing(DrawingWindow &window, Camera &camera, std::vector<Light> lights, float scalar) {
  float startRatio = (scalar - 1) / (scalar * 2);
  float endRatio = (scalar + 1) / (scalar * 2);
  float increment = 1/(scalar+1);

  for (float y = window.height * startRatio ; y < window.height * endRatio; y += increment) {
    for (float x = window.width * startRatio; x < window.width * endRatio; x += increment) {
      CanvasPoint point = CanvasPoint(x, y);
      Ray ray = Ray(point, camera, window);
      ray.setDirection(ray.direction() * camera.getOrientationMatrix());
        
      RayTriangleIntersection intersection = getClosestIntersection(ray);
      if (!intersection.isNull()) {
        CanvasPoint point2 = CanvasPoint(
            ((x - (window.width / 2)) * scalar) + (window.width / 2),
            ((y - (window.height/ 2)) * scalar) + (window.height/ 2),
            point.z() 
        );
        Colour colour = intersection.getColour(lights, *this);
        point2.setZ(-intersection.getDistanceFromOrigin());
        point2.setColour(colour);
        point2.draw(window);
      }
    }
  }
  std::cout << "Finished ray tracing" << std::endl;
}

void ObjModel::draw(DrawingWindow &window, Camera &camera, float scalar) {
  for (ObjObject object: _objects) {
    object.draw(window, camera, scalar);
  }
}

RayTriangleIntersection ObjModel::getClosestIntersection(Ray &ray) {
  std::vector<RayTriangleIntersection> intersections;
  for (ObjObject object: getObjects()) {
    RayTriangleIntersection possibleIntersection = object.getClosestIntersection(ray);
    if (!possibleIntersection.isNull()) {
      intersections.push_back(possibleIntersection);
    }
  }
  return ::getClosestIntersection(intersections);
}

std::vector<ObjObject> ObjModel::getObjects() {
  return _objects;
}

