/*
 * my_motor.c
 *
 *  Created on: 2023年12月16日
 *      Author: 86152
 */


#include "zf_common_headfile.h"

#define MOTOR1_DIR               (P02_6)
#define MOTOR1_PWM               (ATOM1_CH7_P02_7)  //左

#define MOTOR2_DIR               (P02_4)
#define MOTOR2_PWM               (ATOM1_CH5_P02_5)   //右
void my_motor_init(void)
{

    gpio_init(MOTOR1_DIR,GPO, 0, GPO_PUSH_PULL);
    gpio_init(MOTOR2_DIR,GPO, 0, GPO_PUSH_PULL);
    pwm_init(MOTOR1_PWM, 17000, 0);
    pwm_init(MOTOR2_PWM, 17000, 0);

}

void my_motor_SetSpeed( int32 speed_l,int32 speed_r)
{


     if(speed_l<0)speed_l=0;
     if(speed_r<0)speed_r=0;
    gpio_set_level(MOTOR1_DIR,1);
    pwm_set_duty(MOTOR1_PWM,speed_l);
   // pwm_set_duty(MOTOR1_PWM,1000-turn);

    gpio_set_level(MOTOR2_DIR,0);
    pwm_set_duty(MOTOR2_PWM,speed_r);//正转

}
