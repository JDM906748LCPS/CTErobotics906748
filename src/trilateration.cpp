#include "math.h"
#include "trilateration.h"
float *add(float *p1, float *p2) {
  static float o[3] = {(*(p1 + 0)) + (*(p2 + 0)), (*(p1 + 1)) + (*(p2 + 1)),
                       (*(p1 + 2)) + (*(p2 + 2))};
  return o;
}
float *sub(float *p1, float *p2) {
  static float o[3] = {(*(p1 + 0)) - (*(p2 + 0)), (*(p1 + 1)) - (*(p2 + 1)),
                       (*(p1 + 2)) - (*(p2 + 2))};
  return o;
}
float *mult(float *p, float x) {
  static float o[3] = {(*(p+0))*x,(*(p+1))*x,(*(p+2))*x};
  return o;
}
float *div(float *p, float x) {
  static float o[3] = {(*(p+0))/x,(*(p+1))/x,(*(p+2))/x};
  return o;
}
float *vmult(float *p1, float *p2) {
  static float o[3] = {(*(p1+0))*(*(p2+0)),(*(p1+1))*(*(p2+1)),(*(p1+2))*(*(p2+2))};
  return o;
}
float dot(float *p1, float *p2) {
  return ((*(p1 + 0)) * (*(p2 + 0))) + ((*(p1 + 1)) * (*(p2 + 1))) +
         ((*(p1 + 2)) * (*(p2 + 2)));
}
float* cross(float *p1, float *p2) {
  static float o[3] = {((*(p1+1))*(*(p2+2)))-((*(p1+2))*(*(p2+1))),((*(p1+2))*(*(p2+0)))-((*(p1+0))*(*(p2+2))),((*(p1+0))*(*(p2+1)))-((*(p1+1))*(*(p2+0)))};
  return o;
}

float magSq(float *p) {
  return ((*(p + 0)) * (*(p + 0))) + ((*(p + 1)) * (*(p + 1))) +
         ((*(p + 2)) * (*(p + 2)));
}
float mag(float *p) { return sqrt(magSq(p)); }
float *norm(float *p) {
  float r = mag(p);
  static float o[3] = {*(p + 0) / r, *(p + 1) / r, *(p + 2) / r};
  return o;
}
float* locate3D(float* p1, float r1, float* p2, float r2, float* p3, float r3, float* p4, float r4) {
  float tmp0[3] = {(*(p2+0))-(*(p1+0)),(*(p2+1))-(*(p1+1)),(*(p2+2))-(*(p1+2))};
  float* e_x = norm(tmp0);
  float i = dot(e_x,sub(p3,p1));
  float* e_y = norm(sub(sub(p3,p1),mult(e_x,i)));
  float* e_z = cross(e_x,e_y);
  float d = mag(sub(p2,p1));
  float j = dot(e_y,sub(p3,p1));
  float x = ((r1*r1)-(r2*r2)+(d*d))/(2*d);
  float y = (((r1*r1)-(r3*r3)+(i*i)+(j*j)-(2*i*x))/(2*j));
  float z1 = sqrt((r1*r1)-(x*x)-(y*y));
  float z2 = -z1;
  float* ans1 = add(add(p1,mult(e_x,x)),add(mult(e_y,y),mult(e_z,z1)));
  float* ans2 = add(add(p1,mult(e_x,x)),add(mult(e_y,y),mult(e_z,z2)));
  float dist1 = mag(sub(p4,ans1));
  float dist2 = mag(sub(p4,ans2));
  if (fabs(r4-dist1)<fabs(r4-dist2)) {
    static float* o = ans1;
    return o;
  } else {
    static float* o = ans2;
    return o;
  }
}