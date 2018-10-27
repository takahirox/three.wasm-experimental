#include "./core/Object3D.h"
#include "./renderer/WebGLRenderer.h"

extern "C" {
	int sizeOfObject3D() {
		return sizeof(Object3D);
	}

	int sizeOfWebGLRenderer() {
		return sizeof(WebGLRenderer);
	}

	Object3D* Object3D_init(
		Object3D *object
	) {
		return new(object) Object3D();
	}

	WebGLRenderer* WebGLRenderer_init(
		WebGLRenderer *renderer,
		char *id
	) {
		return new(renderer) WebGLRenderer(id);
	}

	WebGLRenderer* WebGLRenderer_setSize(
		WebGLRenderer *renderer,
		int width,
		int height
	) {
		return renderer->setSize(width, height);
	}

	WebGLRenderer* WebGLRenderer_clearColor(
		WebGLRenderer *renderer,
		double r,
		double g,
		double b,
		double a
	) {
		return renderer->clearColor(r, g, b, a);
	}

	WebGLRenderer* WebGLRenderer_render(
		WebGLRenderer *renderer,
		Object3D *scene
	) {
		return renderer->render(scene);
	}
}
