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
void ch2() {
  while (!Controller1.ButtonA.pressing()) {
    fd(96.00-PIVOTS-PIVOTS);
    pivotR(180.0);
  }
}
