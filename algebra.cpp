#include "algebra.h"

mat4 create_matrix_transform(vec3 translation)
{
    mat4 matrix;

    matrix.entries[0] = 1.0f;
    matrix.entries[1] = 0.0f;
    matrix.entries[2] = 0.0f;
    matrix.entries[3] = 0.0f;

    matrix.entries[4] = 0.0f;
    matrix.entries[5] = 1.0f;
    matrix.entries[6] = 0.0f;
    matrix.entries[7] = 0.0f;

    matrix.entries[8] = 0.0f;
    matrix.entries[9] = 0.0f;
    matrix.entries[10] = 1.0f;
    matrix.entries[11] = 0.0f;

    matrix.entries[12] = translation.entries[0];
    matrix.entries[13] = translation.entries[1];
    matrix.entries[14] = translation.entries[2];
    matrix.entries[15] = 1.0f;

    return matrix;
}

mat4 create_z_rotation(float angle)
{
    angle *= PI / 180;
    mat4 matrix;


    matrix.entries[0] = cos(angle);
    matrix.entries[1] = sin(angle);
    matrix.entries[2] = 0.0f;
    matrix.entries[3] = 0.0f;

    matrix.entries[4] = -sin(angle);
    matrix.entries[5] = cos(angle);
    matrix.entries[6] = 0.0f;
    matrix.entries[7] = 0.0f;

    matrix.entries[8] = 0.0f;
    matrix.entries[9] = 0.0f;
    matrix.entries[10] = 1.0f;
    matrix.entries[11] = 0.0f;

    matrix.entries[12] = 0.0f;
    matrix.entries[13] = 0.0f;
    matrix.entries[14] = 0.0f;
    matrix.entries[15] = 1.0f;

    return matrix;
}

mat4 create_model_transform(vec3 translation, float angle)
{
    mat4 matrix;
    angle *= PI / 180;

    matrix.entries[0] = cos(angle);
    matrix.entries[1] = sin(angle);
    matrix.entries[2] = 0.0f;
    matrix.entries[3] = 0.0f;

    matrix.entries[4] = -sin(angle);
    matrix.entries[5] = cos(angle);
    matrix.entries[6] = 0.0f;
    matrix.entries[7] = 0.0f;

    matrix.entries[8] = 0.0f;
    matrix.entries[9] = 0.0f;
    matrix.entries[10] = 1.0f;
    matrix.entries[11] = 0.0f;

    matrix.entries[12] = translation.entries[0];
    matrix.entries[13] = translation.entries[1];
    matrix.entries[14] = translation.entries[2];
    matrix.entries[15] = 1.0f;

    return matrix;
}

mat4 create_look_at(vec3 from, vec3 to)
{
    mat4 matrix;

    vec3 global_up = { 0.0f, 0.0f, 1.0f };

    //creating 'forward' vector (to - from)
    vec3 f = { to.entries[0] - from.entries[0],
            to.entries[1] - from.entries[1],
            to.entries[2] - from.entries[2]
    };

    f = normalize(f);

    //creating 'right' vector (forward (cross) up)
    vec3 r = normalize(cross(f, global_up));

    //creating 'up' vector (forward (cross) right)
    vec3 u = normalize(cross(r, f));

    //constructing the view transformation matrix:
    matrix.entries[0] = r.entries[0];
    matrix.entries[1] = u.entries[0];
    matrix.entries[2] = -f.entries[0];
    matrix.entries[3] = 0.0f;

    matrix.entries[4] = r.entries[1];
    matrix.entries[5] = u.entries[1];
    matrix.entries[6] = -f.entries[1];
    matrix.entries[7] = 0.0f;

    matrix.entries[8] = r.entries[2];
    matrix.entries[9] = u.entries[2];
    matrix.entries[10] = -f.entries[2];
    matrix.entries[11] = 0.0f;

    matrix.entries[12] = -dot(r,from);
    matrix.entries[13] = -dot(u,from);
    matrix.entries[14] = dot(f,from);
    matrix.entries[15] = 1.0f;

    return matrix;
}

float dot(vec3 u, vec3 v)
{
    return u.entries[0] * v.entries[0]+ u.entries[1] * v.entries[1]+ u.entries[2] * v.entries[2];
}

vec3 normalize(vec3 v)
{
    vec3 u;

    float magnitude = sqrt(dot(v, v));

    u.entries[0] = v.entries[0] / magnitude;
    u.entries[1] = v.entries[1] / magnitude;
    u.entries[2] = v.entries[2] / magnitude;

    return u;
}

vec3 cross(vec3 u, vec3 v)
{
    vec3 w;

    w.entries[0] = u.entries[1] * v.entries[2] - u.entries[2] * v.entries[1];
    w.entries[1] = -(u.entries[0] * v.entries[2] - u.entries[2] * v.entries[0]);
    w.entries[2] = u.entries[0] * v.entries[1] - u.entries[1] * v.entries[0];

    return w;
}

mat4 create_prespective_projection(float fovy, float aspect, float near, float far)
{
    mat4 matrix;
    fovy *= PI / 360.0f;
    float t = tan(fovy);
    float n = -near;
    float f = -far;
    matrix.entries[0] = 1 / (aspect * t);
    matrix.entries[1] = 0.0f;
    matrix.entries[2] = 0.0f;
    matrix.entries[3] = 0.0f;

    matrix.entries[4] = 0.0f;
    matrix.entries[5] = 1 / t;
    matrix.entries[6] =  0.0f;
    matrix.entries[7] =  0.0f;
                        
    matrix.entries[8]  = 0.0f;
    matrix.entries[9]  = 0.0f;
    matrix.entries[10] = -(n + f) / (n - f);
    matrix.entries[11] = -1.0f;

    matrix.entries[12] = 0.0f;
    matrix.entries[13] = 0.0f;
    matrix.entries[14] = 2*n*f/(n-f);
    matrix.entries[15] = 0.0f;
    return matrix;
}
