#include "BufferGeometry.h"

BufferGeometry::BufferGeometry()
: index(NULL) {}

BufferAttribute* BufferGeometry::getIndex() {
	return this->index;
}

BufferGeometry* BufferGeometry::setIndex(
	BufferAttribute *_index
) {
	this->index = _index;
	return this;
}

BufferGeometry* BufferGeometry::addAttribute(
	std::string name,
	BufferAttribute *attribute
) {
	this->attributes[name] = attribute;
	return this;
}

BufferAttribute* BufferGeometry::getAttribute(
	std::string name
) {
	return this->attributes[name];
}
