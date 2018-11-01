#include "Plane.h"

Plane::Plane() : constant(0.0) {
	this->normal.set(1.0, 0.0, 0.0);
}

Plane* Plane::setComponents(
	double x,
	double y,
	double z,
	double w
) {
	this->normal.set(x, y, z);
	this->constant = w;
	return this;
}

Plane *Plane::normalize() {
	double inverseNormalLength = 1.0 / this->normal.length();
	this->normal.multiplyScalar( inverseNormalLength );
	this->constant *= inverseNormalLength;
	return this;
}

double Plane::distanceToPoint(
	Vector3 *point
) {
	return this->normal.dot(point) + this->constant;
}
