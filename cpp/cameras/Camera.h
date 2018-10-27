#ifndef __THREE_CAMERA__
#define __THREE_CAMERA__

#include "../math/Matrix3.h"
#include "../math/Matrix4.h"
#include "../core/Object3D.h"

class Camera : public Object3D {
public:
	Matrix4 matrixWorldInverse;
	Matrix4 projectionMatrix;
	Matrix4 projectionMatrixInverse;

	Camera();

	Camera* updateMatrixWorld(bool force);
};

#endif
