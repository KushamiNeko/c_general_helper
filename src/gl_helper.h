#ifndef GL_HELPER_H
#define GL_HELPER_H

#define GL_HELPER_VIEWPORT_SIZE 2

// #include <glib-2.0/glib.h>

#include <GL/glew.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <stb_image.h>

#include "general_helper.h"

#ifdef DEBUG

void programLinkCheck(GLuint program);

void shaderCompileCheck(GLuint shader);

#define LINK_GL_SHADER_PROGRAM(expr) programLinkCheck(expr)
#define COMPILE_GL_SHADER(expr) shaderCompileCheck(expr)

#else

#define LINK_GL_SHADER_PROGRAM(expr) glLinkProgram(expr)
#define COMPILE_GL_SHADER(expr) glCompileShader(expr)
#endif

#endif

GLuint generateVBO(const GLuint *vao, const int point_count,
                   const int vector_size, const GLfloat *data_array,
                   const int loc);

void setVBOData(const GLuint *vbo, const int point_count, const int vector_size,
                const GLfloat *dataArray);

void generateShader(const GLuint *shader_program, const char *shader_file,
                    const GLenum shader_type);

bool loadTexture(const char *textureFile, GLuint *shaderProgram,
                 GLenum textureSlot, GLuint *tex, GLint *texLoc);

bool createCubeMap(const char *front, const char *back, const char *top,
                   const char *bottom, const char *right, const char *left,
                   GLuint *shaderProgram, GLenum textureSlot, GLuint *cubeTex,
                   GLint *cubeTexLoc);

GLuint generateGLTexture();

GLint generateTexLoc(GLuint *shaderProgram, const char *textureName);
