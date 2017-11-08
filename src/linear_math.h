#ifndef LINEAR_MATH_H
#define LINEAR_MATH_H

#include <math.h>
#include <stdio.h>
//#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

//#include "debug.h"

#include "general_helper.h"

typedef void *vec2;
typedef void *vec3;
typedef void *vec4;
typedef void *mat3;
typedef void *mat4;
typedef void *versor;

#define TAU 2.0f * M_PI
#define ONE_DEG_IN_RAD ((2.0f * M_PI) / 360.0f) // 0.017444444
#define ONE_RAD_IN_DEG (360.0f / (2.0f * M_PI)) // 57.2957795

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

float *vec3GetData(vec3 v);

size_t vec3GetSize(vec3 v);

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

float *mat3GetData(mat3 m);

size_t mat3GetSize(mat3 m);

mat4 zeroMat4();

mat4 identityMat4();

float *mat4GetData(mat4 m);

size_t mat4GetSize(mat4 m);

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

float *versorGetData(versor vr);

size_t versorGetSize(versor vr);

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
