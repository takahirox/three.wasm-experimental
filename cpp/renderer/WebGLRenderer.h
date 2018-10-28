#ifndef __THREE_WEBGLRENDERER_H__
#define __THREE_WEBGLRENDERER_H__

#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <vector>
#include <map>
#include "../include/html5.h"
#include "../math/Matrix4.h"
#include "../core/Object3D.h"
#include "../cameras/Camera.h"

struct RenderEntry {
	Object3D* object;
	double z;
};

class WebGLRenderer {
private:
	Matrix4 projScreenMatrix;
	std::vector<RenderEntry> currentRenderList;

	std::map<Object3D*, GLuint> tmpBufferMap;
	std::map<Object3D*, Vector3*> tmpColorMap;
	Vector3 tmpVector3;

	bool activateContext();

	void projectObject(
		Object3D *object,
		Camera *camera
	);

	void renderObjects(
		std::vector<RenderEntry> *renderList,
		Camera *camera
	);

	void renderObject(
		Object3D *object,
		Camera *camera
	);

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
		Object3D *scene,
		Camera *camera
	);
};

#endif
