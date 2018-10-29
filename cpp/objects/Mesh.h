#ifndef __THREE_MESH__
#define __THREE_MESH__

#include "../core/Object3D.h"
#include "../geometries/BufferGeometry.h"
#include "../materials/Material.h"

class Mesh : public Object3D {
public:
	BufferGeometry *geometry;
	Material *material;

	Mesh(
		BufferGeometry *_geometry,
		Material *_material
	);

	virtual ObjectType type() { return MeshType; }
};

#endif
