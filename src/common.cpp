#include "common.h"

float posX = 0;
float posY = 0;
float posH = 0;
float wlX = -WDIST/2;
float wlY = 0;
float wrX = WDIST/2;
float wrY = 0;

float dsin(float theta) {return sin(PI*theta/180);}
float dcos(float theta) {return cos(PI*theta/180);}
float datan2(float y,float x) {return 180*atan2(y,x)/PI;}
float lerp(float x, float y, float t) {return x+(t*(y-x));}

void updatePoints() {
  float sx=WPMULT*dsin(posH+90),sy=WPMULT*dcos(posH+90);
  wlX=posX-sx;
  wlY=posY-sy;
  wrX=posX+sx;
  wrY=posY+sy;
}

void posPivot(float x,float y,float t) {
  float x1=(posX-x),y1=(posY-y);
  posX=x+((x1*dcos(t))+(y1*dsin(t)));
  posY=y+((y1*dcos(t))-(x1*dsin(t)));
  posH+=t;
  updatePoints();
}

void posFd(float x) {
  posX+=x*dsin(posH);
  posY+=x*dcos(posH);
  updatePoints();
}

void draw(int x0i, int y0i, int x1i, int y1i) {
  float x0 = float(x0i), x1 = float(x1i), y0 = float(y0i), y1 = float(y1i);
  float X0 = floor(x0 * 480.0 / 26.0);
  float Y0 = floor(y0 * 240.0 / 14.0);
  float X1 = ceil(x1 * 480.0 / 26.0);
  float Y1 = ceil(y1 * 240.0 / 14.0);
  Brain.Screen.drawRectangle(X0, Y0, X1 - X0, Y1 - Y0);
}

void GG() {
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(white);
  draw(3, 2, 10, 4);
  draw(2, 4, 4, 10);
  draw(3, 10, 10, 12);
  draw(8, 6, 10, 8);
  draw(10, 6, 12, 10);
  draw(11, 10, 12, 12);

  draw(15, 2, 22, 4);
  draw(14, 4, 16, 10);
  draw(15, 10, 22, 12);
  draw(20, 6, 22, 8);
  draw(22, 6, 24, 10);
  draw(23, 10, 24, 12);

  /*
     #######     #######
    ##          ##
    ##    ####  ##    ####
    ##      ##  ##      ##
     ####### #   ####### #
  */
}

void awaitFinish(brakeType x) {
  LMotor.setStopping(x);
  RMotor.setStopping(x);
  //waitUntil(LMotor.isSpinning()||RMotor.isSpinning());
  while (!(LMotor.isDone()&&RMotor.isDone())) {
    Controller1.Screen.newLine();
    Controller1.Screen.print("%7.3f %7.3f", LMotor.torque(Nm),
                             RMotor.torque(Nm));
  }
  waitUntil(LMotor.isDone()&&RMotor.isDone()&&(!(LMotor.isSpinning()||RMotor.isSpinning())));
  wait(500, msec);
}

void awaitFinish() {awaitFinish(hold);}

void setDriveTorque(float x) {
  LMotor.setMaxTorque(100.0*x,percent);
  RMotor.setMaxTorque(100.0*x,percent);
}
void setDriveStopping(brakeType x) {
  LMotor.setStopping(x);
  RMotor.setStopping(x);
}

void setArmTorque(float x) {
  Arm.setMaxTorque(100.0*x,percent);
}
void setClawTorque(float x) {
  Claw.setMaxTorque(100.0*x,percent);
}

void setArmTurns(float x) {
  Arm.setPosition(x,turns);
}
void setClawTurns(float x) {
  Claw.setPosition(x,turns);
}

void setArm(float x, float y) {
  Arm.setMaxTorque(100.0*y,percent);
  Arm.setPosition(x,turns);
}
void setClaw(float x, float y) {
  Claw.setMaxTorque(100.0*y,percent);
  Claw.setPosition(x,turns);
}

void tankMoveD(float lx, float rx, bool wait) {
  LMotor.spinFor(forward,lx,degrees,false);
  RMotor.spinFor(forward,rx,degrees,false);
  if (wait) {awaitFinish();}
}
void tankMoveD(float lx, float rx) {tankMoveD(lx,rx,true);}

void tankMoveT(float lx, float rx, bool wait) {
  LMotor.spinFor(forward,lx,turns,false);
  RMotor.spinFor(forward,rx,turns,false);
  if (wait) {awaitFinish();}
}
void tankMoveT(float lx, float rx) {tankMoveT(lx,rx,true);}

void lt(float theta, bool wait) {
  Controller1.Screen.newLine();
  Controller1.Screen.print("lt %10.6f (%10.6f)", theta, (WDIST * theta) / WRAD);
  Brain.Screen.newLine();
  Brain.Screen.print("lt %10.6f (%10.6f)", theta, (WDIST * theta) / WRAD);
  float y = (WDIST * theta) / (360*WRAD);
  posFd(WCIRC*y*OMULT);
  posPivot(wlX,wlY,-theta);
  tankMoveT(y*OMULT,y*(RMULT+OMULT),wait);
}

void rt(float theta, bool wait) {
  Controller1.Screen.newLine();
  Controller1.Screen.print("rt %10.6f (%10.6f)", theta, (WDIST * theta) / WRAD);
  Brain.Screen.newLine();
  Brain.Screen.print("rt %10.6f (%10.6f)", theta, (WDIST * theta) / WRAD);
  float y = (WDIST * theta) / (360*WRAD);
  posFd(WCIRC*y*OMULT);
  posPivot(wrX,wrY,theta);
  tankMoveD(y*(RMULT+OMULT),y*OMULT,wait);
}
void lt(float theta) {lt(theta,true);}
void rt(float theta) {rt(theta,true);}

void pivotL(float theta, bool wait) {
  Controller1.Screen.newLine();
  Controller1.Screen.print("lp %10.6f (%10.6f)", theta, (WDIST * theta) / WRAD);
  Brain.Screen.newLine();
  Brain.Screen.print("lp %10.6f (%10.6f)", theta, (WDIST * theta) / WRAD);
  tankMoveD(-PIVOTM*theta,PIVOTM*theta,wait);
  posH-=theta;
  updatePoints();
}
void pivotR(float theta, bool wait) {
  Controller1.Screen.newLine();
  Controller1.Screen.print("rp %10.6f (%10.6f)", theta, (WDIST * theta) / WRAD);
  Brain.Screen.newLine();
  Brain.Screen.print("rp %10.6f (%10.6f)", theta, (WDIST * theta) / WRAD);
  tankMoveD(PIVOTM*theta,-PIVOTM*theta);
  posH+=theta;
  updatePoints();
}
void pivotL(float theta) {pivotL(theta,true);}
void pivotR(float theta) {pivotR(theta,true);}

void fd() {
  Controller1.Screen.newLine();
  Controller1.Screen.print("fd");
  Brain.Screen.newLine();
  Brain.Screen.print("fd");
  LMotor.spin(forward);
  RMotor.spin(forward);
}

void bk() {
  Controller1.Screen.newLine();
  Controller1.Screen.print("bk");
  Brain.Screen.newLine();
  Brain.Screen.print("bk");
  LMotor.spin(reverse);
  RMotor.spin(reverse);
}

void halt(brakeType mode) {
  Controller1.Screen.newLine();
  Controller1.Screen.print("stop");
  Brain.Screen.newLine();
  Brain.Screen.print("stop");
  RMotor.setStopping(mode);
  LMotor.setStopping(mode);
  float l = LMotor.position(turns), r = RMotor.position(turns);
  RMotor.stop();
  LMotor.stop();
  RMotor.spinToPosition(l,turns);
  LMotor.spinToPosition(r,turns);
  awaitFinish();
}
void halt() {halt(hold);}

void fd(float dist, bool wait) {
  Controller1.Screen.newLine();
  Controller1.Screen.print("fd %10.6f (%10.6f)", dist, dist / WCIRC);
  Brain.Screen.newLine();
  Brain.Screen.print("fd %10.6f (%10.6f)", dist, dist / WCIRC);
  float x = dist * DMULT / WCIRC;
  float d1 = look();
  tankMoveT(x,x,wait);
  if (wait) {
    float d2 = look();
    if (((d1-dist)-d2>0.25)&&(d2>=0)) {
      fd((d1-dist)-d2);
    }
  }
}
void bk(float dist, bool wait) {
  Controller1.Screen.newLine();
  Controller1.Screen.print("bk %10.6f (%10.6f)", dist, dist / WCIRC);
  Brain.Screen.newLine();
  Brain.Screen.print("bk %10.6f (%10.6f)", dist, dist / WCIRC);
  float x = dist * DMULT / WCIRC;
  float d1 = look();
  tankMoveT(-x,-x,wait);
  if (wait) {
    float d2 = look();
    if (((d1+dist)-d2>0.25)&&(d2>=0)) {
      bk((d1+dist)-d2);
    }
  }
}
void fd(float dist) {fd(dist,true);}
void bk(float dist) {bk(dist,true);}