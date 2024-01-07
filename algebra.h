#pragma once
#include <math.h>
#define PI 3.1415962

struct mat4 {
	float entries[16];
};

struct vec3 {
	float entries[3];
};

//function which produces a translation matrix
mat4 create_matrix_transform(vec3 translation);

//funciton to produce rotation in z axis
mat4 create_z_rotation(float angle);

//doing both
mat4 create_model_transform(vec3 pos, float angle);

//using view transformation
mat4 create_look_at(vec3 from, vec3 to);

float dot(vec3 u, vec3 v);

vec3 normalize(vec3 u);

vec3 cross(vec3 u, vec3 v);

//creating prespective projection transformation
mat4 create_prespective_projection(
	float fovy, float aspect, float near, float far
);
