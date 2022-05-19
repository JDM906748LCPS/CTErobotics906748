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

void ch1() {
  fd(24.00 - WDIST);
  lt(90.00);
  fd(31.00 - WDIST);
  rt(90.00);
  fd(18.75 - WDIST);
  rt(90.00);
  fd(15.00 - WDIST);
  // GG();
}
