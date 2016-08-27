#include "linear_math.h"

#define TAU 2.0 * M_PI
#define ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0  // 0.017444444
#define ONE_RAD_IN_DEG 360.0 / (2.0 * M_PI)  // 57.2957795

#define VEC2_SIZE 2
#define VEC3_SIZE 3
#define VEC4_SIZE 4
#define MAT3_SIZE 9
#define MAT4_SIZE 16
#define VERSOR_SIZE 4

#define __LINEAR_MATH_DEBUG 1

/*-----------------------------DEGUB MACRO------------------------------------*/

struct Representation {
  double *data;
  unsigned int size;
};

static struct Representation *representationNew(size_t dataSize) {
  struct Representation *re =
      defenseMalloc(sizeof(struct Representation), mallocFailAbort, NULL);
  re->size = dataSize;

  re->data = defenseMalloc(dataSize * sizeof(double), mallocFailAbort, NULL);

  return re;
}

#if __LINEAR_MATH_DEBUG
inline static void vec2SizeCheck(vec2 v) {
  struct Representation *vr = (struct Representation *)v;
  assert(vr->size == VEC2_SIZE);
}

inline static void vec3SizeCheck(vec3 v) {
  struct Representation *vr = (struct Representation *)v;
  assert(vr->size == VEC3_SIZE);
}

inline static void vec4SizeCheck(vec4 v) {
  struct Representation *vr = (struct Representation *)v;
  assert(vr->size == VEC4_SIZE);
}

inline static void mat3SizeCheck(mat3 m) {
  struct Representation *mr = (struct Representation *)m;
  assert(mr->size == MAT3_SIZE);
}

inline static void mat4SizeCheck(mat4 m) {
  struct Representation *mr = (struct Representation *)m;
  assert(mr->size == MAT4_SIZE);
}

inline static void versorSizeCheck(versor ve) {
  struct Representation *ver = (struct Representation *)ve;
  assert(ver->size == VERSOR_SIZE);
}

#define __vec2_size_check(expr) vec2SizeCheck(expr)
#define __vec3_size_check(expr) vec3SizeCheck(expr)
#define __vec4_size_check(expr) vec4SizeCheck(expr)
#define __mat3_size_check(expr) mat3SizeCheck(expr)
#define __mat4_size_check(expr) mat4SizeCheck(expr)
#define __versor_size_check(expr) versorSizeCheck(expr)

#define __assert_ptr(expr) assert(expr)

#else

#define __vec2_size_check(expr) NULL
#define __vec3_size_check(expr) NULL
#define __vec4_size_check(expr) NULL
#define __mat3_size_check(expr) NULL
#define __mat4_size_check(expr) NULL
#define __versor_size_check(expr) NULL

#define __assert_ptr(expr) NULL

#endif

/*-----------------------------PRINT FUNCTIONS--------------------------------*/

void printVec2(vec2 v) {
  __vec2_size_check(v);
  struct Representation *vr = (struct Representation *)v;
  printf("[%.4f, %.4f]\n", vr->data[0], vr->data[1]);
}

void printVec3(vec3 v) {
  __vec3_size_check(v);
  struct Representation *vr = (struct Representation *)v;
  printf("[%.4f, %.4f, %.4f]\n", vr->data[0], vr->data[1], vr->data[2]);
}

void printVec4(vec4 v) {
  __vec4_size_check(v);
  struct Representation *vr = (struct Representation *)v;
  printf("[%.4f, %.4f, %.4f, %.4f]\n", vr->data[0], vr->data[1], vr->data[2],
         vr->data[3]);
}

void printMat3(mat3 m) {
  __mat3_size_check(m);
  struct Representation *mr = (struct Representation *)m;

  printf("[%.4f][%.4f][%.4f]\n", mr->data[0], mr->data[3], mr->data[6]);
  printf("[%.4f][%.4f][%.4f]\n", mr->data[1], mr->data[4], mr->data[7]);
  printf("[%.4f][%.4f][%.4f]\n", mr->data[2], mr->data[5], mr->data[8]);
}

void printMat4(mat4 m) {
  __mat4_size_check(m);
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
  __versor_size_check(q);
  struct Representation *qr = (struct Representation *)q;
  printf("[%.4f ,%.4f, %.4f, %.4f]\n", qr->data[0], qr->data[1], qr->data[2],
         qr->data[3]);
}

/*------------------------------VECTOR FUNCTIONS------------------------------*/

vec3 zeroVec3() {
  struct Representation *vc = representationNew(VEC3_SIZE);

  vc->data[0] = 0.0f;
  vc->data[1] = 0.0f;
  vc->data[2] = 0.0f;

  return (vec3)vc;
}

vec4 zeroVec4() {
  struct Representation *vc = representationNew(VEC4_SIZE);

  vc->data[0] = 0.0f;
  vc->data[1] = 0.0f;
  vc->data[2] = 0.0f;
  vc->data[3] = 0.0f;

  return (vec4)vc;
}

void vecFree(void *v) {
  __assert_ptr(v);

  struct Representation *vr = (struct Representation *)v;

  free(vr->data);
  free(vr);

  v = NULL;
}

vec3 vec3New(double x, double y, double z) {
  struct Representation *v = representationNew(VEC3_SIZE);
  v->data[0] = x;
  v->data[1] = y;
  v->data[2] = z;

  return (vec3)v;
}

double vec3Length(vec3 v) {
  __vec3_size_check(v);
  struct Representation *vr = (struct Representation *)v;

  return sqrt(vr->data[0] * vr->data[0] + vr->data[1] * vr->data[1] +
              vr->data[2] * vr->data[2]);
}

// squared length
double vec3LengthSquare(vec3 v) {
  __vec3_size_check(v);
  struct Representation *vr = (struct Representation *)v;

  return vr->data[0] * vr->data[0] + vr->data[1] * vr->data[1] +
         vr->data[2] * vr->data[2];
}

vec3 vec3Normalize(vec3 v) {
  __vec3_size_check(v);

  struct Representation *rv = representationNew(VEC3_SIZE);
  double l = vec3Length(v);

  struct Representation *vr = (struct Representation *)v;

  if (0.0f == l) {
    vr->data[0] = vr->data[1] = vr->data[2] = 0.0f;
  }

  rv->data[0] = vr->data[0] / l;
  rv->data[1] = vr->data[1] / l;
  rv->data[2] = vr->data[2] / l;

  return (vec3)rv;
}

vec3 vec3Add(vec3 first, vec3 second) {
  __vec3_size_check(first);
  __vec3_size_check(second);

  struct Representation *firstr = (struct Representation *)first;
  struct Representation *secondr = (struct Representation *)second;
  struct Representation *vc = representationNew(VEC3_SIZE);

  vc->data[0] = firstr->data[0] + secondr->data[0];
  vc->data[1] = firstr->data[1] + secondr->data[1];
  vc->data[2] = firstr->data[2] + secondr->data[2];

  return (vec3)vc;
}

/* void vec3AddOver(_FLOAT *first, const _FLOAT *second) { */
/*   __vec3_size_check(first); */
/*   __vec3_size_check(second); */
/*   first[0] += second[0]; */
/*   first[1] += second[1]; */
/*   first[2] += second[2]; */
/* } */

vec3 vec3Sub(vec3 first, vec3 second) {
  __vec3_size_check(first);
  __vec3_size_check(second);

  struct Representation *firstr = (struct Representation *)first;
  struct Representation *secondr = (struct Representation *)second;
  struct Representation *vc = representationNew(VEC3_SIZE);

  vc->data[0] = firstr->data[0] - secondr->data[0];
  vc->data[1] = firstr->data[1] - secondr->data[1];
  vc->data[2] = firstr->data[2] - secondr->data[2];

  return (vec3)vc;
}

/* void vec3SubOver(_FLOAT *first, const _FLOAT *second) { */
/*   __vec3_size_check(first); */
/*   __vec3_size_check(second); */
/*   first[0] -= second[0]; */
/*   first[1] -= second[1]; */
/*   first[2] -= second[2]; */
/* } */

vec3 vec3AddFloat(vec3 v, double num) {
  __vec3_size_check(v);

  struct Representation *vr = (struct Representation *)v;
  struct Representation *vc = representationNew(VEC3_SIZE);

  vc->data[0] = vr->data[0] + num;
  vc->data[1] = vr->data[1] + num;
  vc->data[2] = vr->data[2] + num;

  return (vec3)vc;
}

/* void vec3AddFloatOver(_FLOAT *v, _FLOAT num) { */
/*   __vec3_size_check(v); */
/*   _FLOAT *vc = zeroVec3(); */
/*   vc[0] += num; */
/*   vc[1] += num; */
/*   vc[2] += num; */
/* } */

vec3 vec3SubFloat(vec3 v, double num) {
  __vec3_size_check(v);

  struct Representation *vr = (struct Representation *)v;
  struct Representation *vc = representationNew(VEC3_SIZE);

  vc->data[0] = vr->data[0] - num;
  vc->data[1] = vr->data[1] - num;
  vc->data[2] = vr->data[2] - num;

  return (vec3)vc;
}

/* void vec3SubFloatOver(_FLOAT *v, _FLOAT num) { */
/*   __vec3_size_check(v); */
/*   _FLOAT *vc = zeroVec3(); */
/*   vc[0] -= num; */
/*   vc[1] -= num; */
/*   vc[2] -= num; */
/* } */

vec3 vec3MultFloat(vec3 v, double num) {
  __vec3_size_check(v);

  struct Representation *vr = (struct Representation *)v;
  struct Representation *vc = representationNew(VEC3_SIZE);

  vc->data[0] = vr->data[0] * num;
  vc->data[1] = vr->data[1] * num;
  vc->data[2] = vr->data[2] * num;

  return (vec3)vc;
}

vec3 vec3DevFloat(vec3 v, double num) {
  __vec3_size_check(v);
  assert(num != 0.0f);

  struct Representation *vr = (struct Representation *)v;
  struct Representation *vc = representationNew(VEC3_SIZE);

  vc->data[0] = vr->data[0] / num;
  vc->data[1] = vr->data[1] / num;
  vc->data[2] = vr->data[2] / num;

  return (vec3)vc;
}

/* void vec3MultFloatOver(_FLOAT *v, _FLOAT num) { */
/*   __vec3_size_check(v); */

/*   _FLOAT *vc = zeroVec3(); */

/*   vc[0] *= num; */
/*   vc[1] *= num; */
/*   vc[2] *= num; */
/* } */

/* void vec3DevFloatOver(_FLOAT *v, _FLOAT num) { */
/*   __vec3_size_check(v); */
/*   assert(num); */
/*   _FLOAT *vc = zeroVec3(); */
/*   vc[0] /= num; */
/*   vc[1] /= num;  */
/*   vc[2] /= num; */
/* } */

vec3 vec3Copy(vec3 source) {
  __vec3_size_check(source);

  struct Representation *sourcer = (struct Representation *)source;
  struct Representation *v = representationNew(VEC3_SIZE);

  v->data[0] = sourcer->data[0];
  v->data[1] = sourcer->data[1];
  v->data[2] = sourcer->data[2];

  return (vec3)v;
}

double vec3Dot(vec3 a, vec3 b) {
  __vec3_size_check(a);
  __vec3_size_check(b);

  struct Representation *ar = (struct Representation *)a;
  struct Representation *br = (struct Representation *)b;

  return ar->data[0] * br->data[0] + ar->data[1] * br->data[1] +
         ar->data[2] * br->data[2];
}

vec3 vec3Cross(vec3 a, vec3 b) {
  __vec3_size_check(a);
  __vec3_size_check(b);

  struct Representation *ar = (struct Representation *)a;
  struct Representation *br = (struct Representation *)b;

  struct Representation *v = representationNew(VEC3_SIZE);

  v->data[0] = ar->data[1] * br->data[2] - ar->data[2] * br->data[1];
  v->data[1] = ar->data[2] * br->data[0] - ar->data[0] * br->data[2];
  v->data[2] = ar->data[0] * br->data[1] - ar->data[1] * br->data[0];

  return (vec3)v;
}

double distanceSquared(vec3 from, vec3 to) {
  __vec3_size_check(from);
  __vec3_size_check(to);

  struct Representation *fromr = (struct Representation *)from;
  struct Representation *tor = (struct Representation *)to;

  double x = (tor->data[0] - fromr->data[0]) * (tor->data[0] - fromr->data[0]);
  double y = (tor->data[1] - fromr->data[1]) * (tor->data[1] - fromr->data[1]);
  double z = (tor->data[2] - fromr->data[2]) * (tor->data[2] - fromr->data[2]);

  return x + y + z;
}

double distance(vec3 from, vec3 to) {
  __vec3_size_check(from);
  __vec3_size_check(to);

  struct Representation *fromr = (struct Representation *)from;
  struct Representation *tor = (struct Representation *)to;

  double x = (tor->data[0] - fromr->data[0]) * (tor->data[0] - fromr->data[0]);
  double y = (tor->data[1] - fromr->data[1]) * (tor->data[1] - fromr->data[1]);
  double z = (tor->data[2] - fromr->data[2]) * (tor->data[2] - fromr->data[2]);

  return sqrt(x + y + z);
}

//  converts an un-normalised direction into a heading in degrees
// Note: i suspect that the z is backwards here but i've used it in
// several places like this.

/* double directionToHeading(vec3 d) { */
/*   __vec3_size_check(d); */

/*   return atan2(-d[0], -d[2]) * ONE_RAD_IN_DEG; */
/* } */

/* vec3 headingToDirection(double degrees) { */
/*   double rad = degrees * ONE_DEG_IN_RAD; */
/*   vec3 vc = zeroVec3(); */

/*   vc->data[0] = -sinf(rad); */
/*   vc->data[1] = 0.0f; */
/*   vc->data[2] = -cosf(rad); */

/*   return vc; */
/* } */

/*-----------------------------MATRIX FUNCTIONS-------------------------------*/

mat3 zeroMat3() {
  struct Representation *mat = representationNew(MAT3_SIZE);

  for (unsigned int i = 0; i < MAT3_SIZE; i++) {
    mat->data[i] = 0.0f;
  }

  return (mat3)mat;
}

mat3 identityMat3() {
  struct Representation *mat = representationNew(MAT3_SIZE);

  mat->data[0] = 1.0f;
  mat->data[4] = 1.0f;
  mat->data[8] = 1.0f;

  return (mat3)mat;
}

mat4 zeroMat4() {
  struct Representation *mat = representationNew(MAT4_SIZE);

  for (unsigned int i = 0; i < MAT4_SIZE; i++) {
    mat->data[i] = 0.0f;
  }

  return (mat4)mat;
}

mat4 identityMat4() {
  struct Representation *mat = representationNew(MAT4_SIZE);

  mat->data[0] = 1.0f;
  mat->data[5] = 1.0f;
  mat->data[10] = 1.0f;
  mat->data[15] = 1.0f;

  return (mat4)mat;

  // return mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
  // 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

void mat4ComponentsAssign(mat4 target, mat4 source) {
  __mat4_size_check(target);
  __mat4_size_check(source);

  struct Representation *targetr = (struct Representation *)target;
  struct Representation *sourcer = (struct Representation *)source;

  for (int i = 0; i < MAT4_SIZE; i++) {
    targetr->data[i] = sourcer->data[i];
  }
}

void matFree(void *m) {
  __assert_ptr(m);

  struct Representation *mr = (struct Representation *)m;
  free(mr->data);
  free(m);

  m = NULL;
}

/* mat4 array layout
 0  4  8 12
 1  5  9 13
 2  6 10 14
 3  7 11 15
*/

vec4 xmat4MulVec4(mat4 m, vec4 v) {
  // 0x + 4y + 8z + 12w

  __mat4_size_check(m);
  __vec4_size_check(v);

  struct Representation *mr = (struct Representation *)m;
  struct Representation *vr = (struct Representation *)v;

  struct Representation *vc = representationNew(VEC4_SIZE);

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
  __mat4_size_check(first);
  __mat4_size_check(second);

  struct Representation *firstr = (struct Representation *)first;
  struct Representation *secondr = (struct Representation *)second;

  struct Representation *mat = representationNew(MAT4_SIZE);
  unsigned int r_index = 0;

  for (unsigned int col = 0; col < 4; col++) {
    for (unsigned int row = 0; row < 4; row++) {
      double sum = 0.0f;

      for (int i = 0; i < 4; i++) {
        // first * second is not equal to second * first
        // in this case, we use rows in first mat4 to multiply columns in the
        // seconds mat4

        sum += firstr->data[i + col * 4] * secondr->data[row + i * 4];
      }

      mat->data[r_index] = sum;
      r_index++;
    }
  }

  return (mat4)mat;
}

mat4 mat4Copy(mat4 m) {
  __mat4_size_check(m);

  struct Representation *mr = (struct Representation *)m;
  struct Representation *mat = representationNew(MAT4_SIZE);

  for (unsigned int i = 0; i < MAT4_SIZE; i++) {
    mat->data[i] = mr->data[i];
  }

  return (mat4)mat;
}

double determinant(mat4 m) {
  __mat4_size_check(m);

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
  __mat4_size_check(m);

  double det = determinant(m);
  // there is no inverse if determinant is zero

  if (0.0f == det) {
    printf("WARNING. matrix has no determinant. can not be inverted\n");
    return m;
  }

  double inv_det = 1.0f / det;

  struct Representation *mr = (struct Representation *)m;
  struct Representation *mat = representationNew(MAT4_SIZE);

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
  __mat4_size_check(m);

  struct Representation *mr = (struct Representation *)m;
  struct Representation *mat = representationNew(MAT4_SIZE);

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
  __mat4_size_check(m);
  __vec3_size_check(v);

  struct Representation *vr = (struct Representation *)v;
  struct Representation *mat = representationNew(MAT4_SIZE);

  mat->data[12] = vr->data[0];
  mat->data[13] = vr->data[1];
  mat->data[14] = vr->data[2];

  mat4 rm = mat4MulMat4((mat4)mat, m);

  matFree(mat);
  return rm;
}

// rotate around x axis by an angle in degrees
mat4 rotateXdeg(mat4 m, double deg) {
  __mat4_size_check(m);

  // convert to radians
  double rad = deg * ONE_DEG_IN_RAD;

  struct Representation *mr = representationNew(MAT4_SIZE);

  mr->data[5] = cos(rad);
  mr->data[9] = -sin(rad);
  mr->data[6] = sin(rad);
  mr->data[10] = cos(rad);

  mat4 rm = mat4MulMat4((mat4)mr, m);

  matFree(mr);
  return rm;
}

// rotate around y axis by an angle in degrees
mat4 rotateYdeg(mat4 m, double deg) {
  __mat4_size_check(m);

  // convert to radians
  double rad = deg * ONE_DEG_IN_RAD;

  struct Representation *mr = representationNew(MAT4_SIZE);

  mr->data[0] = cos(rad);
  mr->data[8] = sin(rad);
  mr->data[2] = -sin(rad);
  mr->data[10] = cos(rad);

  mat4 rm = mat4MulMat4((mat4)mr, m);
  matFree(mr);

  return rm;
}

// rotate around z axis by an angle in degrees
mat4 rotateZdeg(mat4 m, double deg) {
  __mat4_size_check(m);

  // convert to radians
  double rad = deg * ONE_DEG_IN_RAD;

  struct Representation *mr = representationNew(MAT4_SIZE);

  mr->data[0] = cos(rad);
  mr->data[4] = -sin(rad);
  mr->data[1] = sin(rad);
  mr->data[5] = cos(rad);

  mat4 rm = mat4MulMat4((mat4)mr, m);
  matFree(mr);

  return rm;
}

// scale a matrix by [x, y, z]
mat4 scale(mat4 m, vec3 v) {
  __mat4_size_check(m);
  __vec3_size_check(v);

  struct Representation *vr = (struct Representation *)v;
  struct Representation *ar = representationNew(MAT4_SIZE);

  ar->data[0] = vr->data[0];
  ar->data[5] = vr->data[1];
  ar->data[10] = vr->data[2];

  mat4 rm = mat4MulMat4((mat4)ar, m);
  matFree(ar);

  return rm;
}

/*-----------------------VIRTUAL CAMERA MATRIX FUNCTIONS----------------------*/

// returns a view matrix using the opengl lookAt style. COLUMN ORDER.
mat4 lookAt(vec3 camPos, vec3 tarPos, vec3 up) {
  __vec3_size_check(camPos);
  __vec3_size_check(tarPos);
  __vec3_size_check(up);

  struct Representation *camPosr = (struct Representation *)camPos;
  //  struct Representation *tarPosr = (struct Representation *)tarPos;
  //  struct Representation *upr = (struct Representation *)up;

  // inverse translation to make camera position at world origin
  mat4 p = identityMat4();
  vec3 camDir =
      vec3New(-camPosr->data[0], -camPosr->data[1], -camPosr->data[2]);
  mat4 q = translate(p, camDir);

  // distance vector
  vec3 d = vec3Sub(tarPos, camPos);

  // forward vector
  vec3 f = vec3Normalize(d);
  struct Representation *fr = (struct Representation *)f;

  // right vector
  vec3 r = vec3Cross(f, up);
  vec3 nr = vec3Normalize(r);
  struct Representation *nrr = (struct Representation *)nr;

  // real up vector
  vec3 u = vec3Cross(nr, f);
  vec3 nu = vec3Normalize(u);
  struct Representation *nur = (struct Representation *)nu;

  struct Representation *ori = (struct Representation *)identityMat4();
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
  double fov_rad = fovy * ONE_DEG_IN_RAD;
  double range = tan(fov_rad / 2.0f) * near;
  double sx = (2.0f * near) / (range * aspect + range * aspect);
  double sy = near / range;
  double sz = -(far + near) / (far - near);
  double pz = -(2.0f * far * near) / (far - near);

  struct Representation *mr = representationNew(MAT4_SIZE);
  //  _FLOAT *m = zeroMat4(); // make sure bottom-right corner is zero
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

  for (unsigned int i = 0; i < VERSOR_SIZE; i++) {
    ver->data[i] = 0.0f;
  }

  return (versor)ver;
}

void versorFree(void *ve) {
  __assert_ptr(ve);

  struct Representation *ver = (struct Representation *)ve;

  free(ver->data);
  free(ver);

  ve = NULL;
}

versor versorDevFloat(versor ve, double num) {
  __versor_size_check(ve);
  assert(num != 0.0f);

  struct Representation *ver = (struct Representation *)ve;
  struct Representation *re = representationNew(VERSOR_SIZE);

  re->data[0] = ver->data[0] / num;
  re->data[1] = ver->data[1] / num;
  re->data[2] = ver->data[2] / num;
  re->data[3] = ver->data[3] / num;

  return (versor)re;
}

versor versorMulFloat(versor ve, double num) {
  __versor_size_check(ve);

  struct Representation *ver = (struct Representation *)ve;
  struct Representation *re = representationNew(VERSOR_SIZE);

  re->data[0] = ver->data[0] * num;
  re->data[1] = ver->data[1] * num;
  re->data[2] = ver->data[2] * num;
  re->data[3] = ver->data[3] * num;

  return (versor)re;
}

versor versorNormalize(versor q) {
  __versor_size_check(q);

  struct Representation *qr = (struct Representation *)q;

  // norm(q) = q / magnitude (q)
  // magnitude (q) = sqrt (w*w + x*x...)
  // only compute sqrt if interior sum != 1.0

  double sum = qr->data[0] * qr->data[0] + qr->data[1] * qr->data[1] +
               qr->data[2] * qr->data[2] + qr->data[3] * qr->data[3];

  // Note: floats have min 6 digits of precision

  const double thresh = 0.0001f;
  if (fabs(1.0f - sum) < thresh) {
    return (versor)qr;
  }

  double mag = sqrt(sum);
  versor rve = versorDevFloat((versor)qr, mag);

  return rve;
}

versor versorMulVersor(versor first, versor second) {
  __versor_size_check(first);
  __versor_size_check(second);

  struct Representation *firstr = (struct Representation *)first;
  struct Representation *secondr = (struct Representation *)second;
  struct Representation *re = representationNew(VERSOR_SIZE);

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
  versorFree((versor)re);

  return rve;
}

versor versorAdd(versor first, versor second) {
  __versor_size_check(first);
  __versor_size_check(second);

  struct Representation *firstr = (struct Representation *)first;
  struct Representation *secondr = (struct Representation *)second;
  struct Representation *re = representationNew(VERSOR_SIZE);

  re->data[0] = firstr->data[0] + secondr->data[0];
  re->data[1] = firstr->data[1] + secondr->data[1];
  re->data[2] = firstr->data[2] + secondr->data[2];
  re->data[3] = firstr->data[3] + secondr->data[3];

  // re-normalise in case of mangling
  versor rve = versorNormalize((versor)re);
  versorFree((versor)re);
  return rve;
}

versor quatFromAxisRad(double radians, double x, double y, double z) {
  struct Representation *re = representationNew(VERSOR_SIZE);
  re->data[0] = cos(radians / 2.0);
  re->data[1] = sin(radians / 2.0) * x;
  re->data[2] = sin(radians / 2.0) * y;
  re->data[3] = sin(radians / 2.0) * z;
  return (versor)re;
}

versor quatFromAxisDeg(double degrees, double x, double y, double z) {
  return quatFromAxisRad(ONE_DEG_IN_RAD * degrees, x, y, z);
}

mat4 quatToMat4(versor q) {
  __versor_size_check(q);
  struct Representation *qr = (struct Representation *)q;

  double w = qr->data[0];
  double x = qr->data[1];
  double y = qr->data[2];
  double z = qr->data[3];

  struct Representation *m = representationNew(MAT4_SIZE);

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
  __versor_size_check(q);
  __versor_size_check(r);

  struct Representation *qr = (struct Representation *)q;
  struct Representation *rr = (struct Representation *)r;

  return qr->data[0] * rr->data[0] + qr->data[1] * rr->data[1] +
         qr->data[2] * rr->data[2] + qr->data[3] * rr->data[3];
}

versor versorSlerp(versor q, versor r, double t) {
  __versor_size_check(q);
  __versor_size_check(r);

  struct Representation *qr = (struct Representation *)q;
  struct Representation *rr = (struct Representation *)r;

  // angle between q0-q1
  double cos_half_theta = versorDot((versor)qr, (versor)rr);

  // if dot product is negative then one quaternion should be negated, to make
  // it take the short way around, rather than the long way

  // we had to recalculate the d.p. after this
  if (cos_half_theta < 0.0f) {
    for (unsigned int i = 0; i < 4; i++) {
      qr->data[i] *= -1.0f;
    }

    cos_half_theta = versorDot((versor)qr, (versor)rr);
  }
  // if qa=qb or qa=-qb then theta = 0 and we can return qa
  if (fabs(cos_half_theta) >= 1.0f) {
    return (versor)qr;
  }
  // Calculate temporary values
  double sin_half_theta = sqrt(1.0f - cos_half_theta * cos_half_theta);
  // if theta = 180 degrees then result is not fully defined
  // we could rotate around any axis normal to qa or qb
  struct Representation *re = representationNew(VERSOR_SIZE);

  if (fabs(sin_half_theta) < 0.001f) {
    for (unsigned int i = 0; i < 4; i++) {
      re->data[i] = (1.0f - t) * qr->data[i] + t * rr->data[i];
    }
    return (versor)re;
  }

  double half_theta = acos(cos_half_theta);
  double a = sin((1.0f - t) * half_theta) / sin_half_theta;
  double b = sin(t * half_theta) / sin_half_theta;

  for (unsigned int i = 0; i < 4; i++) {
    re->data[i] = qr->data[i] * a + rr->data[i] * b;
  }
  return (versor)re;
}
