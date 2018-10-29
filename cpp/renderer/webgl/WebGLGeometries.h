#ifndef __THREE_WEBGL_GEOMETRIES__
#define __THREE_WEBGL_GEOMETRIES__

#include <GLES2/gl2.h>
#include "../../geometries/BufferGeometry.h"
#include "WebGLAttributes.h"

class WebGLGeometries {
	WebGLAttributes *attributes;
public:
	WebGLGeometries(
		WebGLAttributes *_attributes
	);

	void update(
		BufferGeometry* geometry
	);
};

#endif
