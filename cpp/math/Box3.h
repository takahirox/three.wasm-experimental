#ifndef __THREE_BOX3__
#define __THREE_BOX3__

#include "Vector3.h"
#include "../core/BufferAttribute.h"

class Box3 {
public:
	Vector3 max;
	Vector3 min;

	Box3();

	bool isEmpty();

	Box3* setFromBufferAttribute(
		BufferAttribute *attribute
	);

	Vector3* getCenter(
		Vector3* target
	);
};

#endif
