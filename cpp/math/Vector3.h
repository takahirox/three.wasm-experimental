#ifndef __THREE_VECTOR3__
#define __THREE_VECTOR3__

#include "Matrix4.h"

class Matrix4;

class Vector3 {
public:
	double x;
	double y;
	double z;

	Vector3();

	Vector3(
		double _x,
		double _y,
		double _z
	);

	Vector3* set(
		double _x,
		double _y,
		double _z
	);

	Vector3* copy(
		Vector3 *v
	);

	bool equals(
		Vector3 *v
	);

	Vector3* applyMatrix4(
		Matrix4 *m
	);

	Vector3* setFromMatrixPosition(
		Matrix4 *m
	);
};

#endif
