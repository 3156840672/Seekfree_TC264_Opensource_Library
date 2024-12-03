/*
 * my_servo.c
 *
 *  Created on: 2024��1��2��
 *      Author: 86152
 */

#include "zf_common_headfile.h"


#define SERVO_MOTOR_PWM             (ATOM1_CH1_P33_9)                          // ���������϶����Ӧ����
#define SERVO_MOTOR_FREQ            (50 )                                           // ���������϶��Ƶ��  �����ע�ⷶΧ 50-300

#define SERVO_MOTOR_L_MAX           (100 )                                           // ���������϶�����Χ �Ƕ�
#define SERVO_MOTOR_R_MAX           (70)                                           // ���������϶�����Χ �Ƕ�



// ------------------ ���ռ�ձȼ��㷽ʽ ------------------
//
// �����Ӧ�� 0-180 ��Ƕȶ�Ӧ ��������� 0.5ms-2.5ms �ߵ�ƽ
//
// ��ô��ͬƵ���µ�ռ�ձȼ��㷽ʽ����
// PWM_DUTY_MAX/(1000/freq)*(1+Angle/180) �� 50hz ʱ���� PWM_DUTY_MAX/(1000/50)*(1+Angle/180)
//
// ��ô 100hz �� 90�ȵĴ�� ���ߵ�ƽʱ��1.5ms ��������Ϊ
// PWM_DUTY_MAX/(1000/100)*(1+90/180) = PWM_DUTY_MAX/10*1.5
//
// ------------------ ���ռ�ձȼ��㷽ʽ ------------------

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

    ek1_s = ek_s;//�����ϴ����

           ek_s = error_t;//���㱾�����

           smotor_duty =85.0+(kp_s*ek_s + kd_s*(ek_s-ek1_s));//����PD����


}







