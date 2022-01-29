#ifndef GL_HEADERS_HPP
#define GL_HEADERS_HPP

#if defined __ANDROID__
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#define GLES20 1
#else
#define GL33 1
#include <GL/glew.h>
/*#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#define __gl_h__
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>*/
#endif
#endif GL_HEADERS_HPP