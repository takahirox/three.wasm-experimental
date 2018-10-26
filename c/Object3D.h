#ifndef __THREE_OBJECT3D_H__
#define __THREE_OBJECT3D_H__

#include "Math.h"

//#define CACHED

struct Object3D {
	struct Vector3 position;
	struct Quaternion quaternion;
	struct Euler rotation;
	struct Vector3 scale;
	struct Matrix4 matrix;
	struct Matrix4 matrixWorld;
	struct Matrix4 modelViewMatrix;
	struct Matrix3 normalMatrix;
	struct Matrix4 matrixWorldInverse;
	struct Matrix4 projectionMatrix;
	struct Matrix4 projectionMatrixInverse;
	int matrixAutoUpdate;
	int matrixWorldNeedsUpdate;
	struct Object3D *parent;
	int childrenNum;
	struct LinkedListHeader children;
#ifdef CACHED
	struct Vector3 cachedPosition;
	struct Quaternion cachedQuaternion;
	struct Vector3 cachedScale;
#endif
};

struct Object3D* Object3D_init(
	struct Object3D *self
);

struct Object3D* Object3D_add(
	struct Object3D *self,
	struct Object3D *child
);

void Object3D_updateMatrix(
	struct Object3D *self
);

void Object3D_updateMatrixWorld(
	struct Object3D *self,
	int force
);

int sizeOfObject3D();

#endif
