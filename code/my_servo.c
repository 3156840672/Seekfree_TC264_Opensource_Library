/*
 * my_servo.c
 *
 *  Created on: 2024年1月2日
 *      Author: 86152
 */

#include "zf_common_headfile.h"


#define SERVO_MOTOR_PWM             (ATOM1_CH1_P33_9)                          // 定义主板上舵机对应引脚
#define SERVO_MOTOR_FREQ            (50 )                                           // 定义主板上舵机频率  请务必注意范围 50-300

#define SERVO_MOTOR_L_MAX           (100 )                                           // 定义主板上舵机活动范围 角度
#define SERVO_MOTOR_R_MAX           (70)                                           // 定义主板上舵机活动范围 角度



// ------------------ 舵机占空比计算方式 ------------------
//
// 舵机对应的 0-180 活动角度对应 控制脉冲的 0.5ms-2.5ms 高电平
//
// 那么不同频率下的占空比计算方式就是
// PWM_DUTY_MAX/(1000/freq)*(1+Angle/180) 在 50hz 时就是 PWM_DUTY_MAX/(1000/50)*(1+Angle/180)
//
// 那么 100hz 下 90度的打角 即高电平时间1.5ms 计算套用为
// PWM_DUTY_MAX/(1000/100)*(1+90/180) = PWM_DUTY_MAX/10*1.5
//
// ------------------ 舵机占空比计算方式 ------------------

#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))


void my_servo_init(void)
{
    pwm_init(SERVO_MOTOR_PWM, SERVO_MOTOR_FREQ, 1000);
    pwm_set_duty(SERVO_MOTOR_PWM,(uint32)SERVO_MOTOR_DUTY(85.0));
}




void my_servo_duty(float myduty)
   {
       if (myduty>SERVO_MOTOR_L_MAX) myduty=SERVO_MOTOR_L_MAX;
       if (myduty<SERVO_MOTOR_R_MAX) myduty=SERVO_MOTOR_R_MAX;
       pwm_set_duty(SERVO_MOTOR_PWM, (uint32)SERVO_MOTOR_DUTY(myduty));
   }


float kp_s=0.5,kd_s=0.2;

int32 ek_s,ek1_s;

float smotor_duty;

void pd_s(void)
{

    ek1_s = ek_s;//保存上次误差

           ek_s = error_t;//计算本次误差

           smotor_duty =85.0+(kp_s*ek_s + kd_s*(ek_s-ek1_s));//进行PD运算


}







