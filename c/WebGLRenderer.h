#ifndef __THREE_WEBGLRENDERER_H__
#define __THREE_WEBGLRENDERER_H__

#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include "html5.h"
#include "Math.h"
#include "Object3D.h"

struct Context {
	char *id;
	int width;
	int height;
	EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;
};

struct WebGLRenderer {
	struct Context context;
	int initialized;
	GLuint program;
};

int WebGLRenderer_activateContext(
	struct WebGLRenderer *self
);

struct WebGLRenderer* WebGLRenderer_init(
	struct WebGLRenderer *self,
	char *id
);

struct WebGLRenderer* WebGLRenderer_setSize(
	struct WebGLRenderer *self,
	int width,
	int height
);

void WebGLRenderer_viewport(
	struct WebGLRenderer *self,
	int width,
	int height
);

void WebGLRenderer_clearColor(
	struct WebGLRenderer *self,
	double r,
	double g,
	double b,
	double a
);

void WebGLRenderer_clear(
	struct WebGLRenderer *self
);

void WebGLRenderer_render(
	struct WebGLRenderer *self,
	struct Object3D *scene
);

int sizeOfWebGLRenderer();

#endif
