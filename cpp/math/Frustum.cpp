#include "Frustum.h"

Frustum::Frustum() {}

Frustum* Frustum::setFromMatrix(
	Matrix4* m
) {
	double me0 = m->elements[0];
	double me1 = m->elements[1];
	double me2 = m->elements[2];
	double me3 = m->elements[3];
	double me4 = m->elements[4];
	double me5 = m->elements[5];
	double me6 = m->elements[6];
	double me7 = m->elements[7];
	double me8 = m->elements[8];
	double me9 = m->elements[9];
	double me10 = m->elements[10];
	double me11 = m->elements[11];
	double me12 = m->elements[12];
	double me13 = m->elements[13];
	double me14 = m->elements[14];
	double me15 = m->elements[15];

	this->planes[0].setComponents(me3 - me0, me7 - me4, me11 - me8, me15 - me12)->normalize();
	this->planes[1].setComponents(me3 + me0, me7 + me4, me11 + me8, me15 + me12)->normalize();
	this->planes[2].setComponents(me3 + me1, me7 + me5, me11 + me9, me15 + me13)->normalize();
	this->planes[3].setComponents(me3 - me1, me7 - me5, me11 - me9, me15 - me13)->normalize();
	this->planes[4].setComponents(me3 - me2, me7 - me6, me11 - me10, me15 - me14)->normalize();
	this->planes[5].setComponents(me3 + me2, me7 + me6, me11 + me10, me15 + me14)->normalize();

	return this;
}

bool Frustum::intersectsObject(
	Object3D *object
) {
	Mesh *mesh = (Mesh*)object;
	BufferGeometry *geometry = mesh->geometry;

	if (geometry->boundingSphere == NULL) {
		geometry->computeBoundingSphere();
	}

	this->tmpSphere.copy(geometry->boundingSphere)
		->applyMatrix4(&object->matrixWorld);
	return this->intersectsSphere(&this->tmpSphere);
}

bool Frustum::intersectsSphere(
	Sphere *sphere
) {
	for(int i = 0; i < 6; ++i) {
		if(this->planes[i].distanceToPoint(&sphere->center) < - sphere->radius) {
			return false;
		}
	}
	return true;
}
