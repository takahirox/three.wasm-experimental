#ifndef __THREE_WEBGLRENDERER_H__
#define __THREE_WEBGLRENDERER_H__

#include <stdio.h>
#include <stdlib.h>
#include <GLES2/gl2.h>
#include <vector>
#include <map>
#include "../include/html5.h"
#include "../math/Matrix4.h"
#include "../math/Frustum.h"
#include "../core/Object3D.h"
#include "../materials/Materials.h"
#include "../objects/Mesh.h"
#include "../scenes/Scene.h"
#include "../cameras/Camera.h"
#include "./webgl/WebGLAttributes.h"
#include "./webgl/WebGLGeometries.h"
#include "./webgl/WebGLIndexedBufferRenderer.h"

struct RenderItem {
	Object3D* object;
	double z;
};

class WebGLRenderer {
private:
	Matrix4 projScreenMatrix;
	std::vector<RenderItem> currentRenderList;
	WebGLAttributes *attributes;
	WebGLGeometries *geometries;
	WebGLIndexedBufferRenderer renderer;
	BufferGeometry *currentGeometry;
	GLuint program;
	GLuint currentProgram;
	Camera *currentCamera;
	Frustum frustum;
	Vector3 tmpVector3;
	std::map<std::string, int> uniformLocationMap;

	bool activateContext();

	GLuint compileShader();

	void projectObject(
		Object3D *object,
		Camera *camera
	);

	void renderObjects(
		std::vector<RenderItem> *renderList,
		Scene *scene,
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

	WebGLRenderer(
		char *_id,
		bool antialias
	);

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
		Scene *scene,
		Camera *camera
	);
};

#endif
