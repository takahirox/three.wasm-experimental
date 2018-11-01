#ifndef __THREE_PLANE__
#define __THREE_PLANE__

#include "Vector3.h"

class Plane {
public:
	Vector3 normal;
	double constant;

	Plane();

	Plane* setComponents(
		double x,
		double y,
		double z,
		double w
	);

	Plane* normalize();

	double distanceToPoint(
		Vector3 *point
	);
};

#endif
