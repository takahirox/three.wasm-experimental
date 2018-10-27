#include <stdlib.h>
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
		"attribute vec4 position;\n"
		"uniform mat4 modelMatrix;\n"
		"uniform mat4 modelViewMatrix;\n"
		"uniform mat4 projectionMatrix;\n"
		"uniform mat4 viewMatrix;\n"
		"uniform mat3 normalMatrix;\n"
		"uniform vec3 cameraPosition;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = modelMatrix * position;\n"
		"}\n";

	GLbyte fragmentShaderCode[] =  
		"precision mediump float;\n"\
		"void main()\n"
		"{\n"
		"	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
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

	printf("%d\n", glGetUniformLocation(program, "modelMatrix"));

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

void WebGLRenderer::renderObjects(
	Object3D *object
) {
	GLfloat vertices[] = {
		 0.0,  0.5,  0.0,
		-0.5, -0.5,  0.0,
		 0.5, -0.5,  0.0
	};

	GLuint vertexPosObject;
	glGenBuffers(1, &vertexPosObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexPosObject);
	glBufferData(GL_ARRAY_BUFFER, 9 * 4, vertices, GL_STATIC_DRAW);
	glUseProgram(this->program);
	glBindBuffer(GL_ARRAY_BUFFER, vertexPosObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
	glEnableVertexAttribArray(0);

	GLfloat elements[16];
	for(int i = 0; i < 16; i++)
		elements[i] = object->matrix.elements[i];
	glUniformMatrix4fv(5, 1, GL_FALSE, elements);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

WebGLRenderer* WebGLRenderer::render(
	Object3D *scene
) {
	if(! this->initialized) {
		this->program = compileShader();
		this->initialized = true;
	}

	scene->updateMatrixWorld(false);

	this->activateContext();
	this->viewport(this->width, this->height);
	this->clear();
	this->renderObjects(scene);

	return this;
}
