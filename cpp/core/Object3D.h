#ifndef __THREE_OBJECT3D__
#define __THREE_OBJECT3D__

//#define CACHED

#include <vector>
#include "../math/Vector3.h"
#include "../math/Quaternion.h"
#include "../math/Matrix3.h"
#include "../math/Matrix4.h"

enum ObjectType {
	Object3DType,
	MeshType
};

class Object3D {
public:
	Vector3 position;
	Quaternion quaternion;
	Vector3 scale;
	Matrix4 matrix;
	Matrix4 matrixWorld;
	Matrix4 modelViewMatrix;
	Matrix3 normalMatrix;
	bool matrixAutoUpdate;
	bool matrixWorldNeedsUpdate;
	Object3D *parent;
	std::vector<Object3D*> children;
#ifdef CACHED
	Vector3 cachedPosition;
	Quaternion cachedQuaternion;
	Vector3 cachedScale;
#endif

	Object3D();

	virtual ObjectType type() { return Object3DType; }

	Object3D* add(
		Object3D *child
	);

	Object3D* updateMatrix();

	virtual Object3D* updateMatrixWorld(
		bool force
	);
};

#endif
