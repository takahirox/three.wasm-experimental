#include "PerspectiveCamera.h"
#include <math.h>

PerspectiveCamera::PerspectiveCamera(
	double _fov,
	double _aspect,
	double _near,
	double _far
): fov(_fov), aspect(_aspect), near(_near), far(_far), zoom(1.0) {
	this->updateProjectionMatrix();
}

PerspectiveCamera* PerspectiveCamera::updateProjectionMatrix() {
	double top = this->near * tan(M_PI / 180.0 * 0.5 * this->fov) / this->zoom;
	double height = top * 2.0;
	double width = this->aspect * height;
	double left = -0.5 * width;
	this->projectionMatrix.makePerspective(left, left + width, top,
		top - height, this->near, this->far);
	this->projectionMatrixInverse.getInverse(&this->projectionMatrix);
	return this;
}
