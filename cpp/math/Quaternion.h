#ifndef __THREE_QUATERNION__
#define __THREE_QUATERNION__

class Quaternion {
public:
	double x;
	double y;
	double z;
	double w;

	Quaternion();
	Quaternion(double _x, double _y, double _z, double _w);

	bool equals(
		Quaternion *q
	);

	Quaternion* copy(
		Quaternion *q
	);
};

#endif
