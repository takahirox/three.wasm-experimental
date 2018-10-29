#ifndef __THREE_WEBGL_ATTRIBUTES__
#define __THREE_WEBGL_ATTRIBUTES__

#include <map>
#include <GLES2/gl2.h>
#include "../../core/BufferAttribute.h"

struct WebGLBufferEntry {
	GLuint buffer;
	int type;
	int bytePerElement;
	int version;
};

class WebGLAttributes {
	WebGLBufferEntry createBuffer(
		BufferAttribute* attribute,
		GLenum bufferType
	);

public:
	std::map<BufferAttribute*, WebGLBufferEntry> buffers;

	WebGLAttributes();

	void update(
		BufferAttribute* attribute,
		GLenum bufferType
	);

	WebGLBufferEntry get(
		BufferAttribute* attribute
	);
};

#endif
