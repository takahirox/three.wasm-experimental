#include "Sphere.h"

Sphere::Sphere() : radius(0.0) {
}

Sphere* Sphere::copy(
	Sphere *sphere
) {
	this->center.copy(&sphere->center);
	this->radius = sphere->radius;
	return this;
}

Sphere* Sphere::applyMatrix4(
	Matrix4 *matrix
) {
	this->center.applyMatrix4(matrix);
	this->radius = this->radius * matrix->getMaxScaleOnAxis();
	return this;
}
