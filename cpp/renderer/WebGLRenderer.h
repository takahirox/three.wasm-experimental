#ifndef __THREE_WEBGLRENDERER_H__
#define __THREE_WEBGLRENDERER_H__

#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "../include/html5.h"
#include "../core/Object3D.h"

class WebGLRenderer {
private:
	bool activateContext();
	void renderObjects(Object3D *object);

public:
	char *id;
	int width;
	int height;
	bool initialized;
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;
	GLuint program;

	WebGLRenderer(char *_id);

	WebGLRenderer* setSize(
		int width,
		int height
	);

	WebGLRenderer* viewport(
		int width,
		int height
	);

	WebGLRenderer* clearColor(
		double r,
		double g,
		double b,
		double a
	);

	WebGLRenderer* clear();

	WebGLRenderer* render(
		Object3D *scene
	);
};

#endif
