#include "unitTests.h"

#include "vex.h"
using namespace vex;

#include "trilateration.h"

#include "math.h"

void testLoc(float x,float y,float z,float r1,float r2,float r3,float r4,float* p1,float* p2,float* p3,float* p4) {
  float* p = locate3D(p1,sqrt(r1),p2,sqrt(r2),p3,sqrt(r3),p4,sqrt(r4));
  float x0 = (*(p+0))-x;
  float y0 = (*(p+1))-y;
  float z0 = (*(p+2))-z;
  float e = sqrt((x0*x0)+(y0*y0)+(z0*z0));
  if (e>(1/4096)) {
    Brain.Screen.print("fail %1.0f %1.0f %1.0f err %f %f %f",x,y,z,x0,y0,z0);
    Brain.Screen.newLine();
  }
}
void testMag(float x,float y,float z,float r) {
  float p[3] = {x,y,z};
  float e = mag(p)-sqrt(r);
  if (e>(1/4096)) {
    Brain.Screen.print("fail %1.0f %1.0f %1.0f err %f",x,y,z,e);
    Brain.Screen.newLine();
  }
}
void testCross(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3) {

}
void tests() {
  static float p1[3] = {0,0,0};
  static float p2[3] = {1,0,0};
  static float p3[3] = {0,1,0};
  static float p4[3] = {0,0,1};
  testLoc(0,0,0,0,1,1,1,p1,p2,p3,p4);
  testLoc(0,0,1,1,2,2,0,p1,p2,p3,p4);
  testLoc(0,1,0,1,2,0,2,p1,p2,p3,p4);
  testLoc(0,1,1,2,3,1,1,p1,p2,p3,p4);
  testLoc(1,0,0,1,0,2,2,p1,p2,p3,p4);
  testLoc(1,0,1,2,1,3,1,p1,p2,p3,p4);
  testLoc(1,1,0,2,1,1,3,p1,p2,p3,p4);
  testLoc(1,1,1,3,2,2,2,p1,p2,p3,p4);
  testMag(0,0,0,0);
  testMag(0,0,1,1);
  testMag(0,1,0,1);
  testMag(0,1,1,2);
  testMag(1,0,0,1);
  testMag(1,0,1,2);
  testMag(1,1,0,2);
  testMag(1,1,1,3);
  float x0[] = {0,0,0,0,0,0,0,0,0,0,-1,-1,0,0,-1,-1,0,1,0,1,0,1,0,1,0,1,-1,0,0,1,-1,0,0,0,0,0,0,0,0,0,0,0,-1,-1,0,0,-1,-1,0,1,0,1,0,1,0,1,0,1,-1,0,0,1,-1,0};
  float y0[] = {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,1,0,1,0,0,-1,0,-1,0,-1,0,-1,0,-1,0,-1,1,0,1,0};
  float z0[] = {};
  for (int i = 0; i < 64; i++) {
    testCross(float((i>>5)&1),float((i>>4)&1),float((i>>3)&1),float((i>>2)&1),float((i>>1)&1),float((i>>0)&1),x0[i],y0[i],z0[i]);
  }
}