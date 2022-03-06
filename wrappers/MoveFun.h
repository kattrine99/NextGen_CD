#ifndef MOVEFUN_H /* Include guard */
#define MOVEFUN_H

void initDCMotor();
void goForward();
void goBackward();
void slow();
void goLeft();
void goRight();
void smoothLeft();
void smoothBackLeft();
void smoothRight();
void smoothBackRight();
void stopDCMotor();
void initPinMode();
void initDCMotorPWM();
void goForwardPWM();
void goBackwardPWM();
void stopDCMotorPWM();
void fullStop();

//wrappers
void wGoForwardPwm(int time);
void wGoBackwardPwm(int time);
void wSmoothRight(int time);
void wSmoothLeft(int time);
void wGoRight(int time);
void wGoLeft(int time);



#endif 