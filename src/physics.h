//
// Created by Windows Vista on 8/9/2021.
//

#ifndef UNTITLED_FPS_PHYSICS_H
#include "vmmath.h"

/*
typedef struct Sphere {
    vec3 position;
    f32 radius;
} Sphere;
*/

vec3 closest_point_on_line_segment(vec3 A, vec3 B, vec3 point) {
    vec3 AB = vec3_sub_vec3(B, A);
    f32 t = vec3_dot(vec3_sub_vec3(point, A), AB) / vec3_dot(AB, AB);
    //return vec3_mul_vec3(vec3_add_f32(A, f32_saturate(t)), AB);
    return vec3_add_vec3(A, vec3_mul_f32(AB, fminf(fmaxf(t, 0.0f), 1.0f)));
}

//TODO(sean): get this to work with vertex - index data
//TODO(sean): move this to just use re-duped vertex data
b32 sphere_collides_with_plane(vec3 A, vec3 B, vec3 C, vec3 P, f32 r, vec3* N, f32* pen_depth) {
    b32 tA, tB, tC;
    tA = (r * r) > ((P.x - A.x) * (P.x - A.x)) + ((P.y - A.y) * (P.y - A.y)) + ((P.z - A.z) * (P.z - A.z));
    tB = (r * r) > ((P.x - B.x) * (P.x - B.x)) + ((P.y - B.y) * (P.y - B.y)) + ((P.z - B.z) * (P.z - B.z));
    tC = (r * r) > ((P.x - C.x) * (P.x - C.x)) + ((P.y - C.y) * (P.y - C.y)) + ((P.z - C.z) * (P.z - C.z));

    if(tA == true) {
        vec3 n = {{P.x - A.x, P.y - A.y, P.z - A.z}};
        *N = vec3_norm(n);
        return true;
    } else if (tB == true) {
        vec3 n = {{P.x - B.x, P.y - B.y, P.z - B.z}};
        *N = vec3_norm(n);
        return true;
    } else if (tC == true) {
        vec3 n = {{P.x - C.x, P.y - C.y, P.z - C.z}};
        *N = vec3_norm(n);
        return true;
    }

    *N = vec3_norm(vec3_cross(vec3_sub_vec3(B, A), vec3_sub_vec3(C, A)));

    vec3 edge1, edge2, h, s, q;
    f32 a, f, u, v;
    edge1 = vec3_sub_vec3(B, A);
    edge2 = vec3_sub_vec3(C, A);
    h = vec3_cross(*N, edge2);
    a = vec3_dot(edge1, h);
    f = 1.0/a;
    s = vec3_sub_vec3(P, A);
    u = f * vec3_dot(s, h);
    if(u < 0.0 || u > 1.0) { return false; }
    q = vec3_cross(s, edge1);
    v = f * vec3_dot(*N, q);
    if(v < 0.0 || (u + v) > 1.0) { return false; }

    f32 t = f * vec3_dot(edge2, q);
    if((t*t) < (r*r)) {
        return true;
    } else {
        return false;
    }
}

#define UNTITLED_FPS_PHYSICS_H

#endif //UNTITLED_FPS_PHYSICS_H