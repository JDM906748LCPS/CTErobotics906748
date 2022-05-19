#include "eyecast.h"
#include "common.h"

#ifdef Eyes
  float cacheX[PCACHE] = {};
  float cacheY[PCACHE] = {};
  int cacheI = 0;
  float look() {
    if (Eyes.foundObject()) {
      float d = Eyes.distance(inches);
      cacheX[cacheI]=posX+(d*dsin(posH));
      cacheY[cacheI]=posY+(d*dcos(posH));
      cacheI=(cacheI+1)%PCACHE;
      return d;
    }
    return -1.0;
  }

  void scan() {
    float sight[72] = {};
    float m = 0,d,d1,d2;
    for (int i = 0; i < 72; i++) {
      d=look();m=fmax(m,d);
      sight[i]=d;
      tankMoveD(5.0,-5.0);
    }
    for (int i = 0; i < 72; i++) {
      d1=(50*sight[(i)%72]/m);
      d2=(50*sight[(i+1)%72]/m);
      Brain.Screen.drawLine(240+(d1*dsin(i*5)),120+(d1*dcos(i*5)),240+(d2*dsin((i+1)*5)),120+(d2*dcos((i+1)*5)));
    }
  }

  void drawView() {
    float s0 = cacheX[0], s1 = cacheX[0];
    for (int i = 0; i < PCACHE; i++) {
      s0=fmin(s0,fmin(cacheX[i],cacheY[i]));
      s1=fmax(s1,fmax(cacheX[i],cacheY[i]));
    }
    for (int i = 0; i < PCACHE; i++) {
      Brain.Screen.drawPixel(lerp(0,480,(cacheX[i]-s0)/(s1-s0)),lerp(240,0,(cacheY[i]-s0)/(s1-s0)));
    }
  }
#else
  // define the following functions so we can compile without including the ultrasonic sensor
  float look() {return -1.0;}
  void scan() {}
  void drawView() {}
#endif