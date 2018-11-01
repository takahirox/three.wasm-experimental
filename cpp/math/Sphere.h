#ifndef __THREE_SPHERE__
#define __THREE_SPHERE__

#include "Vector3.h"
#include "Matrix4.h"

class Sphere {
public:
	Vector3 center;
	double radius;

	Sphere();

	Sphere* copy(
		Sphere *sphere
	);

	Sphere* applyMatrix4(
		Matrix4 *matrix
	);
};

#endif
