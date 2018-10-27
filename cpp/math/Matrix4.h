#ifndef __THREE_MATRIX4__
#define __THREE_MATRIX4__

#include "Vector3.h"
#include "Quaternion.h"

class Vector3;

class Matrix4 {
public:
	double elements[16];

	Matrix4();

	Matrix4* copy(
		Matrix4 *m
	);

	Matrix4* multiplyMatrices(
		Matrix4 *a,
		Matrix4 *b
	);

	Matrix4* compose(
		Vector3 *position,
		Quaternion *quaternion,
		Vector3 *scale
	);

	Matrix4* getInverse(
		Matrix4 *m
	);

	Matrix4* makePerspective(
		double left,
		double right,
		double top,
		double bottom,
		double near,
		double far
	);
};

#endif