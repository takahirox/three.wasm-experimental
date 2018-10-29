#include "MeshBasicMaterial.h"

MeshBasicMaterial::MeshBasicMaterial() {
	this->color.set(0.0, 0.0, 0.0);
}

MeshBasicMaterial::MeshBasicMaterial(
	Vector3 *_color
) {
	this->color.copy(_color);
}
