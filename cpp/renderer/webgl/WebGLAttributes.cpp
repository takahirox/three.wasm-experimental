#include "WebGLAttributes.h"

WebGLAttributes::WebGLAttributes() {}

WebGLBufferEntry WebGLAttributes::createBuffer(
	BufferAttribute* attribute,
	GLenum bufferType
) {
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(bufferType, buffer);
	glBufferData(bufferType,
		attribute->bytePerElement * attribute->itemSize * attribute->count,
		attribute->array,
		GL_STATIC_DRAW);
	WebGLBufferEntry entry;
	entry.buffer = buffer;
	entry.version = attribute->version;
	return entry;
}

void WebGLAttributes::update(
	BufferAttribute *attribute,
	GLenum bufferType
) {
	if(this->buffers.count(attribute) == 0) {
		this->buffers[attribute] = this->createBuffer(attribute, bufferType);
	}
}

WebGLBufferEntry WebGLAttributes::get(
	BufferAttribute *attribute
) {
	return this->buffers[attribute];
}
