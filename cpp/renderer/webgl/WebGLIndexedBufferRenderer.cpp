#include "WebGLIndexedBufferRenderer.h"

WebGLIndexedBufferRenderer::WebGLIndexedBufferRenderer() {}

WebGLIndexedBufferRenderer* WebGLIndexedBufferRenderer::setIndex(
	BufferAttribute* index
) {
	this->type = index->dataType;
	return this;
}

WebGLIndexedBufferRenderer* WebGLIndexedBufferRenderer::render(
	int start,
	int count
) {
	glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_SHORT, 0);
	return this;
}
