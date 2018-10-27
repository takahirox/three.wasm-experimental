#include "Matrix3.h"

Matrix3::Matrix3() {
	this->elements[0] = 1.0;
	this->elements[1] = 0.0;
	this->elements[2] = 0.0;
	this->elements[3] = 0.0;
	this->elements[4] = 1.0;
	this->elements[5] = 0.0;
	this->elements[6] = 0.0;
	this->elements[7] = 0.0;
	this->elements[8] = 1.0;
}

Matrix3* Matrix3::setFromMatrix4(
	struct Matrix4 *m
) {
	this->elements[0] = m->elements[0];
	this->elements[1] = m->elements[1];
	this->elements[2] = m->elements[2];
	this->elements[3] = m->elements[4];
	this->elements[4] = m->elements[5];
	this->elements[5] = m->elements[6];
	this->elements[6] = m->elements[8];
	this->elements[7] = m->elements[9];
	this->elements[8] = m->elements[10];
	return this;
}

Matrix3* Matrix3::getInverse(
	struct Matrix3 *matrix
) {
	double n11 = matrix->elements[0];
	double n21 = matrix->elements[1];
	double n31 = matrix->elements[2];
	double n12 = matrix->elements[3];
	double n22 = matrix->elements[4];
	double n32 = matrix->elements[5];
	double n13 = matrix->elements[6];
	double n23 = matrix->elements[7];
	double n33 = matrix->elements[8];
	double t11 = n33 * n22 - n32 * n23;
	double t12 = n32 * n13 - n33 * n12;
	double t13 = n23 * n12 - n22 * n13;
	double det = n11 * t11 + n21 * t12 + n31 * t13;

	if (det == 0.0) {
		// TODO: Error handling
		return this;
	}

	double detInv = 1.0 / det;
	this->elements[0] = t11 * detInv;
	this->elements[1] = (n31 * n23 - n33 * n21) * detInv;
	this->elements[2] = (n32 * n21 - n31 * n22) * detInv;
	this->elements[3] = t12 * detInv;
	this->elements[4] = (n33 * n11 - n31 * n13) * detInv;
	this->elements[5] = (n31 * n12 - n32 * n11) * detInv;
	this->elements[6] = t13 * detInv;
	this->elements[7] = (n21 * n13 - n23 * n11) * detInv;
	this->elements[8] = (n22 * n11 - n21 * n12) * detInv;

	return this;
}

Matrix3* Matrix3::transpose(){
	double tmp;
	tmp = this->elements[1];
	this->elements[1] = this->elements[3];
	this->elements[3] = tmp;
	tmp = this->elements[2];
	this->elements[2] = this->elements[6];
	this->elements[6] = tmp;
	tmp = this->elements[5];
	this->elements[5] = this->elements[7];
	this->elements[7] = tmp;
	return this;
}

Matrix3* Matrix3::getNormalMatrix(
	struct Matrix4 *matrix4
) {
	this->setFromMatrix4(matrix4);
	this->getInverse(this);
	this->transpose();
	return this;
}
