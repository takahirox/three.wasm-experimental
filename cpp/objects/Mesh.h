#ifndef __THREE_MESH__
#define __THREE_MESH__

#include "../core/Object3D.h"
#include "../geometries/BufferGeometry.h"

#include <stdio.h>

class Mesh : public Object3D {
public:
	BufferGeometry *geometry;

	Mesh(
		BufferGeometry *_geometry
	);

	virtual ObjectType type() { return MeshType; }
};

#endif
