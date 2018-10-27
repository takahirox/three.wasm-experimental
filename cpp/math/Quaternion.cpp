#include "Quaternion.h"

Quaternion::Quaternion()
: x(0.0), y(0.0), z(0.0), w(1.0) {
}

Quaternion::Quaternion(
	double _x,
	double _y,
	double _z,
	double _w
)
: x(_x), y(_y), z(_z), w(_w) {
}

bool Quaternion::equals(
	Quaternion *q
) {
	return this->x == q->x && this->y == q->y && this->z == q->z
		&& this->w == q->w;
}

Quaternion* Quaternion::copy(
	Quaternion *q
) {
	this->x = q->x;
	this->y = q->y;
	this->z = q->z;
	this->w = q->w;
	return this;
}
