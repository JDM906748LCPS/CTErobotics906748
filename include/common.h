#include "vex.h"
using namespace vex;

#include "stdio.h"
#include "stdlib.h"
#include "eyecast.h"
#include "math.h"

#define PI 3.1415926535897932384626 // high accuracy value of pi
#define WRAD 2.0                    // wheel radius
#define WCIRC (2.0 * PI * WRAD)     // wheel circumference
#define WDIST 11.59200              // wheel distance
#define ADIST 6.5                   // axle distance

//#define PIVOTO (ADIST/2.0)        // pivot offset
#define PIVOTS (ADIST/(2.0*WCIRC))  // derived pivot shift value
//#define PIVOTC (PI*WDIST)         // pivot circumference
#define PIVOTM (WDIST/(2.0*WRAD))   // derived pivot multiplier value

#define RMULT 1.0
#define OMULT 0.0
#define DMULT 1.0

#define WPMULT 0.5*WDIST

extern float posX;
extern float posY;
extern float posH;
extern float wlX;
extern float wlY;
extern float wrX;
extern float wrY;

float lerp(float x, float y, float t);

float dsin(float theta);
float dcos(float theta);
float datan2(float y, float x);

void updatePoints();
void posFd(float x);
void posPivot(float x,float y,float t);

void draw(int x0i, int y0i, int x1i, int y1i);
void GG();

void awaitFinish(brakeType x);
void awaitFinish();

void setDriveTorque(float x);
void setDriveStopping(brakeType x);

void setArmTorque(float x);
void setArmTurns(float x);
void setArm(float x, float y);

void setClawTorque(float x);
void setClawTurns(float x);
void setClaw(float x, float y);

void tankMoveD(float lxi, float rxi, bool wait);
void tankMoveT(float lxi, float rxi, bool wait);
void tankMoveD(float lx, float rx);
void tankMoveT(float lx, float rx);

void lt(float theta, bool wait);
void rt(float theta, bool wait);
void lt(float theta);
void rt(float theta);

void pivotL(float theta, bool wait);
void pivotR(float theta, bool wait);
void pivotL(float theta);
void pivotR(float theta);

void fd();
void fd(float dist, bool wait);
void fd(float dist);

void bk();
void bk(float dist, bool wait);
void bk(float dist);

void halt(brakeType mode);
void halt();