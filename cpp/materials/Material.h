#ifndef __THREE_MATERIAL__
#define __THREE_MATERIAL__

enum MaterialType {
	DefaultMaterialType,
	MeshBasicMaterialType
};

class Material {
public:
	Material();

	virtual MaterialType type() { return DefaultMaterialType; }
};

#endif
