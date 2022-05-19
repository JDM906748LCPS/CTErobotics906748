// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LMotor               motor         10              
// RMotor               motor         1               
// Controller1          controller                    
// Arm                  motor         8               
// Claw                 motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "challenges.h"
#include "trilateration.h"
#include "unitTests.h"
#include "eyecast.h"

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  LMotor.setMaxTorque(10, percent);
  RMotor.setMaxTorque(10, percent);
  LMotor.setVelocity(10, percent);
  RMotor.setVelocity(10, percent);
  ch6();
}