/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/lgpl-3.0.html.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <displays/MinVR_Dome/DomeDisplay.h>
#include <iostream>
#include <string>

namespace MinVR {

DomeDisplay::DomeDisplay() {
	// TODO Auto-generated constructor stub

}

DomeDisplay::~DomeDisplay() {
	glDeleteFramebuffers(1, &_fboId);
	glDeleteRenderbuffers(1, &_depthBufferId);
	glDeleteTextures(1, &_colorTexId);
	glDeleteProgram(_shaderProgram);
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
	glDeleteBuffers(1, &_indexVbo);
}

void DomeDisplay::init(AbstractMVRAppRef app, int threadId, WindowRef window) {
	//createTexture(window);
	createFramebuffer(app, threadId, window);
	createShader();
	createVBO();
}

void DomeDisplay::drawGraphics(AbstractMVRAppRef app, int threadId,
		AbstractCameraRef camera, WindowRef window) {

	glBindFramebuffer(GL_FRAMEBUFFER, _fboId);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	app->drawGraphics(threadId, camera, window);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _colorTexId);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(_shaderProgram);
	GLint loc = glGetUniformLocation(_shaderProgram, "tex");
	glUniform1i(loc, 0);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexVbo);

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
	glUseProgram(0);
}

void DomeDisplay::createFramebuffer(AbstractMVRAppRef app, int threadId, WindowRef window) {
	glGenFramebuffers(1, &_fboId);
	glBindFramebuffer(GL_FRAMEBUFFER, _fboId);

	createTexture(window);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorTexId, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthBufferId);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Could not create a valid framebuffer" << std::endl;
	}

	// check FBO status
	GLenum e = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	std::string message = "";
	switch (e) {
		case GL_FRAMEBUFFER_UNDEFINED:
			message = "FBO Undefined";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT :
			message = "FBO Incomplete Attachment";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT :
			message = "FBO Missing Attachment";
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER :
			message = "FBO Incomplete Draw Buffer";
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED :
			message = "FBO Unsupported";
			break;
		case GL_FRAMEBUFFER_COMPLETE:
			message = "FBO OK";
			break;
		default:
			message = "FBO Problem?";
	}

	if (e != GL_FRAMEBUFFER_COMPLETE) {
		MinVR::Logger::getInstance().assertMessage(false, message.c_str());
	}

	app->initializeContextSpecificVars(threadId, window);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DomeDisplay::createTexture(WindowRef window) {
	glGenRenderbuffers(1, &_depthBufferId);
	glGenTextures(1, &_colorTexId);

	GLubyte* tex = new GLubyte[window->getWidth()*window->getHeight()*4];
	for (int f = 0; f < window->getWidth()*window->getHeight()*4; f++)
	{
		tex[f] = 255*float(f)/float(window->getWidth()*window->getHeight()*4);
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _colorTexId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  window->getWidth(), window->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex);
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] tex;

	glBindRenderbuffer(GL_RENDERBUFFER, _depthBufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, window->getWidth(), window->getHeight());
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void DomeDisplay::createShader() {
	GLuint vertexShader, fragmentShader;
	std::string vsText, fsText;

	 // Read source code from shader files
	vsText =
	"#version 330\n"
	"layout(location = 0) in vec2 pos;\n"
	"out vec2 txcoord;\n"
	"void main() {\n"
	" gl_Position = vec4(pos,0.0,1.0);\n"
	" txcoord = pos/2+vec2(0.5);\n"
	"}\n";

	fsText =
	"#version 330\n"
	"uniform sampler2D tex;\n"
	"out vec4 FragColor;\n"
	"in vec2 txcoord;\n"
	"void main () {\n"
	//" FragColor = vec4(1,0,0,1);\n"
	" FragColor = texture2D(tex,txcoord);\n"
	//" FragColor = vec4(txcoord, 0, 1);\n"
	"}\n";

	const char *source;
	int length;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	source = vsText.c_str();
	length = vsText.size();
	glShaderSource(vertexShader, 1, &source, &length);
	glCompileShader(vertexShader);

	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) {
		GLint length;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetShaderInfoLog(vertexShader, length, &length, &log[0]);
		std::cerr << &log[0];
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	source = fsText.c_str();
	length = fsText.size();
	glShaderSource(fragmentShader, 1, &source, &length);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) {
		GLint length;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetShaderInfoLog(fragmentShader, length, &length, &log[0]);
		std::cerr << &log[0];
	}

	// create program
	_shaderProgram = glCreateProgram();
	// attach shaders
	glAttachShader(_shaderProgram, vertexShader);
	glAttachShader(_shaderProgram, fragmentShader);
	// link the program and check for errors
	glLinkProgram(_shaderProgram);

	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &status);
	if(status == GL_FALSE) {
		GLint length;
		glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> log(length);
		glGetProgramInfoLog(_shaderProgram, length, &length, &log[0]);
		std::cerr << &log[0];
	}
}

void DomeDisplay::createVBO() {
	//Setup fullscreen quad vbo
	GLfloat fullscreenVertices[8];
	GLuint fullscreenIndices[4];
	fullscreenVertices[0] = -1.0;
	fullscreenVertices[1] = -1.0;
	fullscreenVertices[2] = 1.0;
	fullscreenVertices[3] = -1.0;
	fullscreenVertices[4] = -1.0;
	fullscreenVertices[5] = 1.0;
	fullscreenVertices[6] = 1.0;
	fullscreenVertices[7] =  1.0;
	fullscreenIndices[0] = 0;
	fullscreenIndices[1] = 1;
	fullscreenIndices[2] = 2;
	fullscreenIndices[3] = 3;

	glGenVertexArrays(1, &_vao);
	glGenBuffers( 1, &_vbo);
	glBindVertexArray(_vao);

	//Create VBO
	glBindBuffer( GL_ARRAY_BUFFER, _vbo );
	glBufferData( GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), 0, GL_STATIC_DRAW );
	glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * sizeof(GLfloat), fullscreenVertices);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (char*)0 + 0*sizeof(GLfloat));

	//Create IBO
	glGenBuffers( 1, &_indexVbo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _indexVbo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), 0, GL_STATIC_DRAW );
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, 4 * sizeof(GLuint), fullscreenIndices);
}

} /* namespace MinVR */
