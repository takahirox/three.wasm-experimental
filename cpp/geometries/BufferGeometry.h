#ifndef __THREE_BUFFER_GEOMETRY__
#define __THREE_BUFFER_GEOMETRY__

#include <map>
#include <string>
#include "../core/BufferAttribute.h"

class BufferGeometry {
public:
	BufferAttribute *index;
	std::map<std::string, BufferAttribute*> attributes;

	BufferGeometry();

	BufferAttribute* getIndex();

	BufferGeometry* setIndex(
		BufferAttribute *_index
	);

	BufferGeometry* addAttribute(
		std::string name,
		BufferAttribute *attribute
	);

	BufferAttribute* getAttribute(
		std::string name
	);
};

#endif
