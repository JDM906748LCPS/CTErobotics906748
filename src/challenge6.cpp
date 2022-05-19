/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\906748                                           */
/*    Created:      Wed Mar 02 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LMotor               motor         10
// RMotor               motor         1
// Controller1          controller
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "challenges.h"
#include "common.h"
float W=60.0,H=120.0;
// ballX[] = {12.0,30.0,48.0};
// ballY[] = {24.0,60.0,96.0};
float depotX = 12.0, depotY = 108.0;
float homeX = 60.0-(WDIST*0.75), homeY = ADIST*1.5;

float px = homeX, py = homeY, ph = 90.0;

void move(float x, float y, bool wait) {
  float dx, dy, a, r;
  Brain.Screen.newLine();
  Brain.Screen.print("goto %5.3f %5.3f",x,y);
  dx = x-px;
  dy = y-py;
  a = fmod((datan2(dy,dx)-ph+180.0),360.0)-180.0;
  r = sqrt((dx*dx)+(dy*dy));
  ph=a;
  pivotL(a);
  fd(r, wait);
  px+=r*dcos(ph);
  py+=r*dsin(ph);
}
void move(float x, float y) {move(x,y,true);}

void qfd(float x, bool wait) {
  fd(x, wait);
  px+=x*dcos(ph);
  py+=x*dsin(ph);
}

void qbk(float x, bool wait) {
  bk(x,wait);
  px-=x*dcos(ph);
  py-=x*dsin(ph);
}

void qlt(float x, bool wait) {
  pivotL(x,wait);
  ph+=x;
}

void qrt(float x, bool wait) {
  pivotR(x,wait);
  ph-=x;
}

void qfd(float x) {qfd(x,true);}
void qbk(float x) {qbk(x,true);}
void qlt(float x) {qlt(x,true);}
void qrt(float x) {qrt(x,true);}

// depot Y is 6 revolutions from home pos
// depot Y is @ 75.3982236862 in. from home
// depot Y is 6.5*1.5+75..., = 85.148223 in.
void prepGrab() {
  setArm(0.000,0.500);
  setClaw(-0.500,0.125);
}

void grab() {
  setDriveTorque(0.125);
  qbk(0.250*WCIRC);
  setArm(0.400,0.500);
  qfd(0.100*WCIRC);
  setClaw(0.000,0.125);
  setArm(1.000,1.000);
  qbk(0.350*WCIRC);
}

void deposit() {
  setDriveStopping(brake);
  move(px,24.000*(PI+0.40625),false);
  awaitFinish();
  setArm(0.600,0.500);
  setClaw(-0.500,0.500);
  qbk(1.000*WCIRC);
}

void ch6() {
  move(12.0,12.0);
  prepGrab();
  move(12.0,24.0);
  grab();
  move(30.0,24.0);
  move(12.0,60.0);
  deposit();
  move(26.0,72.0);
  prepGrab();
  move(30.0,60.0);
  grab();
  move(12.0,60.0);
  deposit();
  move(12.0,65.0);
  move(48.0,65.0);
  prepGrab();
  move(48.0,96.0);
  grab();
  move(48.0,65.0);
  move(12.0,65.0);
  deposit();
}
