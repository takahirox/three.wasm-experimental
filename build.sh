#/bin/bash

emcc -O2 -o ./WebGLRenderer.js ./c/*.c --memory-init-file 0 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS="['_sizeOfObject3D', '_Object3D_init', '_sizeOfWebGLRenderer', '_WebGLRenderer_init', '_WebGLRenderer_setSize', '_WebGLRenderer_clearColor', '_WebGLRenderer_render']" -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap', 'stringToUTF8']"
