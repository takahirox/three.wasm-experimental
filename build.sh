#/bin/bash

emcc \
	-O2\
	-o ./three-wasm.js\
	./cpp/*.cpp ./cpp/*/*.cpp ./cpp/*/*/*.cpp \
	--memory-init-file 0\
	-s WASM=1\
	-s ALLOW_MEMORY_GROWTH=1\
	-s EXPORTED_FUNCTIONS="[\
	'_sizeOfVector3',\
	'_sizeOfMatrix4',\
	'_sizeOfBufferAttribute',\
	'_sizeOfBufferGeometry',\
	'_sizeOfObject3D',\
	'_sizeOfMesh',\
	'_sizeOfMeshBasicMaterial',\
	'_sizeOfScene',\
	'_sizeOfPerspectiveCamera',\
	'_sizeOfWebGLRenderer',\
	'_Vector3_init',\
	'_Matrix4_multiplyMatrices',\
	'_BufferAttribute_init',\
	'_BufferGeometry_init',\
	'_BufferGeometry_setIndex',\
	'_BufferGeometry_addAttribute',\
	'_Object3D_init',\
	'_Object3D_add',\
	'_Object3D_getPositionPointer',\
	'_Object3D_updateMatrixWorld',\
	'_Object3D_updateMatrixWorld2',\
	'_Mesh_init',\
	'_MeshBasicMaterial_init',\
	'_Scene_init',\
	'_PerspectiveCamera_init',\
	'_WebGLRenderer_init',\
	'_WebGLRenderer_setSize',\
	'_WebGLRenderer_clearColor',\
	'_WebGLRenderer_render',\
	'_initGl',\
	'_runTest']"\
	-s EXTRA_EXPORTED_RUNTIME_METHODS="[\
	'ccall',\
	'cwrap',\
	'stringToUTF8']"
