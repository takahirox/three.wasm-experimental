#ifndef __THREE_PERSPECTIVE_CAMERA__
#define __THREE_PERSPECTIVE_CAMERA__

#include "Camera.h"

class PerspectiveCamera : public Camera {
public:
	double fov;
	double zoom;
	double near;
	double far;
	double focus;
	double aspect;

	PerspectiveCamera(
		double _fov,
		double _aspect,
		double _near,
		double _far
	);

	PerspectiveCamera* updateProjectionMatrix();
};

#endif