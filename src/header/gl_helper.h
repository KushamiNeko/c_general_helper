#ifndef GL_HELPER_H
#define GL_HELPER_H

#define __GL_DEBUG 1
#define __GL_VIEWPORT 2

#include <GL/glew.h>

//#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include <stb_image.h>

extern GLuint generateVBO(const GLuint *vao, const int point_count,
                          const int vector_size, const GLfloat *data_array,
                          const int loc);

extern void setVBOData(const GLuint *vbo, const int point_count,
                       const int vector_size, const GLfloat *dataArray);

extern char *readShader(const char *file);

extern void generateShader(const GLuint *shader_program,
                           const char *shader_file, const GLenum shader_type);

// int loadTexture(const char *textureFile, GLuint *shaderProgram,
//                 GLenum textureSlot, const char *textureName);

extern int loadTexture(const char *textureFile, GLuint *shaderProgram,
                       GLenum textureSlot, GLuint *tex, GLint *texLoc);

extern GLuint generateGLTexture();

extern GLint generateTexLoc(GLuint *shaderProgram, const char *textureName);

// extern void bindGLTexture(unsigned char *imageData, int width, int height,
//                           GLenum textureSlot, GLuint tex);

extern void bindToTexLoc(GLuint texLoc, GLenum textureSlot,
                         GLuint *shaderProgram);

#if __GL_DEBUG
extern void programLinkCheck(GLuint program);

extern void shaderCompileCheck(GLuint shader);

#define __LinkProgram(expr) programLinkCheck(expr)
#define __CompileShader(expr) shaderCompileCheck(expr)
#else
#define __LinkProgram(expr) glLinkProgram(expr)
#define __CompileShader(expr) glCompileShader(expr)
#endif

#endif
