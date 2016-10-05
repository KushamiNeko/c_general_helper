#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include <GL/glew.h>

#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "general_helper.h"
#include "linear_math.h"

#include "debug_macro.h"

//#ifdef DEBUG
//#include <glib-2.0/glib/gstdio.h>
//#endif

struct Obj {
  int point_counts;
  float *vp;
  float *vn;
  float *vt;
  float *vtan;
};

struct Obj *objLoad(const char *fileName);
void objFree(struct Obj *model);

#endif
