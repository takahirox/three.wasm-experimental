#include <stdlib.h>
#include "WebGLRenderer.h"

int validEmscriptenResult(
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
			char *infoLog = malloc(sizeof(char) * infoLen);
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
			char *infoLog = malloc(sizeof(char) * infoLen);
			glGetProgramInfoLog(program, infoLen, 0, infoLog);
			printf("Error linking program:\n%s\n", infoLog);
			free(infoLog);
		}

		glDeleteProgram(program);
		return 0;
	}

	return program;
}

int WebGLRenderer_activateContext(
	struct WebGLRenderer *self
) {
	return validEmscriptenResult(
		emscripten_webgl_make_context_current(self->context.context)
	);
}

struct WebGLRenderer* WebGLRenderer_init(
	struct WebGLRenderer *self,
	char *id
) {
	printf( "Context creation for %s\n", id );

	self->context.id = id;
	self->initialized = 0;

	EmscriptenWebGLContextAttributes attrs;
	attrs.explicitSwapControl = 0;
	attrs.depth = 1;
	attrs.stencil = 1;
	attrs.antialias = 1;
	attrs.majorVersion = 1;
	attrs.minorVersion = 0;
	self->context.context = emscripten_webgl_create_context(id, &attrs);

	if (self->context.context <= 0) {
		printf("Context creation Error\n");
		validEmscriptenResult((EMSCRIPTEN_RESULT)self->context.context);
		return self;
	}

	if (! WebGLRenderer_activateContext(self)) {
		return self;
	}

	return self;
}

struct WebGLRenderer* WebGLRenderer_setSize(
	struct WebGLRenderer *self,
	int width,
	int height
) {
	self->context.width = width;
	self->context.height = height;
	return self;
}

void WebGLRenderer_viewport(
	struct WebGLRenderer *self,
	int width,
	int height
) {
	glViewport(0.0, 0.0, width, height);
}

void WebGLRenderer_clearColor(
	struct WebGLRenderer *self,
	double r,
	double g,
	double b,
	double a
) {
	glClearColor(r, g, b, a);
}

void WebGLRenderer_clear(
	struct WebGLRenderer *self
) {
	glClear(GL_COLOR_BUFFER_BIT);
}

void WebGLRenderer_renderObjects(
	struct WebGLRenderer *self,
	struct Object3D *object
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
	glUseProgram(self->program);
	glBindBuffer(GL_ARRAY_BUFFER, vertexPosObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
	glEnableVertexAttribArray(0);

	GLfloat elements[16];
	for(int i = 0; i < 16; i++)
		elements[i] = object->matrix.elements[i];
	glUniformMatrix4fv(5, 1, GL_FALSE, elements);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void WebGLRenderer_render(
	struct WebGLRenderer *self,
	struct Object3D *scene
) {
	if(self->initialized == 0) {
		self->program = compileShader();
		self->initialized = 1;
	}

	Object3D_updateMatrixWorld(scene, 0);

	WebGLRenderer_activateContext(self);
	WebGLRenderer_viewport(self, self->context.width, self->context.height);
	WebGLRenderer_clear(self);
	WebGLRenderer_renderObjects(self, scene);
}

int sizeOfWebGLRenderer() {
	return sizeof(struct WebGLRenderer);
}
