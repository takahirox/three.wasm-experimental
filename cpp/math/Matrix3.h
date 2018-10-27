#ifndef __THREE_MATRIX3__
#define __THREE_MATRIX3__

#include "Matrix4.h"

class Matrix3 {
public:
	double elements[9];

	Matrix3();

	Matrix3* setFromMatrix4(
		Matrix4 *m
	);

	Matrix3* getInverse(
		Matrix3 *matrix
	);

	Matrix3* transpose();

	Matrix3* getNormalMatrix(
		Matrix4 *matrix4
	);
};

#endif
