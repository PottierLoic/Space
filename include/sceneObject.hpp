#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

enum ObjectType {
  RECT,
  CIRCLE,
  TRIANGLE
};

class SceneObject {
public:
  ObjectType type;
};

#endif