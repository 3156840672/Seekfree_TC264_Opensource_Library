/*
 * servo.h
 *
 *  Created on: 2024Äê1ÔÂ2ÈÕ
 *      Author: 86152
 */

#ifndef CODE_MY_SERVO_H_
#define CODE_MY_SERVO_H_


void my_servo_init(void);
void my_servo_duty(float myduty);
void pd_s(void);

extern float kp_s,kd_s;

extern int32 ek_s,ek1_s;

extern float smotor_duty;

#endif /* CODE_MY_SERVO_H_ */
