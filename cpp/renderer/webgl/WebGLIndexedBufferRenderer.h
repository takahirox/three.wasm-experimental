#ifndef __THREE_WEBGL_INDEXED_BUFFER_RENDERER__
#define __THREE_WEBGL_INDEXED_BUFFER_RENDERER__

#include <GLES2/gl2.h>
#include "../../core/BufferAttribute.h"

class WebGLIndexedBufferRenderer {
	BufferAttribute::type type;
	int bytePerElement;

public:
	WebGLIndexedBufferRenderer();

	WebGLIndexedBufferRenderer* setIndex(
		BufferAttribute* index
	);

	WebGLIndexedBufferRenderer* render(
		int start,
		int count
	);
};

#endif
