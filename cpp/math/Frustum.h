#ifndef __THREE_FRUSTUM__
#define __THREE_FRUSTUM__

#include "Matrix4.h"
#include "Plane.h"
#include "Sphere.h"
#include "../core/Object3D.h"
#include "../objects/Mesh.h"

class Frustum {
	Sphere tmpSphere;

public:
	Plane planes[6];

	Frustum();

	Frustum* setFromMatrix(
		Matrix4 *m
	);

	bool intersectsObject(
		Object3D *object
	);

	bool intersectsSphere(
		Sphere *sphere
	);
};

#endif
