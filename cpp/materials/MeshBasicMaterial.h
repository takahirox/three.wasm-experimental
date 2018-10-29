#ifndef __THREE_MESH_BASIC_MATERIAL__
#define __THREE_MESH_BASIC_MATERIAL__

#include "Material.h"
#include "../math/Vector3.h"

class MeshBasicMaterial : public Material {
public:
	Vector3 color;

	MeshBasicMaterial();

	MeshBasicMaterial(
		Vector3 *_color
	);

	virtual MaterialType type() { return MeshBasicMaterialType; }
};

#endif
