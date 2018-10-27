#include "Object3D.h"

Object3D::Object3D()
: matrixAutoUpdate(true), matrixWorldNeedsUpdate(false), parent(NULL) {
	this->scale.set(1.0, 1.0, 1.0);
#ifdef CACHED
	this->cachedScale.copy(&this->scale);
#endif
}

Object3D* Object3D::add(
	Object3D *child
) {
	this->children.push_back(child);
	return this;
}

Object3D* Object3D::updateMatrix() {
#ifdef CACHED
	if(! this->position.equals(&this->cachedPosition) ||
		! this->quaternion.equals(&this->cachedQuaternion) ||
		! this->scale.equals(&this->cachedScale)) {
#endif
		this->matrix.compose(&this->position, &this->quaternion, &this->scale);
		this->matrixWorldNeedsUpdate = true;
#ifdef CACHED
		this->cachedPosition.copy(&this->cachedPosition);
		this->cachedQuaternion.copy(&this->cachedQuaternion);
		this->cachedScale.copy(&this->cachedScale);
	}
#endif
	return this;
}

Object3D* Object3D::updateMatrixWorld(
	bool force = false
) {
	if(this->matrixAutoUpdate) this->updateMatrix();

	if(this->matrixWorldNeedsUpdate || force) {
		if(this->parent == NULL) {
			this->matrixWorld.copy(&this->matrix);
		} else {
			this->matrixWorld.multiplyMatrices(
				&this->parent->matrixWorld, &this->matrix);
		}
		this->matrixWorldNeedsUpdate = false;
		force = true;
	}

	for(int i = 0, il = this->children.size(); i < il; ++i) {
		this->children[i]->updateMatrixWorld(force);
	}

	return this;
}
