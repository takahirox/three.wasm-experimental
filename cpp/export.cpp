#include "./core/Object3D.h"
#include "./cameras/PerspectiveCamera.h"
#include "./renderer/WebGLRenderer.h"

extern "C" {
	int sizeOfObject3D() {
		return sizeof(Object3D);
	}

	int sizeOfPerspectiveCamera() {
		return sizeof(PerspectiveCamera);
	}

	int sizeOfWebGLRenderer() {
		return sizeof(WebGLRenderer);
	}

	Object3D* Object3D_init(
		Object3D *object
	) {
		return new(object) Object3D();
	}

	Object3D* Object3D_add(
		Object3D *object,
		Object3D *child
	) {
		return object->add(child);
	}

	PerspectiveCamera* PerspectiveCamera_init(
		PerspectiveCamera* camera,
		double fov,
		double aspect,
		double near,
		double far
	) {
		return new(camera) PerspectiveCamera(fov, aspect, near, far);
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
		Object3D *scene,
		Camera *camera
	) {
		return renderer->render(scene, camera);
	}
}
