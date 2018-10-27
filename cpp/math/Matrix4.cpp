#include "Matrix4.h"

Matrix4::Matrix4() {
	this->elements[0] = 1.0;
	this->elements[1] = 0.0;
	this->elements[2] = 0.0;
	this->elements[3] = 0.0;
	this->elements[4] = 0.0;
	this->elements[5] = 1.0;
	this->elements[6] = 0.0;
	this->elements[7] = 0.0;
	this->elements[8] = 0.0;
	this->elements[9] = 0.0;
	this->elements[10] = 1.0;
	this->elements[11] = 0.0;
	this->elements[12] = 0.0;
	this->elements[13] = 0.0;
	this->elements[14] = 0.0;
	this->elements[15] = 1.0;
}

Matrix4* Matrix4::copy(
	Matrix4 *m
) {
	this->elements[0] = m->elements[0];
	this->elements[1] = m->elements[1];
	this->elements[2] = m->elements[2];
	this->elements[3] = m->elements[3];
	this->elements[4] = m->elements[4];
	this->elements[5] = m->elements[5];
	this->elements[6] = m->elements[6];
	this->elements[7] = m->elements[7];
	this->elements[8] = m->elements[8];
	this->elements[9] = m->elements[9];
	this->elements[10] = m->elements[10];
	this->elements[11] = m->elements[11];
	this->elements[12] = m->elements[12];
	this->elements[13] = m->elements[13];
	this->elements[14] = m->elements[14];
	this->elements[15] = m->elements[15];
	return this;
}

Matrix4* Matrix4::multiplyMatrices(
	struct Matrix4 *a,
	struct Matrix4 *b
) {
	double a11 = a->elements[0];
	double a12 = a->elements[4];
	double a13 = a->elements[8];
	double a14 = a->elements[12];
	double a21 = a->elements[1];
	double a22 = a->elements[5];
	double a23 = a->elements[9];
	double a24 = a->elements[13];
	double a31 = a->elements[2];
	double a32 = a->elements[6];
	double a33 = a->elements[10];
	double a34 = a->elements[14];
	double a41 = a->elements[3];
	double a42 = a->elements[7];
	double a43 = a->elements[11];
	double a44 = a->elements[15];

	double b11 = b->elements[0];
	double b12 = b->elements[4];
	double b13 = b->elements[8];
	double b14 = b->elements[12];
	double b21 = b->elements[1];
	double b22 = b->elements[5];
	double b23 = b->elements[9];
	double b24 = b->elements[13];
	double b31 = b->elements[2];
	double b32 = b->elements[6];
	double b33 = b->elements[10];
	double b34 = b->elements[14];
	double b41 = b->elements[3];
	double b42 = b->elements[7];
	double b43 = b->elements[11];
	double b44 = b->elements[15];

	this->elements[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
	this->elements[4] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
	this->elements[8] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
	this->elements[12] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

	this->elements[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
	this->elements[5] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
	this->elements[9] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
	this->elements[13] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

	this->elements[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
	this->elements[6] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
	this->elements[10] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
	this->elements[14] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

	this->elements[3] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
	this->elements[7] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
	this->elements[11] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
	this->elements[15] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

	return this;
}

Matrix4* Matrix4::compose(
	struct Vector3 *position,
	struct Quaternion *quaternion,
	struct Vector3 *scale
) {
	double x = quaternion->x;
	double y = quaternion->y;
	double z = quaternion->z;
	double w = quaternion->w;

	double x2 = x + x;
	double y2 = y + y;
	double z2 = z + z;

	double xx = x * x2;
	double xy = x * y2;
	double xz = x * z2;

	double yy = y * y2;
	double yz = y * z2;
	double zz = z * z2;

	double wx = w * x2;
	double wy = w * y2;
	double wz = w * z2;

	double sx = scale->x;
	double sy = scale->y;
	double sz = scale->z;

	this->elements[0] = (1.0 - (yy + zz)) * sx;
	this->elements[1] = (xy + wz) * sx;
	this->elements[2] = (xz - wy) * sx;
	this->elements[3] = 0.0;

	this->elements[4] = (xy - wz) * sy;
        this->elements[5] = (1.0 - (xx + zz)) * sy;
        this->elements[6] = (yz + wx) * sy;
        this->elements[7] = 0.0;

        this->elements[8] = (xz + wy) * sz;
        this->elements[9] = (yz - wx) * sz;
        this->elements[10] = (1.0 - (xx + yy)) * sz;
        this->elements[11] = 0.0;

        this->elements[12] = position->x;
        this->elements[13] = position->y;
        this->elements[14] = position->z;
        this->elements[15] = 1.0;

	return this;
}
