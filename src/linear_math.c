#include "linear_math.h"

//#include <cmockery/pbc.h>
#include "debug_macro.h"

#ifdef UNIT_TESTING
#include <cmockery/cmockery_override.h>
#endif

// #define TAU 2.0f * M_PI
// #define ONE_DEG_IN_RAD ((2.0f * M_PI) / 360.0f)  // 0.017444444
// #define ONE_RAD_IN_DEG (360.0f / (2.0f * M_PI))  // 57.2957795

#define VEC2_SIZE 2
#define VEC3_SIZE 3
#define VEC4_SIZE 4
#define MAT3_SIZE 9
#define MAT4_SIZE 16
#define VERSOR_SIZE 4

#define THRESHOLD 0.00001f

/*-----------------------------DEGUB MACRO------------------------------------*/

struct Representation {
  float *data;
  size_t size;
};

//#define REPRESENTATION(ptr) ((struct Representation *)ptr);

static void representationFree(struct Representation *re) {
  // REQUIRE(re != NULL);

  free(re->data);
  DEFENSE_FREE(re);
}

static struct Representation *representationNew(size_t dataSize) {
  REQUIRE(dataSize > 0);

  // struct Representation *re = malloc(sizeof(struct Representation));
  struct Representation *re =
      DEFENSE_MALLOC(sizeof(struct Representation), mallocFailAbort, NULL);

  // RETURN_NULL_ON_FAIL(re);
  //  if (re == NULL) {
  //    return NULL;
  //  }

  ENSURE(re != NULL);

  re->size = dataSize;
  // re->data = malloc(dataSize * sizeof(float));
  re->data = DEFENSE_MALLOC(dataSize * sizeof(float), mallocFailAbort, NULL);

  //  if (re->data == NULL) {
  //    // free(re);
  //    goto clean;
  //    return NULL;
  //  }

  ENSURE(re->data != NULL);

  return re;

  // clean:
  //  representationFree(re);
  //  return NULL;
}

#ifdef DEBUG
// inline static void vec2SizeCheck(vec2 v) {
//  struct Representation *vr = (struct Representation *)v;
//  assert(vr->size == VEC2_SIZE);
//}
//
// inline static void vec3SizeCheck(vec3 v) {
//  struct Representation *vr = (struct Representation *)v;
//  assert(vr->size == VEC3_SIZE);
//}
//
// inline static void vec4SizeCheck(vec4 v) {
//  struct Representation *vr = (struct Representation *)v;
//  assert(vr->size == VEC4_SIZE);
//}
//
// inline static void mat3SizeCheck(mat3 m) {
//  struct Representation *mr = (struct Representation *)m;
//  assert(mr->size == MAT3_SIZE);
//}
//
// inline static void mat4SizeCheck(mat4 m) {
//  struct Representation *mr = (struct Representation *)m;
//  assert(mr->size == MAT4_SIZE);
//}
//
// inline static void versorSizeCheck(versor ve) {
//  struct Representation *ver = (struct Representation *)ve;
//  assert(ver->size == VERSOR_SIZE);
//}

inline static int vec2SizeCheck(vec2 v) {
  struct Representation *vr = (struct Representation *)v;
  return (vr->size == VEC2_SIZE);
}

inline static int vec3SizeCheck(vec3 v) {
  struct Representation *vr = (struct Representation *)v;
  return (vr->size == VEC3_SIZE);
}

inline static int vec4SizeCheck(vec4 v) {
  struct Representation *vr = (struct Representation *)v;
  return (vr->size == VEC4_SIZE);
}

inline static int mat3SizeCheck(mat3 m) {
  struct Representation *mr = (struct Representation *)m;
  return (mr->size == MAT3_SIZE);
}

inline static int mat4SizeCheck(mat4 m) {
  struct Representation *mr = (struct Representation *)m;
  return (mr->size == MAT4_SIZE);
}

inline static int versorSizeCheck(versor ve) {
  struct Representation *ver = (struct Representation *)ve;
  return (ver->size == VERSOR_SIZE);
}

//#define __vec2_size_check(expr) vec2SizeCheck(expr)
//#define __vec3_size_check(expr) vec3SizeCheck(expr)
//#define __vec4_size_check(expr) vec4SizeCheck(expr)
//#define __mat3_size_check(expr) mat3SizeCheck(expr)
//#define __mat4_size_check(expr) mat4SizeCheck(expr)
//#define __versor_size_check(expr) versorSizeCheck(expr)
//
//#define __assert_ptr(expr) assert(expr)

//#else

//#define __vec2_size_check(expr) NULL
//#define __vec3_size_check(expr) NULL
//#define __vec4_size_check(expr) NULL
//#define __mat3_size_check(expr) NULL
//#define __mat4_size_check(expr) NULL
//#define __versor_size_check(expr) NULL
//
//#define __assert_ptr(expr) NULL

#endif

/*-----------------------------PRINT FUNCTIONS--------------------------------*/

void printVec2(vec2 v) {
  REQUIRE(vec2SizeCheck(v));

  struct Representation *vr = (struct Representation *)v;
  printf("[%.4f, %.4f]\n", vr->data[0], vr->data[1]);
}

void printVec3(vec3 v) {
  REQUIRE(vec3SizeCheck(v));

  struct Representation *vr = (struct Representation *)v;
  printf("[%.4f, %.4f, %.4f]\n", vr->data[0], vr->data[1], vr->data[2]);
}

void printVec4(vec4 v) {
  REQUIRE(vec4SizeCheck(v));

  struct Representation *vr = (struct Representation *)v;
  printf("[%.4f, %.4f, %.4f, %.4f]\n", vr->data[0], vr->data[1], vr->data[2],
         vr->data[3]);
}

void printMat3(mat3 m) {
  REQUIRE(mat3SizeCheck(m));

  struct Representation *mr = (struct Representation *)m;

  printf("[%.4f][%.4f][%.4f]\n", mr->data[0], mr->data[3], mr->data[6]);
  printf("[%.4f][%.4f][%.4f]\n", mr->data[1], mr->data[4], mr->data[7]);
  printf("[%.4f][%.4f][%.4f]\n", mr->data[2], mr->data[5], mr->data[8]);
}

void printMat4(mat4 m) {
  REQUIRE(mat4SizeCheck(m));

  struct Representation *mr = (struct Representation *)m;

  printf("[%.4f][%.4f][%.4f][%.4f]\n", mr->data[0], mr->data[4], mr->data[8],
         mr->data[12]);
  printf("[%.4f][%.4f][%.4f][%.4f]\n", mr->data[1], mr->data[5], mr->data[9],
         mr->data[13]);
  printf("[%.4f][%.4f][%.4f][%.4f]\n", mr->data[2], mr->data[6], mr->data[10],
         mr->data[14]);
  printf("[%.4f][%.4f][%.4f][%.4f]\n", mr->data[3], mr->data[7], mr->data[11],
         mr->data[15]);
}

void printVersor(versor q) {
  REQUIRE(versorSizeCheck(q));

  struct Representation *qr = (struct Representation *)q;
  printf("[%.4f ,%.4f, %.4f, %.4f]\n", qr->data[0], qr->data[1], qr->data[2],
         qr->data[3]);
}

/*------------------------------VECTOR FUNCTIONS------------------------------*/

vec3 zeroVec3() {
  struct Representation *vc = representationNew(VEC3_SIZE);
  // RETURN_NULL_ON_FAIL(vc);

  ENSURE(vc != NULL);

  vc->data[0] = 0.0f;
  vc->data[1] = 0.0f;
  vc->data[2] = 0.0f;

  return (vec3)vc;
}

vec4 zeroVec4() {
  struct Representation *vc = representationNew(VEC4_SIZE);
  // RETURN_NULL_ON_FAIL(vc);

  ENSURE(vc != NULL);

  vc->data[0] = 0.0f;
  vc->data[1] = 0.0f;
  vc->data[2] = 0.0f;
  vc->data[3] = 0.0f;

  return (vec4)vc;
}

void vecFree(void *v) {
  // REQUIRE(v != NULL);

  struct Representation *vr = (struct Representation *)v;
  representationFree(vr);

  // v = NULL;
}

vec3 vec3New(double x, double y, double z) {
  struct Representation *v = representationNew(VEC3_SIZE);
  // RETURN_NULL_ON_FAIL(v);

  ENSURE(v != NULL);

  v->data[0] = x;
  v->data[1] = y;
  v->data[2] = z;

  return (vec3)v;
}

float *vec3GetData(vec3 v) {
  REQUIRE(v != NULL);
  REQUIRE(vec3SizeCheck(v));

  struct Representation *vr = (struct Representation *)v;
  return vr->data;
}

size_t vec3GetSize(vec3 v) {
  REQUIRE(v != NULL);
  REQUIRE(vec3SizeCheck(v));

  struct Representation *vr = (struct Representation *)v;
  return vr->size;
}

double vec3Length(vec3 v) {
  REQUIRE(v != NULL);
  REQUIRE(vec3SizeCheck(v));

  struct Representation *vr = (struct Representation *)v;

  return sqrt(vr->data[0] * vr->data[0] + vr->data[1] * vr->data[1] +
              vr->data[2] * vr->data[2]);
}

// squared length
double vec3LengthSquare(vec3 v) {
  REQUIRE(v != NULL);
  REQUIRE(vec3SizeCheck(v));

  struct Representation *vr = (struct Representation *)v;

  return vr->data[0] * vr->data[0] + vr->data[1] * vr->data[1] +
         vr->data[2] * vr->data[2];
}

vec3 vec3Normalize(vec3 v) {
  REQUIRE(v != NULL);
  REQUIRE(vec3SizeCheck(v));

  struct Representation *rv = representationNew(VEC3_SIZE);
  // RETURN_NULL_ON_FAIL(rv);

  double l = vec3Length(v);

  struct Representation *vr = (struct Representation *)v;

  if (0.0f == l) {
    // if (fabs(1.0f - l) < THRESHOLD) {
    // vr->data[0] = vr->data[1] = vr->data[2] = 0.0f;
    rv->data[0] = 0.0f;
    rv->data[1] = 0.0f;
    rv->data[2] = 0.0f;
    return (vec3)rv;
  }

  ENSURE(l != 0);

  rv->data[0] = vr->data[0] / l;
  rv->data[1] = vr->data[1] / l;
  rv->data[2] = vr->data[2] / l;

  return (vec3)rv;
}

vec3 vec3Add(vec3 first, vec3 second) {
  REQUIRE(first != NULL);
  REQUIRE(second != NULL);
  REQUIRE(vec3SizeCheck(first));
  REQUIRE(vec3SizeCheck(second));

  struct Representation *firstr = (struct Representation *)first;
  struct Representation *secondr = (struct Representation *)second;

  struct Representation *vc = representationNew(VEC3_SIZE);
  // RETURN_NULL_ON_FAIL(vc);

  ENSURE(vc != NULL);

  vc->data[0] = firstr->data[0] + secondr->data[0];
  vc->data[1] = firstr->data[1] + secondr->data[1];
  vc->data[2] = firstr->data[2] + secondr->data[2];

  return (vec3)vc;
}

/* void vec3AddOver(_FLOAT *first, const _FLOAT *second) { */
/*   __vec3SizeCheck(first); */
/*   __vec3SizeCheck(second); */
/*   first[0] += second[0]; */
/*   first[1] += second[1]; */
/*   first[2] += second[2]; */
/* } */

vec3 vec3Sub(vec3 first, vec3 second) {
  REQUIRE(first != NULL);
  REQUIRE(second != NULL);
  REQUIRE(vec3SizeCheck(first));
  REQUIRE(vec3SizeCheck(second));

  struct Representation *firstr = (struct Representation *)first;
  struct Representation *secondr = (struct Representation *)second;

  struct Representation *vc = representationNew(VEC3_SIZE);
  // RETURN_NULL_ON_FAIL(vc);

  ENSURE(vc != NULL);

  vc->data[0] = firstr->data[0] - secondr->data[0];
  vc->data[1] = firstr->data[1] - secondr->data[1];
  vc->data[2] = firstr->data[2] - secondr->data[2];

  return (vec3)vc;
}

/* void vec3SubOver(_FLOAT *first, const _FLOAT *second) { */
/*   __vec3SizeCheck(first); */
/*   __vec3SizeCheck(second); */
/*   first[0] -= second[0]; */
/*   first[1] -= second[1]; */
/*   first[2] -= second[2]; */
/* } */

vec3 vec3AddFloat(vec3 v, double num) {
  REQUIRE(v != NULL);
  REQUIRE(vec3SizeCheck(v));

  struct Representation *vr = (struct Representation *)v;

  struct Representation *vc = representationNew(VEC3_SIZE);
  // RETURN_NULL_ON_FAIL(vc);

  ENSURE(vc != NULL);

  vc->data[0] = vr->data[0] + num;
  vc->data[1] = vr->data[1] + num;
  vc->data[2] = vr->data[2] + num;

  return (vec3)vc;
}

/* void vec3AddFloatOver(_FLOAT *v, _FLOAT num) { */
/*   __vec3SizeCheck(v); */
/*   _FLOAT *vc = zeroVec3(); */
/*   vc[0] += num; */
/*   vc[1] += num; */
/*   vc[2] += num; */
/* } */

vec3 vec3SubFloat(vec3 v, double num) {
  REQUIRE(v != NULL);
  REQUIRE(vec3SizeCheck(v));

  struct Representation *vr = (struct Representation *)v;

  struct Representation *vc = representationNew(VEC3_SIZE);
  // RETURN_NULL_ON_FAIL(vc);

  ENSURE(vc != NULL);

  vc->data[0] = vr->data[0] - num;
  vc->data[1] = vr->data[1] - num;
  vc->data[2] = vr->data[2] - num;

  return (vec3)vc;
}

/* void vec3SubFloatOver(_FLOAT *v, _FLOAT num) { */
/*   __vec3SizeCheck(v); */
/*   _FLOAT *vc = zeroVec3(); */
/*   vc[0] -= num; */
/*   vc[1] -= num; */
/*   vc[2] -= num; */
/* } */

vec3 vec3MultFloat(vec3 v, double num) {
  REQUIRE(v != NULL);
  REQUIRE(vec3SizeCheck(v));

  struct Representation *vr = (struct Representation *)v;

  struct Representation *vc = representationNew(VEC3_SIZE);
  // RETURN_NULL_ON_FAIL(vc);

  ENSURE(vc != NULL);

  vc->data[0] = vr->data[0] * num;
  vc->data[1] = vr->data[1] * num;
  vc->data[2] = vr->data[2] * num;

  return (vec3)vc;
}

vec3 vec3DevFloat(vec3 v, double num) {
  REQUIRE(v != NULL);
  REQUIRE(vec3SizeCheck(v));

  REQUIRE(num != 0.0f);

  struct Representation *vr = (struct Representation *)v;

  struct Representation *vc = representationNew(VEC3_SIZE);
  // RETURN_NULL_ON_FAIL(vc);

  ENSURE(vc != NULL);

  vc->data[0] = vr->data[0] / num;
  vc->data[1] = vr->data[1] / num;
  vc->data[2] = vr->data[2] / num;

  return (vec3)vc;
}

/* void vec3MultFloatOver(_FLOAT *v, _FLOAT num) { */
/*   __vec3SizeCheck(v); */

/*   _FLOAT *vc = zeroVec3(); */

/*   vc[0] *= num; */
/*   vc[1] *= num; */
/*   vc[2] *= num; */
/* } */

/* void vec3DevFloatOver(_FLOAT *v, _FLOAT num) { */
/*   __vec3SizeCheck(v); */
/*   assert(num); */
/*   _FLOAT *vc = zeroVec3(); */
/*   vc[0] /= num; */
/*   vc[1] /= num;  */
/*   vc[2] /= num; */
/* } */

vec3 vec3Copy(vec3 source) {
  REQUIRE(source != NULL);
  REQUIRE(vec3SizeCheck(source));

  struct Representation *sourcer = (struct Representation *)source;

  struct Representation *v = representationNew(VEC3_SIZE);
  // RETURN_NULL_ON_FAIL(v);

  ENSURE(v != NULL);

  memcpy(v->data, sourcer->data, VEC3_SIZE * sizeof(double));

  //  v->data[0] = sourcer->data[0];
  //  v->data[1] = sourcer->data[1];
  //  v->data[2] = sourcer->data[2];

  return (vec3)v;
}

double vec3Dot(vec3 a, vec3 b) {
  REQUIRE(a != NULL);
  REQUIRE(b != NULL);
  REQUIRE(vec3SizeCheck(a));
  REQUIRE(vec3SizeCheck(b));

  struct Representation *ar = (struct Representation *)a;
  struct Representation *br = (struct Representation *)b;

  return ar->data[0] * br->data[0] + ar->data[1] * br->data[1] +
         ar->data[2] * br->data[2];
}

vec3 vec3Cross(vec3 a, vec3 b) {
  REQUIRE(a != NULL);
  REQUIRE(b != NULL);
  REQUIRE(vec3SizeCheck(a));
  REQUIRE(vec3SizeCheck(b));

  struct Representation *ar = (struct Representation *)a;
  struct Representation *br = (struct Representation *)b;

  struct Representation *v = representationNew(VEC3_SIZE);
  // RETURN_NULL_ON_FAIL(v);

  ENSURE(v != NULL);

  v->data[0] = ar->data[1] * br->data[2] - ar->data[2] * br->data[1];
  v->data[1] = ar->data[2] * br->data[0] - ar->data[0] * br->data[2];
  v->data[2] = ar->data[0] * br->data[1] - ar->data[1] * br->data[0];

  return (vec3)v;
}

double distanceSquared(vec3 from, vec3 to) {
  REQUIRE(from != NULL);
  REQUIRE(to != NULL);
  REQUIRE(vec3SizeCheck(from));
  REQUIRE(vec3SizeCheck(to));

  struct Representation *fromr = (struct Representation *)from;
  struct Representation *tor = (struct Representation *)to;

  double x = (tor->data[0] - fromr->data[0]) * (tor->data[0] - fromr->data[0]);
  double y = (tor->data[1] - fromr->data[1]) * (tor->data[1] - fromr->data[1]);
  double z = (tor->data[2] - fromr->data[2]) * (tor->data[2] - fromr->data[2]);

  return x + y + z;
}

double distance(vec3 from, vec3 to) {
  REQUIRE(from != NULL);
  REQUIRE(to != NULL);
  REQUIRE(vec3SizeCheck(from));
  REQUIRE(vec3SizeCheck(to));

  struct Representation *fromr = (struct Representation *)from;
  struct Representation *tor = (struct Representation *)to;

  double x = (tor->data[0] - fromr->data[0]) * (tor->data[0] - fromr->data[0]);
  double y = (tor->data[1] - fromr->data[1]) * (tor->data[1] - fromr->data[1]);
  double z = (tor->data[2] - fromr->data[2]) * (tor->data[2] - fromr->data[2]);

  return sqrt(x + y + z);
}

// converts an un-normalised direction into a heading in degrees
// assume that -z is forward

double directionToHeading(vec3 v) {
  REQUIRE(v != NULL);
  REQUIRE(vec3SizeCheck(v));

  struct Representation *vr = (struct Representation *)v;

  return atan2(-vr->data[0], -vr->data[2]) * ONE_RAD_IN_DEG;
}

// converts a heading in degrees into an un-normalised direction
// assume that -z is forward

vec3 headingToDirection(double degrees) {
  double rad = degrees * ONE_DEG_IN_RAD;

  struct Representation *vc = representationNew(VEC3_SIZE);
  // RETURN_NULL_ON_FAIL(vc);

  ENSURE(vc != NULL);

  vc->data[0] = -sinf(rad);
  vc->data[1] = 0.0f;
  vc->data[2] = -cosf(rad);

  return (vec3)vc;
}

/*-----------------------------MATRIX FUNCTIONS-------------------------------*/

mat3 zeroMat3() {
  struct Representation *mat = representationNew(MAT3_SIZE);
  // RETURN_NULL_ON_FAIL(mat);

  ENSURE(mat != NULL);

  for (int i = 0; i < MAT3_SIZE; i++) {
    mat->data[i] = 0.0f;
  }

  return (mat3)mat;
}

mat3 identityMat3() {
  // struct Representation *mat = representationNew(MAT3_SIZE);
  mat3 mat = zeroMat3();
  struct Representation *matr = (struct Representation *)mat;
  // RETURN_NULL_ON_FAIL(mat);

  ENSURE(mat != NULL);

  matr->data[0] = 1.0f;
  matr->data[4] = 1.0f;
  matr->data[8] = 1.0f;

  return (mat3)matr;
}

float *mat3GetData(mat3 m) {
  REQUIRE(m != NULL);
  REQUIRE(mat3SizeCheck(m));

  struct Representation *mr = (struct Representation *)m;
  return mr->data;
}

size_t mat3GetSize(mat3 m) {
  REQUIRE(m != NULL);
  REQUIRE(mat3SizeCheck(m));

  struct Representation *mr = (struct Representation *)m;
  return mr->size;
}

mat4 zeroMat4() {
  struct Representation *mat = representationNew(MAT4_SIZE);
  // RETURN_NULL_ON_FAIL(mat);

  ENSURE(mat != NULL);

  for (int i = 0; i < MAT4_SIZE; i++) {
    mat->data[i] = 0.0f;
  }

  return (mat4)mat;
}

mat4 identityMat4() {
  // struct Representation *mat = representationNew(MAT4_SIZE);
  mat4 mat = zeroMat4();
  struct Representation *matr = (struct Representation *)mat;
  // RETURN_NULL_ON_FAIL(mat);

  ENSURE(mat != NULL);

  matr->data[0] = 1.0f;
  matr->data[5] = 1.0f;
  matr->data[10] = 1.0f;
  matr->data[15] = 1.0f;

  return (mat4)matr;

  // return mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
  // 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

float *mat4GetData(mat4 m) {
  REQUIRE(m != NULL);
  REQUIRE(mat4SizeCheck(m));

  struct Representation *mr = (struct Representation *)m;
  return mr->data;
}

size_t mat4GetSize(mat4 m) {
  REQUIRE(m != NULL);
  REQUIRE(mat4SizeCheck(m));

  struct Representation *mr = (struct Representation *)m;
  return mr->size;
}

void mat4ComponentsAssign(mat4 target, mat4 source) {
  REQUIRE(target != NULL);
  REQUIRE(source != NULL);
  REQUIRE(mat4SizeCheck(target));
  REQUIRE(mat4SizeCheck(source));

  struct Representation *targetr = (struct Representation *)target;
  struct Representation *sourcer = (struct Representation *)source;

  for (int i = 0; i < MAT4_SIZE; i++) {
    targetr->data[i] = sourcer->data[i];
  }
}

void matFree(void *m) {
  // REQUIRE(m != NULL);

  struct Representation *mr = (struct Representation *)m;
  representationFree(mr);

  // m = NULL;
}

/* mat4 array layout
 0  4  8 12
 1  5  9 13
 2  6 10 14
 3  7 11 15
*/

vec4 mat4MulVec4(mat4 m, vec4 v) {
  REQUIRE(m != NULL);
  REQUIRE(v != NULL);
  REQUIRE(mat4SizeCheck(m));
  REQUIRE(vec4SizeCheck(v));

  struct Representation *mr = (struct Representation *)m;
  struct Representation *vr = (struct Representation *)v;

  struct Representation *vc = representationNew(VEC4_SIZE);
  // RETURN_NULL_ON_FAIL(vc);

  ENSURE(vc != NULL);

  // 0x + 4y + 8z + 12w
  vc->data[0] = mr->data[0] * vr->data[0] + mr->data[4] * vr->data[1] +
                mr->data[8] * vr->data[2] + mr->data[12] * vr->data[3];
  // 1x + 5y + 9z + 13w
  vc->data[1] = mr->data[1] * vr->data[0] + mr->data[5] * vr->data[1] +
                mr->data[9] * vr->data[2] + mr->data[13] * vr->data[3];
  // 2x + 6y + 10z + 14w
  vc->data[2] = mr->data[2] * vr->data[0] + mr->data[6] * vr->data[1] +
                mr->data[10] * vr->data[2] + mr->data[14] * vr->data[3];
  // 3x + 7y + 11z + 15w
  vc->data[3] = mr->data[3] * vr->data[0] + mr->data[7] * vr->data[1] +
                mr->data[11] * vr->data[2] + mr->data[15] * vr->data[3];

  return (vec4)vc;
}

mat4 mat4MulMat4(mat4 first, mat4 second) {
  REQUIRE(first != NULL);
  REQUIRE(second != NULL);
  REQUIRE(mat4SizeCheck(first));
  REQUIRE(mat4SizeCheck(second));

  struct Representation *firstr = (struct Representation *)first;
  struct Representation *secondr = (struct Representation *)second;

  struct Representation *mat = representationNew(MAT4_SIZE);
  // RETURN_NULL_ON_FAIL(mat);

  ENSURE(mat != NULL);

  unsigned int r_index = 0;
  int mat4SqrtSize = sqrt(MAT4_SIZE);

  ENSURE(mat4SqrtSize == 4);

  for (int col = 0; col < mat4SqrtSize; col++) {
    for (int row = 0; row < mat4SqrtSize; row++) {
      double sum = 0.0f;

      for (int i = 0; i < mat4SqrtSize; i++) {
        // NOTE: first * second is not equal to second * first in matrix
        // multiplication
        // in this case, we use rows in first mat4 to multiply columns in the
        // seconds mat4

        sum += firstr->data[i + col * mat4SqrtSize] *
               secondr->data[row + i * mat4SqrtSize];
      }

      mat->data[r_index] = sum;
      r_index++;
    }
  }

  return (mat4)mat;
}

mat4 mat4Copy(mat4 m) {
  REQUIRE(m != NULL);
  REQUIRE(mat4SizeCheck(m));

  struct Representation *mr = (struct Representation *)m;

  struct Representation *mat = representationNew(MAT4_SIZE);
  // RETURN_NULL_ON_FAIL(mat);

  ENSURE(mat != NULL);

  memcpy(mat->data, mr->data, MAT4_SIZE * sizeof(double));

  // for (int i = 0; i < MAT4_SIZE; i++) {
  //  mat->data[i] = mr->data[i];
  //}

  return (mat4)mat;
}

double determinant(mat4 m) {
  REQUIRE(m != NULL);
  REQUIRE(mat4SizeCheck(m));

  struct Representation *mr = (struct Representation *)m;

  double dv = mr->data[12] * mr->data[9] * mr->data[6] * mr->data[3] -
              mr->data[8] * mr->data[13] * mr->data[6] * mr->data[3] -
              mr->data[12] * mr->data[5] * mr->data[10] * mr->data[3] +
              mr->data[4] * mr->data[13] * mr->data[10] * mr->data[3] +
              mr->data[8] * mr->data[5] * mr->data[14] * mr->data[3] -
              mr->data[4] * mr->data[9] * mr->data[14] * mr->data[3] -
              mr->data[12] * mr->data[9] * mr->data[2] * mr->data[7] +
              mr->data[8] * mr->data[13] * mr->data[2] * mr->data[7] +
              mr->data[12] * mr->data[1] * mr->data[10] * mr->data[7] -
              mr->data[0] * mr->data[13] * mr->data[10] * mr->data[7] -
              mr->data[8] * mr->data[1] * mr->data[14] * mr->data[7] +
              mr->data[0] * mr->data[9] * mr->data[14] * mr->data[7] +
              mr->data[12] * mr->data[5] * mr->data[2] * mr->data[11] -
              mr->data[4] * mr->data[13] * mr->data[2] * mr->data[11] -
              mr->data[12] * mr->data[1] * mr->data[6] * mr->data[11] +
              mr->data[0] * mr->data[13] * mr->data[6] * mr->data[11] +
              mr->data[4] * mr->data[1] * mr->data[14] * mr->data[11] -
              mr->data[0] * mr->data[5] * mr->data[14] * mr->data[11] -
              mr->data[8] * mr->data[5] * mr->data[2] * mr->data[15] +
              mr->data[4] * mr->data[9] * mr->data[2] * mr->data[15] +
              mr->data[8] * mr->data[1] * mr->data[6] * mr->data[15] -
              mr->data[0] * mr->data[9] * mr->data[6] * mr->data[15] -
              mr->data[4] * mr->data[1] * mr->data[10] * mr->data[15] +
              mr->data[0] * mr->data[5] * mr->data[10] * mr->data[15];
  return dv;
}

mat4 inverse(mat4 m) {
  REQUIRE(m != NULL);
  REQUIRE(mat4SizeCheck(m));

  double det = determinant(m);
  // there is no inverse if determinant is zero

  if (0.0f == det) {
    // printf("WARNING. matrix has no determinant. can not be inverted\n");
    // return m;

    // matrix cannot be inverted if the determinant of the matrix is 0
    return NULL;
  }

  ENSURE(det != 0.0f);

  double inv_det = 1.0f / det;

  struct Representation *mr = (struct Representation *)m;

  struct Representation *mat = representationNew(MAT4_SIZE);
  // RETURN_NULL_ON_FAIL(mat);

  ENSURE(mat != NULL);

  mat->data[0] = inv_det * (mr->data[9] * mr->data[14] * mr->data[7] -
                            mr->data[13] * mr->data[10] * mr->data[7] +
                            mr->data[13] * mr->data[6] * mr->data[11] -
                            mr->data[5] * mr->data[14] * mr->data[11] -
                            mr->data[9] * mr->data[6] * mr->data[15] +
                            mr->data[5] * mr->data[10] * mr->data[15]);

  mat->data[1] = inv_det * (mr->data[13] * mr->data[10] * mr->data[3] -
                            mr->data[9] * mr->data[14] * mr->data[3] -
                            mr->data[13] * mr->data[2] * mr->data[11] +
                            mr->data[1] * mr->data[14] * mr->data[11] +
                            mr->data[9] * mr->data[2] * mr->data[15] -
                            mr->data[1] * mr->data[10] * mr->data[15]);

  mat->data[2] = inv_det * (mr->data[5] * mr->data[14] * mr->data[3] -
                            mr->data[13] * mr->data[6] * mr->data[3] +
                            mr->data[13] * mr->data[2] * mr->data[7] -
                            mr->data[1] * mr->data[14] * mr->data[7] -
                            mr->data[5] * mr->data[2] * mr->data[15] +
                            mr->data[1] * mr->data[6] * mr->data[15]);

  mat->data[3] = inv_det * (mr->data[9] * mr->data[6] * mr->data[3] -
                            mr->data[5] * mr->data[10] * mr->data[3] -
                            mr->data[9] * mr->data[2] * mr->data[7] +
                            mr->data[1] * mr->data[10] * mr->data[7] +
                            mr->data[5] * mr->data[2] * mr->data[11] -
                            mr->data[1] * mr->data[6] * mr->data[11]);

  mat->data[4] = inv_det * (mr->data[12] * mr->data[10] * mr->data[7] -
                            mr->data[8] * mr->data[14] * mr->data[7] -
                            mr->data[12] * mr->data[6] * mr->data[11] +
                            mr->data[4] * mr->data[14] * mr->data[11] +
                            mr->data[8] * mr->data[6] * mr->data[15] -
                            mr->data[4] * mr->data[10] * mr->data[15]);

  mat->data[5] = inv_det * (mr->data[8] * mr->data[14] * mr->data[3] -
                            mr->data[12] * mr->data[10] * mr->data[3] +
                            mr->data[12] * mr->data[2] * mr->data[11] -
                            mr->data[0] * mr->data[14] * mr->data[11] -
                            mr->data[8] * mr->data[2] * mr->data[15] +
                            mr->data[0] * mr->data[10] * mr->data[15]);

  mat->data[6] = inv_det * (mr->data[12] * mr->data[6] * mr->data[3] -
                            mr->data[4] * mr->data[14] * mr->data[3] -
                            mr->data[12] * mr->data[2] * mr->data[7] +
                            mr->data[0] * mr->data[14] * mr->data[7] +
                            mr->data[4] * mr->data[2] * mr->data[15] -
                            mr->data[0] * mr->data[6] * mr->data[15]);

  mat->data[7] = inv_det * (mr->data[4] * mr->data[10] * mr->data[3] -
                            mr->data[8] * mr->data[6] * mr->data[3] +
                            mr->data[8] * mr->data[2] * mr->data[7] -
                            mr->data[0] * mr->data[10] * mr->data[7] -
                            mr->data[4] * mr->data[2] * mr->data[11] +
                            mr->data[0] * mr->data[6] * mr->data[11]);

  mat->data[8] = inv_det * (mr->data[8] * mr->data[13] * mr->data[7] -
                            mr->data[12] * mr->data[9] * mr->data[7] +
                            mr->data[12] * mr->data[5] * mr->data[11] -
                            mr->data[4] * mr->data[13] * mr->data[11] -
                            mr->data[8] * mr->data[5] * mr->data[15] +
                            mr->data[4] * mr->data[9] * mr->data[15]);

  mat->data[9] = inv_det * (mr->data[12] * mr->data[9] * mr->data[3] -
                            mr->data[8] * mr->data[13] * mr->data[3] -
                            mr->data[12] * mr->data[1] * mr->data[11] +
                            mr->data[0] * mr->data[13] * mr->data[11] +
                            mr->data[8] * mr->data[1] * mr->data[15] -
                            mr->data[0] * mr->data[9] * mr->data[15]);

  mat->data[10] = inv_det * (mr->data[4] * mr->data[13] * mr->data[3] -
                             mr->data[12] * mr->data[5] * mr->data[3] +
                             mr->data[12] * mr->data[1] * mr->data[7] -
                             mr->data[0] * mr->data[13] * mr->data[7] -
                             mr->data[4] * mr->data[1] * mr->data[15] +
                             mr->data[0] * mr->data[5] * mr->data[15]);

  mat->data[11] = inv_det * (mr->data[8] * mr->data[5] * mr->data[3] -
                             mr->data[4] * mr->data[9] * mr->data[3] -
                             mr->data[8] * mr->data[1] * mr->data[7] +
                             mr->data[0] * mr->data[9] * mr->data[7] +
                             mr->data[4] * mr->data[1] * mr->data[11] -
                             mr->data[0] * mr->data[5] * mr->data[11]);

  mat->data[12] = inv_det * (mr->data[12] * mr->data[9] * mr->data[6] -
                             mr->data[8] * mr->data[13] * mr->data[6] -
                             mr->data[12] * mr->data[5] * mr->data[10] +
                             mr->data[4] * mr->data[13] * mr->data[10] +
                             mr->data[8] * mr->data[5] * mr->data[14] -
                             mr->data[4] * mr->data[9] * mr->data[14]);

  mat->data[13] = inv_det * (mr->data[8] * mr->data[13] * mr->data[2] -
                             mr->data[12] * mr->data[9] * mr->data[2] +
                             mr->data[12] * mr->data[1] * mr->data[10] -
                             mr->data[0] * mr->data[13] * mr->data[10] -
                             mr->data[8] * mr->data[1] * mr->data[14] +
                             mr->data[0] * mr->data[9] * mr->data[14]);

  mat->data[14] = inv_det * (mr->data[12] * mr->data[5] * mr->data[2] -
                             mr->data[4] * mr->data[13] * mr->data[2] -
                             mr->data[12] * mr->data[1] * mr->data[6] +
                             mr->data[0] * mr->data[13] * mr->data[6] +
                             mr->data[4] * mr->data[1] * mr->data[14] -
                             mr->data[0] * mr->data[5] * mr->data[14]);

  mat->data[15] = inv_det * (mr->data[4] * mr->data[9] * mr->data[2] -
                             mr->data[8] * mr->data[5] * mr->data[2] +
                             mr->data[8] * mr->data[1] * mr->data[6] -
                             mr->data[0] * mr->data[9] * mr->data[6] -
                             mr->data[4] * mr->data[1] * mr->data[10] +
                             mr->data[0] * mr->data[5] * mr->data[10]);

  return (mat4)mat;
}

mat4 transpose(mat4 m) {
  REQUIRE(m != NULL);
  REQUIRE(mat4SizeCheck(m));

  struct Representation *mr = (struct Representation *)m;

  struct Representation *mat = representationNew(MAT4_SIZE);
  // RETURN_NULL_ON_FAIL(mat);

  ENSURE(mat != NULL);

  mat->data[0] = mr->data[0];
  mat->data[1] = mr->data[4];
  mat->data[2] = mr->data[8];
  mat->data[3] = mr->data[12];
  mat->data[4] = mr->data[1];
  mat->data[5] = mr->data[5];
  mat->data[6] = mr->data[9];
  mat->data[7] = mr->data[13];
  mat->data[8] = mr->data[2];
  mat->data[9] = mr->data[6];
  mat->data[10] = mr->data[10];
  mat->data[11] = mr->data[14];
  mat->data[12] = mr->data[3];
  mat->data[13] = mr->data[7];
  mat->data[14] = mr->data[11];
  mat->data[15] = mr->data[15];

  return (mat4)mat;
}

/*--------------------------AFFINE MATRIX FUNCTIONS---------------------------*/

// translate a 4d matrix with xyz array
mat4 translate(mat4 m, vec3 v) {
  REQUIRE(m != NULL);
  REQUIRE(v != NULL);
  REQUIRE(mat4SizeCheck(m));
  REQUIRE(vec3SizeCheck(v));

  struct Representation *vr = (struct Representation *)v;

  // struct Representation *mat = representationNew(MAT4_SIZE);
  mat4 mat = identityMat4();
  struct Representation *matr = (struct Representation *)mat;
  // RETURN_NULL_ON_FAIL(mat);

  ENSURE(mat != NULL);

  matr->data[12] = vr->data[0];
  matr->data[13] = vr->data[1];
  matr->data[14] = vr->data[2];

  mat4 rm = mat4MulMat4((mat4)matr, m);
  ENSURE(rm != NULL);

  matFree(mat);

  return rm;
}

// rotate around x axis by an angle in degrees
mat4 rotateXdeg(mat4 m, double deg) {
  REQUIRE(m != NULL);
  REQUIRE(mat4SizeCheck(m));

  // convert to radians
  double rad = deg * ONE_DEG_IN_RAD;

  // struct Representation *mr = representationNew(MAT4_SIZE);
  mat4 mat = identityMat4();
  struct Representation *matr = (struct Representation *)mat;
  // RETURN_NULL_ON_FAIL(mr);

  ENSURE(matr != NULL);

  matr->data[5] = cos(rad);
  matr->data[9] = -sin(rad);
  matr->data[6] = sin(rad);
  matr->data[10] = cos(rad);

  mat4 rm = mat4MulMat4((mat4)matr, m);
  ENSURE(rm != NULL);

  matFree(matr);
  return rm;
}

// rotate around y axis by an angle in degrees
mat4 rotateYdeg(mat4 m, double deg) {
  REQUIRE(m != NULL);
  REQUIRE(mat4SizeCheck(m));

  // convert to radians
  double rad = deg * ONE_DEG_IN_RAD;

  mat4 mat = identityMat4();
  struct Representation *matr = (struct Representation *)mat;
  // struct Representation *mr = representationNew(MAT4_SIZE);
  // RETURN_NULL_ON_FAIL(mr);

  ENSURE(matr != NULL);

  matr->data[0] = cos(rad);
  matr->data[8] = sin(rad);
  matr->data[2] = -sin(rad);
  matr->data[10] = cos(rad);

  mat4 rm = mat4MulMat4((mat4)matr, m);
  ENSURE(rm != NULL);

  matFree(matr);

  return rm;
}

// rotate around z axis by an angle in degrees
mat4 rotateZdeg(mat4 m, double deg) {
  REQUIRE(m != NULL);
  REQUIRE(mat4SizeCheck(m));

  // convert to radians
  double rad = deg * ONE_DEG_IN_RAD;

  mat4 mat = identityMat4();
  struct Representation *matr = (struct Representation *)mat;
  // struct Representation *mr = representationNew(MAT4_SIZE);
  // RETURN_NULL_ON_FAIL(mr);

  ENSURE(matr != NULL);

  matr->data[0] = cos(rad);
  matr->data[4] = -sin(rad);
  matr->data[1] = sin(rad);
  matr->data[5] = cos(rad);

  mat4 rm = mat4MulMat4((mat4)matr, m);
  ENSURE(rm != NULL);

  matFree(matr);

  return rm;
}

// scale a matrix by [x, y, z]
mat4 scale(mat4 m, vec3 v) {
  REQUIRE(m != NULL);
  REQUIRE(v != NULL);
  REQUIRE(mat4SizeCheck(m));
  REQUIRE(vec3SizeCheck(v));

  struct Representation *vr = (struct Representation *)v;

  mat4 a = identityMat4();
  struct Representation *ar = (struct Representation *)a;
  // struct Representation *ar = representationNew(MAT4_SIZE);
  // RETURN_NULL_ON_FAIL(ar);

  ENSURE(ar != NULL);

  ar->data[0] = vr->data[0];
  ar->data[5] = vr->data[1];
  ar->data[10] = vr->data[2];

  mat4 rm = mat4MulMat4((mat4)ar, m);
  ENSURE(rm != NULL);

  matFree(ar);

  return rm;
}

/*-----------------------VIRTUAL CAMERA MATRIX FUNCTIONS----------------------*/

// returns a view matrix using the opengl lookAt style. COLUMN ORDER.
mat4 lookAt(vec3 camPos, vec3 tarPos, vec3 up) {
  REQUIRE(camPos != NULL);
  REQUIRE(tarPos != NULL);
  REQUIRE(up != NULL);
  REQUIRE(vec3SizeCheck(camPos));
  REQUIRE(vec3SizeCheck(tarPos));
  REQUIRE(vec3SizeCheck(up));

  struct Representation *camPosr = (struct Representation *)camPos;
  //  struct Representation *tarPosr = (struct Representation *)tarPos;
  //  struct Representation *upr = (struct Representation *)up;

  // inverse translation to make camera position at world origin
  mat4 p = identityMat4();
  // RETURN_NULL_ON_FAIL(p);
  ENSURE(p != NULL);

  vec3 camDir =
      vec3New(-camPosr->data[0], -camPosr->data[1], -camPosr->data[2]);

  // RETURN_NULL_ON_FAIL(camDir);
  ENSURE(camDir != NULL);

  mat4 q = translate(p, camDir);

  // RETURN_NULL_ON_FAIL(q);
  ENSURE(q != NULL);

  // distance vector
  vec3 d = vec3Sub(tarPos, camPos);

  // RETURN_NULL_ON_FAIL(d);
  ENSURE(d != NULL);

  // forward vector
  vec3 f = vec3Normalize(d);
  // RETURN_NULL_ON_FAIL(f);
  ENSURE(f != NULL);

  struct Representation *fr = (struct Representation *)f;

  // right vector
  vec3 r = vec3Cross(f, up);
  // RETURN_NULL_ON_FAIL(r);
  ENSURE(r != NULL);

  vec3 nr = vec3Normalize(r);
  // RETURN_NULL_ON_FAIL(nr);
  ENSURE(nr != NULL);

  struct Representation *nrr = (struct Representation *)nr;

  // real up vector
  vec3 u = vec3Cross(nr, f);
  // RETURN_NULL_ON_FAIL(u);
  ENSURE(u != NULL);

  vec3 nu = vec3Normalize(u);
  // RETURN_NULL_ON_FAIL(nu);
  ENSURE(nu != NULL);

  struct Representation *nur = (struct Representation *)nu;

  struct Representation *ori = (struct Representation *)identityMat4();
  // RETURN_NULL_ON_FAIL(ori);
  ENSURE(ori != NULL);
  // note that the matrix is in cloumn major order

  ori->data[0] = nrr->data[0];
  ori->data[4] = nrr->data[1];
  ori->data[8] = nrr->data[2];
  ori->data[1] = nur->data[0];
  ori->data[5] = nur->data[1];
  ori->data[9] = nur->data[2];
  ori->data[2] = -fr->data[0];
  ori->data[6] = -fr->data[1];
  ori->data[10] = -fr->data[2];

  mat4 rm = mat4MulMat4((mat4)ori, q);
  // RETURN_NULL_ON_FAIL(rm);
  ENSURE(rm != NULL);

  // clean up calculate resource
  matFree(p);
  vecFree(camDir);
  matFree(q);
  vecFree(d);
  vecFree(f);
  vecFree(r);
  vecFree(nr);
  vecFree(u);
  vecFree(nu);
  matFree((mat4)ori);

  return rm;
  // return ori * p; // p * ori;
}

// returns a perspective function mimicking the opengl projection style.
mat4 perspective(double fovy, double aspect, double near, double far) {
  double fovRad = fovy * ONE_DEG_IN_RAD;

  double range = tan(fovRad / 2.0f) * near;

  double sx = (2.0f * near) / (range * aspect + range * aspect);
  double sy = near / range;
  double sz = -(far + near) / (far - near);
  double pz = -(2.0f * far * near) / (far - near);

  // struct Representation *mr = representationNew(MAT4_SIZE);
  mat4 m = zeroMat4();
  struct Representation *mr = (struct Representation *)m;
  // RETURN_NULL_ON_FAIL(mr);

  ENSURE(mr != NULL);

  // make sure bottom-right corner is zero
  // note that the matrix is in cloumn major order

  mr->data[0] = sx;
  mr->data[5] = sy;
  mr->data[10] = sz;
  mr->data[14] = pz;
  mr->data[11] = -1.0f;

  return (mat4)mr;
}

/*----------------------------HAMILTON FUNCTION-------------------------------*/

versor zeroVersor() {
  struct Representation *ver = representationNew(VERSOR_SIZE);
  // RETURN_NULL_ON_FAIL(ver);

  ENSURE(ver != NULL);

  for (int i = 0; i < VERSOR_SIZE; i++) {
    ver->data[i] = 0.0f;
  }

  return (versor)ver;
}

void versorFree(void *ve) {
  // REQUIRE(ve != NULL);

  struct Representation *ver = (struct Representation *)ve;
  representationFree(ver);
}

versor versorCopy(versor source) {
  REQUIRE(source != NULL);
  REQUIRE(versorSizeCheck(source));

  struct Representation *sourcer = (struct Representation *)source;

  struct Representation *v = representationNew(VERSOR_SIZE);
  // RETURN_NULL_ON_FAIL(v);
  ENSURE(v != NULL);

  memcpy(v->data, sourcer->data, VERSOR_SIZE * sizeof(double));

  //  v->data[0] = sourcer->data[0];
  //  v->data[1] = sourcer->data[1];
  //  v->data[2] = sourcer->data[2];

  return (versor)v;
}

float *versorGetData(versor vr) {
  REQUIRE(vr != NULL);
  REQUIRE(versorSizeCheck(vr));

  struct Representation *vrr = (struct Representation *)vr;
  return vrr->data;
}

size_t versorGetSize(versor vr) {
  REQUIRE(vr != NULL);
  REQUIRE(versorSizeCheck(vr));

  struct Representation *vrr = (struct Representation *)vr;
  return vrr->size;
}

versor versorDevFloat(versor ve, double num) {
  REQUIRE(versorSizeCheck(ve));
  REQUIRE(num != 0.0f);

  struct Representation *ver = (struct Representation *)ve;

  struct Representation *re = representationNew(VERSOR_SIZE);
  // RETURN_NULL_ON_FAIL(re);
  ENSURE(re != NULL);

  re->data[0] = ver->data[0] / num;
  re->data[1] = ver->data[1] / num;
  re->data[2] = ver->data[2] / num;
  re->data[3] = ver->data[3] / num;

  return (versor)re;
}

versor versorMulFloat(versor ve, double num) {
  REQUIRE(versorSizeCheck(ve));

  struct Representation *ver = (struct Representation *)ve;

  struct Representation *re = representationNew(VERSOR_SIZE);
  // RETURN_NULL_ON_FAIL(re);
  ENSURE(re != NULL);

  re->data[0] = ver->data[0] * num;
  re->data[1] = ver->data[1] * num;
  re->data[2] = ver->data[2] * num;
  re->data[3] = ver->data[3] * num;

  return (versor)re;
}

versor versorNormalize(versor q) {
  REQUIRE(versorSizeCheck(q));

  struct Representation *qr = (struct Representation *)q;

  // normalize(q) = q / magnitude (q)
  // magnitude (q) = sqrt (w*w + x*x...)
  // only compute sqrt if sum != 1.0

  double sum = qr->data[0] * qr->data[0] + qr->data[1] * qr->data[1] +
               qr->data[2] * qr->data[2] + qr->data[3] * qr->data[3];

  // Note: floats have min 6 digits of precision

  if (fabs(1.0f - sum) < THRESHOLD) {
    return zeroVersor();
  }

  double mag = sqrt(sum);

  ENSURE(mag != 0.0f);

  versor rve = versorDevFloat(q, mag);
  ENSURE(rve != NULL);

  return rve;
}

versor versorMulVersor(versor first, versor second) {
  REQUIRE(first != NULL);
  REQUIRE(second != NULL);
  REQUIRE(versorSizeCheck(first));
  REQUIRE(versorSizeCheck(second));

  struct Representation *firstr = (struct Representation *)first;
  struct Representation *secondr = (struct Representation *)second;

  struct Representation *re = representationNew(VERSOR_SIZE);
  // RETURN_NULL_ON_FAIL(re);
  ENSURE(re != NULL);

  re->data[0] =
      firstr->data[0] * secondr->data[0] - firstr->data[1] * secondr->data[1] -
      firstr->data[2] * secondr->data[2] - firstr->data[3] * secondr->data[3];
  re->data[1] =
      firstr->data[0] * secondr->data[1] + firstr->data[1] * secondr->data[0] -
      firstr->data[2] * secondr->data[3] + firstr->data[3] * secondr->data[2];
  re->data[2] =
      firstr->data[0] * secondr->data[2] + firstr->data[1] * secondr->data[3] +
      firstr->data[2] * secondr->data[0] - firstr->data[3] * secondr->data[1];
  re->data[3] =
      firstr->data[0] * secondr->data[3] - firstr->data[1] * secondr->data[2] +
      firstr->data[2] * secondr->data[1] + firstr->data[3] * secondr->data[0];

  // re-normalise in case of mangling
  versor rve = versorNormalize((versor)re);

  ENSURE(rve != NULL);

  versorFree((versor)re);

  return rve;
}

versor versorAdd(versor first, versor second) {
  REQUIRE(first != NULL);
  REQUIRE(second != NULL);
  REQUIRE(versorSizeCheck(first));
  REQUIRE(versorSizeCheck(second));

  struct Representation *firstr = (struct Representation *)first;
  struct Representation *secondr = (struct Representation *)second;

  struct Representation *re = representationNew(VERSOR_SIZE);
  // RETURN_NULL_ON_FAIL(re);
  ENSURE(re != NULL);

  re->data[0] = firstr->data[0] + secondr->data[0];
  re->data[1] = firstr->data[1] + secondr->data[1];
  re->data[2] = firstr->data[2] + secondr->data[2];
  re->data[3] = firstr->data[3] + secondr->data[3];

  // re-normalise in case of mangling
  versor rve = versorNormalize((versor)re);
  ENSURE(rve != NULL);

  versorFree((versor)re);

  return rve;
}

versor quatFromAxisRad(double radians, double x, double y, double z) {
  struct Representation *re = representationNew(VERSOR_SIZE);
  // RETURN_NULL_ON_FAIL(re);
  ENSURE(re != NULL);

  re->data[0] = cos(radians / 2.0f);
  re->data[1] = sin(radians / 2.0f) * x;
  re->data[2] = sin(radians / 2.0f) * y;
  re->data[3] = sin(radians / 2.0f) * z;

  return (versor)re;
}

versor quatFromAxisDeg(double degrees, double x, double y, double z) {
  return quatFromAxisRad(ONE_DEG_IN_RAD * degrees, x, y, z);
}

mat4 quatToMat4(versor q) {
  REQUIRE(q != NULL);
  REQUIRE(versorSizeCheck(q));

  struct Representation *qr = (struct Representation *)q;

  double w = qr->data[0];
  double x = qr->data[1];
  double y = qr->data[2];
  double z = qr->data[3];

  struct Representation *m = representationNew(MAT4_SIZE);
  // RETURN_NULL_ON_FAIL(m);
  ENSURE(m != NULL);

  m->data[0] = 1.0f - 2.0f * y * y - 2.0f * z * z;
  m->data[1] = 2.0f * x * y + 2.0f * w * z;
  m->data[2] = 2.0f * x * z - 2.0f * w * y;
  m->data[3] = 0.0f;
  m->data[4] = 2.0f * x * y - 2.0f * w * z;
  m->data[5] = 1.0f - 2.0f * x * x - 2.0f * z * z;
  m->data[6] = 2.0f * y * z + 2.0f * w * x;
  m->data[7] = 0.0f;
  m->data[8] = 2.0f * x * z + 2.0f * w * y;
  m->data[9] = 2.0f * y * z - 2.0f * w * x;
  m->data[10] = 1.0f - 2.0f * x * x - 2.0f * y * y;
  m->data[11] = 0.0f;
  m->data[12] = 0.0f;
  m->data[13] = 0.0f;
  m->data[14] = 0.0f;
  m->data[15] = 1.0;

  return (mat4)m;
}

double versorDot(versor q, versor r) {
  REQUIRE(q != NULL);
  REQUIRE(r != NULL);
  REQUIRE(versorSizeCheck(q));
  REQUIRE(versorSizeCheck(r));

  struct Representation *qr = (struct Representation *)q;
  struct Representation *rr = (struct Representation *)r;

  return qr->data[0] * rr->data[0] + qr->data[1] * rr->data[1] +
         qr->data[2] * rr->data[2] + qr->data[3] * rr->data[3];
}

versor versorSlerp(versor q, versor r, double t) {
  REQUIRE(q != NULL);
  REQUIRE(r != NULL);
  REQUIRE(versorSizeCheck(q));
  REQUIRE(versorSizeCheck(r));

  struct Representation *qr = (struct Representation *)q;
  struct Representation *rr = (struct Representation *)r;

  // angle between q0-q1
  double cosHalfTheta = versorDot(q, r);

  // if dot product is negative then one quaternion should be negated, to make
  // it take the short way around, rather than the long way

  // we had to recalculate the dot product after this
  if (cosHalfTheta < 0.0f) {
    for (int i = 0; i < VERSOR_SIZE; i++) {
      qr->data[i] *= -1.0f;
    }

    cosHalfTheta = versorDot(q, r);
  }

  // if qa=qb or qa=-qb then theta = 0 and we can return qa
  if (fabs(cosHalfTheta) >= 1.0f) {
    // return (versor)qr;
    return versorCopy(q);
  }

  struct Representation *re = representationNew(VERSOR_SIZE);
  // RETURN_NULL_ON_FAIL(re);
  ENSURE(re != NULL);

  double sinHalfTheta = sqrt(1.0f - cosHalfTheta * cosHalfTheta);
  // if theta = 180 degrees then result is not fully defined
  // we could rotate around any axis normal to qa or qb

  // if (fabs(sinHalfTheta) < 0.001f) {
  if (fabs(sinHalfTheta) < THRESHOLD) {
    for (int i = 0; i < VERSOR_SIZE; i++) {
      re->data[i] = (1.0f - t) * qr->data[i] + t * rr->data[i];
    }
    return (versor)re;
  }

  double halfTheta = acos(cosHalfTheta);
  double a = sin((1.0f - t) * halfTheta) / sinHalfTheta;
  double b = sin(t * halfTheta) / sinHalfTheta;

  for (int i = 0; i < VERSOR_SIZE; i++) {
    re->data[i] = qr->data[i] * a + rr->data[i] * b;
  }
  return (versor)re;
}
