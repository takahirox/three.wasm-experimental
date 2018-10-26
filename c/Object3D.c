#include "Object3D.h"

struct Object3D* Object3D_init(
	struct Object3D *self
) {
	Vector3_init(&self->position);
	Quaternion_init(&self->quaternion);
	Vector3_init(&self->scale);
	self->scale.x = 1;
	self->scale.y = 1;
	self->scale.z = 1;
	Euler_init(&self->rotation);
#ifdef CACHED
	Vector3_copy(&self->cachedScale, &self->scale);
#endif
	Matrix4_init(&self->matrix);
	Matrix4_init(&self->matrixWorld);
	self->matrixAutoUpdate = 1;
	self->matrixWorldNeedsUpdate = 0;
	self->parent = 0;
	self->childrenNum = 0;
	LinkedListHeader_init(&self->children);
	return self;
}

struct Object3D* Object3D_add(
	struct Object3D *self,
	struct Object3D *child
) {
	LinkedListHeader_add(&self->children, child);
	self->childrenNum++;
	child->parent = self;
	return self;
}

void Object3D_updateMatrix(
	struct Object3D *self
) {
#ifdef CACHED
	if (! Vector3_equals(&self->position, &self->cachedPosition) ||
		! Quaternion_equals(&self->quaternion, &self->cachedQuaternion) ||
		! Vector3_equals(&self->scale, &self->cachedScale)) {
#endif
		Matrix4_compose(
			&self->matrix,
			&self->position,
			&self->quaternion,
			&self->scale
		);

		self->matrixWorldNeedsUpdate = 1;
#ifdef CACHED
		Vector3_copy(&self->cachedPosition, &self->position);
		Quaternion_copy(&self->cachedQuaternion, &self->quaternion);
		Vector3_copy(&self->cachedScale, &self->scale);
	}
#endif
}

void Object3D_updateMatrixWorld(
	struct Object3D *self,
	int force
) {
	if (self->matrixAutoUpdate == 1) Object3D_updateMatrix(self);

	if (self->matrixWorldNeedsUpdate == 1 || force == 1) {
		if (self->parent == 0) {
			Matrix4_copy(&self->matrixWorld, &self->matrix);
		} else {
			Matrix4_multiplyMatrices(
				&self->matrixWorld,
				&self->parent->matrixWorld,
				&self->matrix
			);
		}

		self->matrixWorldNeedsUpdate = 0;
		force = 1;
	}

	int childrenNum = self->childrenNum;

	struct LinkedList *node = self->children.head;

	while (node != 0) {
		Object3D_updateMatrixWorld(node->value, force);
		node = node->next;
	}
}

int sizeOfObject3D() {
	return sizeof(struct Object3D);
}
