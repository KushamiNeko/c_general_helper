#include "gl_helper.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../third_party/stb/stb_image.h"

GLuint generateVBO(const GLuint *vao, const int pointCounts,
                   const int vectorSize, const GLfloat *dataArray,
                   const int loc) {
  // generate vbo
  GLuint vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * pointCounts * vectorSize,
               dataArray, GL_STATIC_DRAW);

  // bind to the specific vao
  glBindVertexArray(*vao);
  // to modified the vertex buffer objects, we need to bind the specific vbo
  // first
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // watch out the index and the vector size
  glVertexAttribPointer(loc, vectorSize, GL_FLOAT, GL_FALSE, 0, NULL);
  // enable the requested index to be used
  glEnableVertexAttribArray(loc);

  return vbo;
}

void setVBOData(const GLuint *vbo, const int pointCounts, const int vectorSize,
                const GLfloat *dataArray) {
  glBindBuffer(GL_ARRAY_BUFFER, *vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * pointCounts * vectorSize,
               dataArray, GL_STATIC_DRAW);
}

void generateShader(const GLuint *shaderProgram, const char *shaderFile,
                    const GLenum shaderType) {
  GLuint shader;
  switch (shaderType) {
  case GL_VERTEX_SHADER: {
    shader = glCreateShader(GL_VERTEX_SHADER);
    break;
  }
  case GL_FRAGMENT_SHADER: {
    shader = glCreateShader(GL_FRAGMENT_SHADER);
    break;
  }
  }
  glShaderSource(shader, 1, &shaderFile, NULL);

  // original GL compile shader function call
  // glCompileShader(fs);

  // wrapper function with gl shader compile and error check
  __CompileShader(shader);
  glAttachShader(*shaderProgram, shader);
}

static int getTextureSlotInt(const GLenum textureSlot) {
  switch (textureSlot) {
  case GL_TEXTURE0: {
    return 0;
    break;
  }
  case GL_TEXTURE1: {
    return 1;
    break;
  }
  case GL_TEXTURE2: {
    return 2;
    break;
  }
  case GL_TEXTURE3: {
    return 3;
    break;
  }
  case GL_TEXTURE4: {
    return 4;
    break;
  }
  case GL_TEXTURE5: {
    return 5;
    break;
  }
  case GL_TEXTURE6: {
    return 6;
    break;
  }
  case GL_TEXTURE7: {
    return 7;
    break;
  }
  case GL_TEXTURE8: {
    return 8;
    break;
  }
  case GL_TEXTURE9: {
    return 9;
    break;
  }
  case GL_TEXTURE10: {
    return 10;
    break;
  }
  case GL_TEXTURE11: {
    return 11;
    break;
  }
  case GL_TEXTURE12: {
    return 12;
    break;
  }
  case GL_TEXTURE13: {
    return 13;
    break;
  }
  case GL_TEXTURE14: {
    return 14;
    break;
  }
  case GL_TEXTURE15: {
    return 15;
    break;
  }
  case GL_TEXTURE16: {
    return 16;
    break;
  }
  case GL_TEXTURE17: {
    return 17;
    break;
  }
  case GL_TEXTURE18: {
    return 18;
    break;
  }
  case GL_TEXTURE19: {
    return 19;
    break;
  }
  case GL_TEXTURE20: {
    return 20;
    break;
  }

  default: {
    return -1;
    break;
  }
  }
}

int loadTexture(const char *textureFile, GLuint *shaderProgram,
                GLenum textureSlot, GLuint *tex, GLint *texLoc) {
  int x, y, n;
  int forceChannels = 4;
  unsigned char *imageData = stbi_load(textureFile, &x, &y, &n, forceChannels);

  if (!imageData) {
    printf("ERROR: counld not load %s\n", textureFile);
    return 0;
  }

  // flip the image data upside down because OpenGL expects that the 0 on the
  // y
  // axis to be at the bottom of the texture, but the image usually have y
  // axis
  // 0 at the top

  int bytesWidth = x * 4;
  unsigned char *top = NULL;
  unsigned char *bottom = NULL;
  unsigned char temp = 0;
  int halfHeight = y / 2;

  for (int row = 0; row < halfHeight; row++) {
    top = imageData + row * bytesWidth;
    bottom = imageData + ((y - row - 1) * bytesWidth);
    for (int col = 0; col < bytesWidth; col++) {
      temp = *top;
      *top = *bottom;
      *bottom = temp;
      top++;
      bottom++;
    }
  }

  // active the first OpenGL texture slot
  glActiveTexture(textureSlot);
  int slotIndex = getTextureSlotInt(textureSlot);
  // printf("texture: %s, slot index: %d\n", textureName, slotIndex);
  glBindTexture(GL_TEXTURE_2D, *tex);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               imageData);

  // set the last argument to GL_REPEAT to enable uv wraping effects
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glActiveTexture(textureSlot);
  glUseProgram(*shaderProgram);
  glUniform1i(*texLoc, slotIndex);
  return 1;
}

GLuint generateGLTexture() {
  GLuint tex = 0;
  glGenTextures(1, &tex);

  return tex;
}

GLint generateTexLoc(GLuint *shaderProgram, const char *textureName) {
  int texLoc = glGetUniformLocation(*shaderProgram, textureName);
  return texLoc;
}

GLuint genBakingBuffer(const unsigned int renderSize) {
  GLuint fb;
  glGenFramebuffers(1, &fb);
  glBindFramebuffer(GL_FRAMEBUFFER, fb);

  GLuint colorTex;
  glGenTextures(1, &colorTex);
  glBindTexture(GL_TEXTURE_2D, colorTex);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, renderSize, renderSize, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, NULL);

  glBindFramebuffer(GL_FRAMEBUFFER, fb);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         colorTex, 0);

  GLenum drawBufs[1] = {GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1, drawBufs);

  GLenum status;
  status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

  if (status != GL_FRAMEBUFFER_COMPLETE) {
    printf("Failed to generate the framebuffer!\n");
  }

  return fb;
}

#if __GL_DEBUG
void programLinkCheck(GLuint program) {
  printf("glLinkProgram check\n");
  glLinkProgram(program);

  // error of program link check
  int params = -1;
  glGetProgramiv(program, GL_LINK_STATUS, &params);
  if (GL_TRUE != params) {
    printf("ERROR: could not link shader program with index %u\n", program);
    //_print_program_info_log(program);
    exit(1);
  }
}

void print_shader_info_log(GLuint shader) {
  int max_length = 2048;
  int actual_length = 0;
  char shader_log[2048];

  glGetShaderInfoLog(shader, max_length, &actual_length, shader_log);
  printf("shader info log for GL shader index %u: \n%s\n", shader, shader_log);
}

void shaderCompileCheck(GLuint shader) {
  printf("glCompileShader check\n");
  glCompileShader(shader);

  // check for shader compile error
  int params = -1;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
  if (GL_TRUE != params) {
    printf("ERROR: GL Shader %i did not compile\n", shader);
    // print_shader_info_log(shader);
    exit(1);
  }
}

#endif
