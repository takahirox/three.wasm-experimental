#include "Box3.h"

Box3::Box3() {}

bool Box3::isEmpty() {
	return (this->max.x < this->min.x) ||
		(this->max.y < this->min.y) ||
		(this->max.z < this->min.z);
}

Box3* Box3::setFromBufferAttribute(
	BufferAttribute *attribute
) {
	double largeValue = 1000000.0; // Fix me
	double minX = largeValue;
	double minY = largeValue;
	double minZ = largeValue;

	double maxX = -largeValue;
	double maxY = -largeValue;
	double maxZ = -largeValue;

	for(int i = 0, il = attribute->count; i < il; ++i) {
		double x = (double)attribute->getXAsFloat(i);
		double y = (double)attribute->getYAsFloat(i);
		double z = (double)attribute->getZAsFloat(i);

		if(x < minX) minX = x;
		if(y < minY) minY = y;
		if(z < minZ) minZ = z;

		if(x > maxX) maxX = x;
		if(y > maxY) maxY = y;
		if(z > maxZ) maxZ = z;
	}

	this->min.set(minX, minY, minZ);
	this->max.set(maxX, maxY, maxZ);

	return this;
}

Vector3* Box3::getCenter(
	Vector3* target
) {
	return this->isEmpty()
		? target->set(0.0, 0.0, 0.0)
		: target->addVectors(&this->min, &this->max)->multiplyScalar(0.5);
}
