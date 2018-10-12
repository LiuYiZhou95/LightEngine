#pragma once
#include <string>
#include <iostream>
#include <glew.h>
#include <glfw3.h>

static void _check_gl_error(const char *file, int line) {
	GLenum err(glGetError());

	while (err != GL_NO_ERROR) {
		std::string error;

		switch (err) {
		case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
		case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
		case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
		case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
		}

		std::cerr << "GL_" << error.c_str() << " - " << file << ":" << line << std::endl;
		err = glGetError();
	}
}

static GLenum DepthFunc[] = { GL_NEVER,GL_LESS,GL_EQUAL,GL_LEQUAL,GL_GREATER,GL_NOTEQUAL,GL_GEQUAL,GL_ALWAYS };
static GLenum StencilOp[] = { GL_KEEP,GL_ZERO,GL_REPLACE,GL_INCR,GL_INCR_WRAP,GL_DECR,GL_DECR_WRAP,GL_INVERT };


#define check_gl_error() _check_gl_error(__FILE__,__LINE__)

static GLenum openGLformat[] = { // Base Internal Formats
			GL_DEPTH_COMPONENT,
			GL_DEPTH_STENCIL,
			GL_STENCIL_INDEX,
			GL_RED,
			GL_RG,
			GL_RGB,
			GL_RGBA,

			// Sized Internal Formats
			GL_R8,
			GL_R8UI,
			GL_R8I,
			GL_R16UI,
			GL_R16I,
			GL_R32UI,
			GL_R32I,
			GL_RG8,
			GL_RG8UI,
			GL_RG8I,
			GL_RG16UI,
			GL_RG16I,
			GL_RG32UI,
			GL_RG32I,
			GL_RGB8,
			GL_RGB565,
			GL_RGBA8,
			GL_SRGB8_ALPHA8,
			GL_RGB5_A1,
			GL_RGBA4,
			GL_RGB10_A2,
			GL_RGBA8UI,
			GL_RGBA8I,
			GL_RGB10_A2UI,
			GL_RGBA16UI,
			GL_RGBA16I,
			GL_RGBA32I,
			GL_RGBA32UI,

			// Sized Depth and Stencil Internal Formats
			GL_DEPTH_COMPONENT16,
			GL_DEPTH_COMPONENT24,
			GL_DEPTH_COMPONENT32F,
			GL_DEPTH24_STENCIL8,
			GL_DEPTH32F_STENCIL8,
			GL_STENCIL_INDEX8,
			// S3TC formats
			GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
			GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
			GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, };

static GLenum openGLfactor[] = { GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA,GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA };
static GLenum openGLfunc[] = { GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX };

static GLenum openGLTexType[] = {
			GL_TEXTURE_2D,
			GL_PROXY_TEXTURE_2D,
			GL_TEXTURE_1D_ARRAY,
			GL_PROXY_TEXTURE_1D_ARRAY,
			GL_TEXTURE_RECTANGLE,
			GL_PROXY_TEXTURE_RECTANGLE,
			GL_TEXTURE_CUBE_MAP,
			GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
			GL_PROXY_TEXTURE_CUBE_MAP,
};

static GLenum openGLNumber[] = {
	GL_UNSIGNED_BYTE,
			GL_BYTE,
			GL_UNSIGNED_SHORT,
			GL_SHORT,
			GL_UNSIGNED_INT,
			GL_INT,
			GL_HALF_FLOAT,
			GL_FLOAT,
			GL_UNSIGNED_SHORT_5_6_5,
			GL_UNSIGNED_SHORT_4_4_4_4,
			GL_UNSIGNED_SHORT_5_5_5_1,
			GL_UNSIGNED_INT_2_10_10_10_REV,
			GL_UNSIGNED_INT_10F_11F_11F_REV,
			GL_UNSIGNED_INT_5_9_9_9_REV,
			GL_UNSIGNED_INT_24_8,
			GL_FLOAT_32_UNSIGNED_INT_24_8_REV,
};

static GLenum openGLWiding[] = { GL_CW, GL_CCW };
static GLenum openGLFace[] = { GL_FRONT, GL_BACK, GL_FRONT_AND_BACK };
static GLenum openGLFill[] = { GL_POINT,GL_LINE, GL_FILL };
static GLenum toOpenGLType[] = {
		GL_BYTE, GL_SHORT, GL_INT,
		GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT,
		GL_BYTE, GL_SHORT, GL_INT,
		GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT,
		GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE };

static GLboolean toOpenGLNormalized[] = {
	GL_FALSE, GL_FALSE, GL_FALSE,
	GL_TRUE, GL_FALSE, GL_FALSE,
	GL_TRUE, GL_TRUE, GL_TRUE,
	GL_TRUE, GL_TRUE, GL_TRUE,
	GL_FALSE, GL_FALSE, GL_FALSE };

static GLenum openglTexuint[] = { GL_TEXTURE0 ,GL_TEXTURE1,GL_TEXTURE2,GL_TEXTURE3 ,GL_TEXTURE4,GL_TEXTURE5,GL_TEXTURE6 ,GL_TEXTURE7,GL_TEXTURE8 };

static GLenum openglBufferUsage[] = {
	GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ,GL_DYNAMIC_COPY
};

static GLenum openglBufferAccess[] = { GL_READ_ONLY, GL_WRITE_ONLY, GL_READ_WRITE };