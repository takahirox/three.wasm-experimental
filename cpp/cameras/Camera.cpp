#include "Camera.h"

Camera::Camera() {}

Camera* Camera::updateMatrixWorld(
	bool force = false
) {
	Object3D::updateMatrixWorld(force);
	this->matrixWorldInverse.getInverse(&this->matrixWorld);
	return this;
}
