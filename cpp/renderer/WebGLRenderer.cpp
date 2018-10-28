#include <stdlib.h>
#include <algorithm>
#include "WebGLRenderer.h"

bool validEmscriptenResult(
	EMSCRIPTEN_RESULT result
) {
	if(result == EMSCRIPTEN_RESULT_SUCCESS)
		return 1;

	if(result == EMSCRIPTEN_RESULT_DEFERRED)
		printf("EMSCRIPTEN_RESULT_DEFERRED error\n");
	else if(result == EMSCRIPTEN_RESULT_NOT_SUPPORTED)
		printf("EMSCRIPTEN_RESULT_NOT_SUPPORTED error\n");
	else if(result == EMSCRIPTEN_RESULT_FAILED_NOT_DEFERRED)
		printf("EMSCRIPTEN_RESULT_FAILED_NOT_DEFERRED error\n");
	else if(result == EMSCRIPTEN_RESULT_INVALID_TARGET)
		printf("EMSCRIPTEN_RESULT_INVALID_TARGETT error\n");
	else if(result == EMSCRIPTEN_RESULT_UNKNOWN_TARGET)
		printf("EMSCRIPTEN_RESULT_UNKNOWN_TARGET error\n");
	else if(result == EMSCRIPTEN_RESULT_INVALID_PARAM)
		printf("EMSCRIPTEN_RESULT_INVALID_PARAM error\n");
	else if(result == EMSCRIPTEN_RESULT_FAILED)
		printf("EMSCRIPTEN_RESULT_FAILED error\n");
	else if(result == EMSCRIPTEN_RESULT_NO_DATA)
		printf("EMSCRIPTEN_RESULT_NO_DATA error\n");
	else
		printf("Unknown error\n");

	return 0;
}

GLuint loadShader(
	GLenum type,
	const char *code
) {
	GLuint shader = glCreateShader(type);

	if(shader == 0) {
		return 0;
	}

	glShaderSource(shader, 1, &code, 0);
	glCompileShader(shader);

	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if(compiled == 0) {

		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if(infoLen > 1) {
			char *infoLog = (char*)malloc(sizeof(char) * infoLen);
			glGetShaderInfoLog(shader, infoLen, 0, infoLog);
			printf("Error compiling code\n%s\n", infoLog);
			free(infoLog);
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

GLuint compileShader() {
	GLbyte vertexShaderCode[] =  
		"attribute vec3 position;\n"
		"uniform mat4 modelMatrix;\n"
		"uniform mat4 modelViewMatrix;\n"
		"uniform mat4 projectionMatrix;\n"
		"uniform mat4 viewMatrix;\n"
		"uniform mat3 normalMatrix;\n"
		"uniform vec3 cameraPosition;\n"
		"void main()\n"
		"{\n"
		"	vec4 mvPosition = modelViewMatrix * vec4(position, 1.0);"
		"	gl_Position = projectionMatrix * mvPosition;\n"
		"}\n";

	GLbyte fragmentShaderCode[] =  
		"precision mediump float;\n"
		"uniform vec3 color;\n"
		"void main()\n"
		"{\n"
		"	gl_FragColor = vec4(color, 1.0);\n"
		"}\n";

	GLuint vertexShader = loadShader(GL_VERTEX_SHADER, (char *)vertexShaderCode);
	GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, (char *)fragmentShaderCode);
	GLuint program = glCreateProgram();

	if(program == 0)
		return 0;

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glBindAttribLocation(program, 0, "position");
	glLinkProgram(program);

	printf("%d\n", glGetUniformLocation(program, "modelViewMatrix"));
	printf("%d\n", glGetUniformLocation(program, "projectionMatrix"));
	printf("%d\n", glGetUniformLocation(program, "color"));

	GLint linked;

	glGetProgramiv(program, GL_LINK_STATUS, &linked);

	if(linked == 0) {

		GLint infoLen = 0;
		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &infoLen);

		if(infoLen > 1) {
			char *infoLog = (char*)malloc(sizeof(char) * infoLen);
			glGetProgramInfoLog(program, infoLen, 0, infoLog);
			printf("Error linking program:\n%s\n", infoLog);
			free(infoLog);
		}

		glDeleteProgram(program);
		return 0;
	}

	return program;
}

WebGLRenderer::WebGLRenderer(
	char *_id
): id(_id), initialized(false) {
	printf( "Context creation for %s\n", id );

	EmscriptenWebGLContextAttributes attrs;
	attrs.explicitSwapControl = 0;
	attrs.depth = 1;
	attrs.stencil = 1;
	attrs.antialias = 1;
	attrs.majorVersion = 1;
	attrs.minorVersion = 0;
	this->context = emscripten_webgl_create_context(_id, &attrs);

	if(this->context <= 0) {
		printf("Context creation Error\n");
		validEmscriptenResult((EMSCRIPTEN_RESULT)this->context);
		return;
	}

	if (! this->activateContext()) {
		return;
	}
}

bool WebGLRenderer::activateContext() {
	return validEmscriptenResult(
		emscripten_webgl_make_context_current(this->context));
}

WebGLRenderer* WebGLRenderer::setSize(
	int _width,
	int _height
) {
	this->width = _width;
	this->height = _height;
	return this;
}

WebGLRenderer* WebGLRenderer::viewport(
	int _width,
	int _height
) {
	glViewport(0.0, 0.0, _width, _height);
	return this;
}

WebGLRenderer* WebGLRenderer::clearColor(
	double r,
	double g,
	double b,
	double a
) {
	glClearColor(r, g, b, a);
	return this;
}

WebGLRenderer* WebGLRenderer::clear() {
	glClear(GL_COLOR_BUFFER_BIT);
	return this;
}

void WebGLRenderer::projectObject(
	Object3D *object,
	Camera *camera
) {
	this->tmpVector3.setFromMatrixPosition(&object->matrixWorld)
		->applyMatrix4(&this->projScreenMatrix);
	struct RenderEntry entry;
	entry.object = object;
	entry.z = this->tmpVector3.z;
	this->currentRenderList.push_back(entry);

	for(int i = 0, il = object->children.size(); i < il; ++i) {
		this->projectObject(object->children[i], camera);
	}
}

void WebGLRenderer::renderObjects(
	std::vector<RenderEntry> *renderList,
	Camera *camera
) {
	for(int i = 0, il = renderList->size(); i < il; ++i) {
		this->renderObject((*renderList)[i].object, camera);
	}
}

void WebGLRenderer::renderObject(
	Object3D *object,
	Camera *camera
) {
	object->modelViewMatrix.multiplyMatrices(&camera->matrixWorldInverse,
		&object->matrixWorld);
	object->normalMatrix.getNormalMatrix(&object->modelViewMatrix);

	GLuint vertexPosObject;
	Vector3* color;

	if(tmpBufferMap.count(object) == 0) {
		GLfloat vertices[] = {
			// front
			-1.0, -1.0,  1.0,
			 1.0, -1.0,  1.0,
			 1.0,  1.0,  1.0,
			-1.0,  1.0,  1.0,
			// back
			-1.0, -1.0, -1.0,
			 1.0, -1.0, -1.0,
			 1.0,  1.0, -1.0,
			-1.0,  1.0, -1.0,
		};

		glGenBuffers(1, &vertexPosObject);
		tmpBufferMap[object] = vertexPosObject;
		glBindBuffer(GL_ARRAY_BUFFER, vertexPosObject);
		glBufferData(GL_ARRAY_BUFFER, 3 * 8 * 4, vertices, GL_STATIC_DRAW);
		color = new Vector3(
			std::rand() / (double)RAND_MAX,
			std::rand() / (double)RAND_MAX,
			std::rand() / (double)RAND_MAX);
		tmpColorMap[object] = color;

		GLuint indicesObject;
		GLushort indices[] = {
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3,
		};
		glGenBuffers(1, &indicesObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * 12 * 2, indices, GL_STATIC_DRAW);
		glUseProgram(this->program);
		glBindBuffer(GL_ARRAY_BUFFER, vertexPosObject);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
	} else {
		vertexPosObject = tmpBufferMap[object];
		color = tmpColorMap[object];
	}

	GLfloat modelViewMatrixElements[16];
	GLfloat projectionMatrixElements[16];
	GLfloat colorElements[3];
	for(int i = 0; i < 16; ++i) {
		modelViewMatrixElements[i] = object->modelViewMatrix.elements[i];
		projectionMatrixElements[i] = camera->projectionMatrix.elements[i];
	}
	colorElements[0] = color->x;
	colorElements[1] = color->y;
	colorElements[2] = color->z;
	glUniformMatrix4fv(5, 1, GL_FALSE, modelViewMatrixElements);
	glUniformMatrix4fv(6, 1, GL_FALSE, projectionMatrixElements);
	glUniform3fv(7, 1, colorElements);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
}

struct painterSort {
	inline bool operator() (RenderEntry entry1, RenderEntry entry2) {
		return entry1.z < entry2.z;
	}
};

WebGLRenderer* WebGLRenderer::render(
	Object3D *scene,
	Camera *camera
) {
	if(! this->initialized) {
		this->program = compileShader();
		this->initialized = true;
		this->activateContext();
		this->viewport(this->width, this->height);
		glEnable(GL_DEPTH_TEST);
		glCullFace(GL_BACK);
	}

	scene->updateMatrixWorld(false);
	if(camera->parent == NULL) camera->updateMatrixWorld(false);

	this->projScreenMatrix.multiplyMatrices(
		&camera->projectionMatrix, &camera->matrixWorldInverse);

	this->projectObject(scene, camera);
	std::sort(this->currentRenderList.begin(), this->currentRenderList.end(),
		painterSort());

	this->clear();
	this->renderObjects(&this->currentRenderList, camera);

	this->currentRenderList.clear();

	return this;
}
