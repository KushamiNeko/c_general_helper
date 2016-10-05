#include "obj_parser.h"

struct Obj *objLoad(const char *fileName) {
  // REQUIRE(g_file_test(fileName, G_FILE_TEST_EXISTS));
  REQUIRE(fileExist(fileName));

  const struct aiScene *scene = aiImportFile(
      fileName, aiProcess_Triangulate | aiProcess_CalcTangentSpace);

  if (!scene) {
    // printf("ERROR on reading mesh: %s\n", file_name);
    DEBUG_MESSAGE("ERROR on reading mesh: %s\n", fileName);
    return NULL;
  }

  ENSURE(scene != NULL);

  const struct aiMesh *mesh = scene->mMeshes[0];
  // printf("vertices in mesh: %i\n", mesh->mNumVertices);
  DEBUG_MESSAGE("vertices in mesh: %i\n", mesh->mNumVertices);

  // obj *model = (obj *)malloc(sizeof(obj));
  struct Obj *model =
      (struct Obj *)DEFENSE_MALLOC(sizeof(struct Obj), mallocFailAbort, NULL);
  model->point_counts = mesh->mNumVertices;

  ENSURE(model != NULL);

  // float *vp = (float *)malloc(sizeof(float) * model->point_counts * 3);
  // float *vn = (float *)malloc(sizeof(float) * model->point_counts * 3);
  // float *vt = (float *)malloc(sizeof(float) * model->point_counts * 2);
  // float *vtan = (float *)malloc(sizeof(float) * model->point_counts * 4);

  float *vp = (float *)DEFENSE_MALLOC(sizeof(float) * model->point_counts * 3,
                                      mallocFailAbort, NULL);
  float *vn = (float *)DEFENSE_MALLOC(sizeof(float) * model->point_counts * 3,
                                      mallocFailAbort, NULL);
  float *vt = (float *)DEFENSE_MALLOC(sizeof(float) * model->point_counts * 2,
                                      mallocFailAbort, NULL);
  float *vtan = (float *)DEFENSE_MALLOC(sizeof(float) * model->point_counts * 4,
                                        mallocFailAbort, NULL);

  ENSURE(vp != NULL);
  ENSURE(vn != NULL);
  ENSURE(vt != NULL);
  ENSURE(vtan != NULL);

  for (int i = 0; i < model->point_counts; i++) {
    const struct aiVector3D *vpos = &(mesh->mVertices[i]);
    vp[i * 3] = (GLfloat)vpos->x;
    vp[i * 3 + 1] = (GLfloat)vpos->y;
    vp[i * 3 + 2] = (GLfloat)vpos->z;

    const struct aiVector3D *vnor = &(mesh->mNormals[i]);
    vn[i * 3] = (GLfloat)vnor->x;
    vn[i * 3 + 1] = (GLfloat)vnor->y;
    vn[i * 3 + 2] = (GLfloat)vnor->z;

    // extract tangent and bitangent information from assimp
    const struct aiVector3D *tangent = &(mesh->mTangents[i]);
    const struct aiVector3D *bitangent = &(mesh->mBitangents[i]);

    vec3 t =
        vec3New((GLfloat)tangent->x, (GLfloat)tangent->y, (GLfloat)tangent->z);

    vec3 n = vec3New((GLfloat)vnor->x, (GLfloat)vnor->y, (GLfloat)vnor->z);

    vec3 b = vec3New((GLfloat)bitangent->x, (GLfloat)bitangent->y,
                     (GLfloat)bitangent->z);

    ENSURE(t != NULL);
    ENSURE(n != NULL);
    ENSURE(b != NULL);

    // orthogonalize and normalize the tangent
    // approximating a T, N, B inverse matrix

    vec3 nMnDotT = vec3MultFloat(n, vec3Dot(n, t));
    vec3 tSubnMDotT = vec3Sub(t, nMnDotT);

    ENSURE(nMnDotT != NULL);
    ENSURE(tSubnMDotT != NULL);

    vec3 tI = vec3Normalize(tSubnMDotT);

    ENSURE(tI != NULL);

    vecFree(nMnDotT);
    vecFree(tSubnMDotT);

    // vec3 t_i = vec3Normalize(vec3Sub(t, vec3MultFloat(n, vec3Dot(n, t))));
    // get determinant of T, B, N 3x3 matrix by dot * cross
    // this is a short-cut calculation
    // we can build a mat3 by using 3 vectors and get the determinant instead

    vec3 nCt = vec3Cross(n, t);

    ENSURE(nCt != NULL);

    // double det = (vec3Dot(vec3Cross(n, t), b));
    double det = vec3Dot(nCt, b);

    vecFree(nCt);

    if (det < 0.0f) {
      det = -1.0f;
    } else {
      det = 1.0f;
    }

    vtan[i * 4] = vec3GetData(tI)[0];
    vtan[i * 4 + 1] = vec3GetData(tI)[1];
    vtan[i * 4 + 2] = vec3GetData(tI)[2];
    vtan[i * 4 + 3] = det;

    // vtan[i * 4] = t_i[0];
    // vtan[i * 4 + 1] = t_i[1];
    // vtan[i * 4 + 2] = t_i[2];
    // vtan[i * 4 + 3] = det;

    vecFree(t);
    vecFree(n);
    vecFree(b);
    vecFree(tI);

    const struct aiVector3D *vst = &(mesh->mTextureCoords[0][i]);
    vt[i * 2] = (GLfloat)vst->x;
    vt[i * 2 + 1] = (GLfloat)vst->y;
  }

  model->vp = vp;
  model->vn = vn;
  model->vt = vt;
  model->vtan = vtan;

  aiReleaseImport(scene);

  return model;
}

void objFree(struct Obj *model) {
  REQUIRE(model != NULL);

  free(model->vp);
  free(model->vt);
  free(model->vn);
  free(model);

  model = NULL;
}
