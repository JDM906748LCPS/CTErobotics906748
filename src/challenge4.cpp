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
void ch4() {
  float l1,r1,l2,r2;
  l1 = LMotor.position(turns);
  r1 = RMotor.position(turns);
  fd();
  waitUntil((look()>0)&&(look()<5));
  l2 = LMotor.position(turns);
  r2 = RMotor.position(turns);
  LMotor.stop();
  RMotor.stop();
  LMotor.spinToPosition(l2,turns,false);
  RMotor.spinToPosition(r2,turns,false);
  LMotor.spinToPosition(l2,turns,true);
  RMotor.spinToPosition(r2,turns,true);
  while (!Controller1.ButtonA.pressing()) {
    LMotor.spinToPosition(l1,turns,false);
    RMotor.spinToPosition(r1,turns,false);
    wait(0.125,seconds);
    LMotor.spinToPosition(l1,turns,true);
    RMotor.spinToPosition(r1,turns,true);
    wait(0.125,seconds);
    LMotor.spinToPosition(l2,turns,false);
    RMotor.spinToPosition(r2,turns,false);
    wait(0.125,seconds);
    LMotor.spinToPosition(l2,turns,true);
    RMotor.spinToPosition(r2,turns,true);
    wait(0.125,seconds);
  }
}
