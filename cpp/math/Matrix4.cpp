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

Matrix4* Matrix4::getInverse(
	Matrix4 *m
) {
	double n11 = m->elements[0];
	double n21 = m->elements[1];
	double n31 = m->elements[2];
	double n41 = m->elements[3];
	double n12 = m->elements[4];
	double n22 = m->elements[5];
	double n32 = m->elements[6];
	double n42 = m->elements[7];
	double n13 = m->elements[8];
	double n23 = m->elements[9];
	double n33 = m->elements[10];
	double n43 = m->elements[11];
	double n14 = m->elements[12];
	double n24 = m->elements[13];
	double n34 = m->elements[14];
	double n44 = m->elements[15];

	double t11 = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44;
	double t12 = n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44;
	double t13 = n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44;
	double t14 = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34;

	double det = n11 * t11 + n21 * t12 + n31 * t13 + n41 * t14;

	if ( det == 0.0 ) {

		// TODO: Error handling
		return this;

	}

	double detInv = 1.0 / det;

	this->elements[0] = t11 * detInv;
	this->elements[1] = ( n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44 ) * detInv;
	this->elements[2] = ( n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44 ) * detInv;
	this->elements[3] = ( n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43 ) * detInv;

	this->elements[4] = t12 * detInv;
	this->elements[5] = ( n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44 ) * detInv;
	this->elements[6] = ( n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44 ) * detInv;
	this->elements[7] = ( n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43 ) * detInv;

	this->elements[8] = t13 * detInv;
	this->elements[9] = ( n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44 ) * detInv;
	this->elements[10] = ( n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44 ) * detInv;
	this->elements[11] = ( n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43 ) * detInv;

	this->elements[12] = t14 * detInv;
	this->elements[13] = ( n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34 ) * detInv;
	this->elements[14] = ( n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34 ) * detInv;
	this->elements[15] = ( n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33 ) * detInv;

	return this;
}

Matrix4* Matrix4::makePerspective(
	double left,
	double right,
	double top,
	double bottom,
	double near,
	double far
) {
	double x = 2.0 * near / ( right - left );
	double y = 2.0 * near / ( top - bottom );

	double a = ( right + left ) / ( right - left );
	double b = ( top + bottom ) / ( top - bottom );
	double c = - ( far + near ) / ( far - near );
	double d = - 2 * far * near / ( far - near );

	this->elements[0] = x;
	this->elements[4] = 0.0;
	this->elements[8] = a;
	this->elements[12] = 0.0;
	this->elements[1] = 0.0;
	this->elements[5] = y;
	this->elements[9] = b;
	this->elements[13] = 0.0;
	this->elements[2] = 0.0;
	this->elements[6] = 0.0;
	this->elements[10] = c;
	this->elements[14] = d;
	this->elements[3] = 0.0;
	this->elements[7] = 0.0;
	this->elements[11] = -1.0;
	this->elements[15] = 0.0;

	return this;
}
