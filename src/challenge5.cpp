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
float a = 0,b=0;
void ch5() {
  while (!Controller1.ButtonA.pressing()) {
    while ((look()<0)||(look()>10)) {
      fd(1);
      wait(0,seconds);
    }
    pivotL(15);
    wait(0,seconds);
    a = look();
    pivotR(15);
    wait(0,seconds);
    pivotR(15);
    wait(0,seconds);
    b = look();
    pivotL(15);
    wait(0,seconds);
    a = datan2((b*dsin(posH+15))-(a*dsin(posH-15)),(b*dcos(posH+15))-(a*dcos(posH-15)));
    pivotL(a);
    wait(0,seconds);
    pivotL(90);
    wait(0,seconds);
    pivotL(15);
    wait(0,seconds);
    a = look();
    pivotR(15);
    wait(0,seconds);
    pivotR(15);
    wait(0,seconds);
    b = look();
    pivotL(15);
    wait(0,seconds);
    a = datan2((b*dsin(posH+15))-(a*dsin(posH-15)),(b*dcos(posH+15))-(a*dcos(posH-15)));
    pivotL(a);
    wait(0,seconds);
  }
}
