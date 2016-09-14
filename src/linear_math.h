#ifndef LINEAR_MATH_H
#define LINEAR_MATH_H

#include <stdio.h>
#include <math.h>
//#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

//#include "debug.h"

#include "general_helper.h"

typedef void *vec2;
typedef void *vec3;
typedef void *vec4;
typedef void *mat3;
typedef void *mat4;
typedef void *versor;

/*---------------------------PRINT FUNCTIONS------------------------------*/

void printVec2(vec2 v);
void printVec3(vec3 v);
void printVec4(vec4 v);
void printMat3(mat3 m);
void printMat4(mat4 m);
void printVersor(versor q);

/*----------------------------VECTOR FUNCTIONS----------------------------*/

vec3 zeroVec3();

vec4 zeroVec4();

void vecFree(void *v);

vec3 vec3New(double x, double y, double z);

double vec3Length(vec3 v);

double vec3LengthSquare(vec3 v);

vec3 vec3Normalize(vec3 v);

vec3 vec3Add(vec3 first, vec3 second);

// void vec3AddOver(vec3 first, vec3 second);

vec3 vec3Sub(vec3 first, vec3 second);

// void vec3SubOver(_FLOAT *first, const _FLOAT *second);

vec3 vec3AddFloat(vec3 v, double num);

// void vec3AddFloatOver(vec3 v, double num);

vec3 vec3SubFloat(vec3 v, double num);

// void vec3SubFloatOver(_FLOAT *v, double num);

vec3 vec3MultFloat(vec3 v, double num);

vec3 vec3DevFloat(vec3 v, double num);

// void vec3MultFloatOver(_FLOAT *v, double num);
// void vec3DevFloatOver(_FLOAT *v, double num);

vec3 vec3Copy(vec3 source);

double vec3Dot(vec3 a, vec3 b);

vec3 vec3Cross(vec3 a, vec3 b);

double distanceSquared(vec3 from, vec3 to);

double distance(vec3 from, vec3 to);

double directionToHeading(vec3 d);

vec3 headingToDirection(double degrees);

/*-----------------------------MATRIX FUNCTIONS---------------------------*/

mat3 zeroMat3();

mat3 identityMat3();

mat4 zeroMat4();

mat4 identityMat4();

void mat4ComponentsAssign(mat4 target, mat4 source);

void matFree(void *m);

vec4 mat4MulVec4(mat4 m, vec4 v);

mat4 mat4MulMat4(mat4 first, mat4 second);

mat4 mat4Copy(mat4 m);

double determinant(mat4 m);

mat4 inverse(mat4 m);

mat4 transpose(mat4 m);

/*--------------------------AFFINE MATRIX FUNCTIONS-----------------------*/

mat4 translate(mat4 m, vec3 v);

mat4 rotateXdeg(mat4 m, double deg);

mat4 rotateYdeg(mat4 m, double deg);

mat4 rotateZdeg(mat4 m, double deg);

mat4 scale(mat4 m, vec3 v);

/*----------------------VIRTUAL CAMERA MATRIX FUNCTIONS-------------------*/

mat4 lookAt(vec3 camPos, vec3 tarPos, vec3 up);

mat4 perspective(double fovy, double aspect, double near, double far);

/*--------------------------HAMILTON FUNCTION-----------------------------*/

versor zeroVersor();

void versorFree(void *ve);

versor versorDevFloat(versor ve, double num);

versor versorMulFloat(versor ve, double num);

versor versorNormalize(versor q);

versor versorMulVersor(versor first, versor second);

versor versorAdd(versor first, versor second);

versor quatFromAxisRad(double radians, double x, double y, double z);

versor quatFromAxisDeg(double degrees, double x, double y, double z);

mat4 quatToMat4(versor q);

double versorDot(versor q, versor r);

versor versorSlerp(versor q, versor r, double t);

#endif
