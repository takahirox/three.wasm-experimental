#include "WebGLGeometries.h"

WebGLGeometries::WebGLGeometries(
	WebGLAttributes *_attributes
): attributes(_attributes) {}

void WebGLGeometries::update(
	BufferGeometry *geometry
) {
	if(geometry->index != NULL) {
		this->attributes->update(geometry->index, GL_ELEMENT_ARRAY_BUFFER);
	}

	for(std::map<std::string, BufferAttribute*>::iterator it =
		geometry->attributes.begin();
		it != geometry->attributes.end(); ++it) {
		this->attributes->update(it->second, GL_ARRAY_BUFFER);
	}
}
