#include "./math/Vector3.h"
#include "./core/BufferAttribute.h"
#include "./core/Object3D.h"
#include "./geometries/BufferGeometry.h"
#include "./objects/Mesh.h"
#include "./materials/Materials.h"
#include "./scenes/Scene.h"
#include "./cameras/PerspectiveCamera.h"
#include "./renderer/WebGLRenderer.h"

// TODO: Replace with EMSCRIPTEN_BINDINGS?

extern "C" {
	int sizeOfVector3() {
		return sizeof(Vector3);
	}

	int sizeOfBufferAttribute() {
		return sizeof(BufferAttribute);
	}

	int sizeOfBufferGeometry() {
		return sizeof(BufferGeometry);
	}

	int sizeOfObject3D() {
		return sizeof(Object3D);
	}

	int sizeOfMesh() {
		return sizeof(Mesh);
	}

	int sizeOfMeshBasicMaterial() {
		return sizeof(MeshBasicMaterial);
	}

	int sizeOfPerspectiveCamera() {
		return sizeof(PerspectiveCamera);
	}

	int sizeOfWebGLRenderer() {
		return sizeof(WebGLRenderer);
	}

	int sizeOfScene() {
		return sizeof(Scene);
	}

	Vector3* Vector3_init(
		Vector3* v,
		double x,
		double y,
		double z
	) {
		return new(v) Vector3(x, y, z);
	}

	BufferAttribute* BufferAttribute_init(
		BufferAttribute *attribute,
		void *array,
		BufferAttribute::type dataType,
		int dataLength,
		int itemSize
	) {
		return new(attribute) BufferAttribute(array, dataType,
			dataLength, itemSize);
	}

	BufferGeometry* BufferGeometry_init(
		BufferGeometry *geometry
	) {
		return new(geometry) BufferGeometry();
	}

	BufferGeometry* BufferGeometry_addAttribute(
		BufferGeometry *geometry,
		char *name,
		BufferAttribute *attribute
	) {
		geometry->addAttribute(name, attribute);
		return geometry;
	}

	BufferGeometry* BufferGeometry_setIndex(
		BufferGeometry *geometry,
		BufferAttribute *attribute
	) {
		geometry->setIndex(attribute);
		return geometry;
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

	void* Object3D_getPositionPointer(
		Object3D* object
	) {
		return &object->position;
	}

	Mesh* Mesh_init(
		Mesh* mesh,
		BufferGeometry *geometry,
		Material *material
	) {
		return new(mesh) Mesh(geometry, material);
	}

	MeshBasicMaterial* MeshBasicMaterial_init(
		MeshBasicMaterial *material,
		Vector3 *color
	) {
		return new(material) MeshBasicMaterial(color);
	}

	Scene* Scene_init(
		Scene *scene
	) {
		return new(scene) Scene();
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
		Scene *scene,
		Camera *camera
	) {
		return renderer->render(scene, camera);
	}
}
