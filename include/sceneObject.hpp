#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

enum ObjectType {
  RECT,
  CIRCLE
};

class SceneObject {
public:
  ObjectType type;
};

#endif