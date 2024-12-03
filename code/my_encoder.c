/*
 * my_encoder.c
 *
 *  Created on: 2023��12��16��
 *      Author: 86152
 */
#include "zf_common_headfile.h"

#define PIT0                            (CCU60_CH0 )                            // ʹ�õ������жϱ��
#define ENCODER_DIR_L                     (TIM2_ENCODER)                         // �������������Ӧʹ�õı������ӿ�
#define ENCODER_DIR_PULSE_L               (TIM2_ENCODER_CH1_P33_7)               // PULSE ��Ӧ������
#define ENCODER_DIR_DIR_L                 (TIM2_ENCODER_CH2_P33_6)               // DIR ��Ӧ������

#define ENCODER_DIR_R                     (TIM5_ENCODER)                         // �������������Ӧʹ�õı������ӿ�
#define ENCODER_DIR_PULSE_R               (TIM5_ENCODER_CH1_P10_3)               // PULSE ��Ӧ������
#define ENCODER_DIR_DIR_R                 (TIM5_ENCODER_CH2_P10_1)               // DIR ��Ӧ������
int16 my_encoder_data_dir_l ;
int16 my_encoder_data_dir_r ;

void my_encoder_init(void)
{


encoder_dir_init(ENCODER_DIR_L, ENCODER_DIR_PULSE_L, ENCODER_DIR_DIR_L);          // ��ʼ��������ģ�������� ����������������ģʽ
encoder_dir_init(ENCODER_DIR_R, ENCODER_DIR_PULSE_R, ENCODER_DIR_DIR_R);          // ��ʼ��������ģ�������� ����������������ģʽ

          pit_ms_init(PIT0, 5);


          system_delay_ms(500);
}







//����PD

//int ek1_t;
//
//int pid_t(int error)
//{
//    int16 turn;
//    float er;
//    float kp,kd,k;     //����ʽPID����
//
//        kp = 50;//���ñ���ϵ��


//
//        kd = 10;//����΢��ϵ��
//
//        k=0.01;
//        er=error*k*(my_encoder_data_dir_l+my_encoder_data_dir_r)/2;
//
//       turn = (int16)(kp*er + kd*(er-ek1_t));//����PD����
//
//
//       ek1_t = er;//�����ϴ����
//       if(turn>1000) turn=1000;
//       if(turn<-1000) turn=-1000;
//
//       return turn;
//}
//����ʽPID

float out_l;          //�����
int16 ek_l,ek1_l,ek2_l;   //ǰ���������
float kp=25,ki=2,kd=0;     //����ʽPID����
int16 set_speed_l=50;    //�����ٶ�

int pid_l(int set_speed,int speed)
{

float out_increment;//����ʽPID�������

int32 motor_duty;   //���ռ�ձ�

ek2_l = ek1_l;//�������ϴ����


                    ek1_l = ek_l; //�����ϴ����


                    ek_l = set_speed_l - speed;//���㵱ǰ���
                    //����PIDϵ��
                           //��������ʽPID����

                    out_increment = (int16)(kp*(ek_l-ek1_l) + ki*ek_l + kd*(ek_l-2*ek2_l+ek2_l));  //��������

                    out_l += out_increment;       //�������
                    if(out_l>8000) out_l=8000;
                    if(out_l<0) out_l=0;//����޷� ���ܳ���ռ�ձ����ֵ

                    motor_duty = (int32)out_l;    //ǿ��ת��Ϊ������ֵ�����ռ�ձȱ���
                    return  motor_duty;

}

float out_r;          //�����
int16 ek_r,ek1_r,ek2_r;   //ǰ���������
int16 set_speed_r=50;    //�����ٶ�
int pid_r(int set_speed,int speed)
{

float out_increment;//����ʽPID�������

int32 motor_duty;   //���ռ�ձ�

ek2_r = ek1_r;//�������ϴ����


                    ek1_r = ek_r; //�����ϴ����

                    ek_r = set_speed_r - speed;//���㵱ǰ���
                    //����PIDϵ��
                           //��������ʽPID����

                   out_increment = (int16)(kp*(ek_r-ek1_r) + ki*ek_r + kd*(ek_r-2*ek2_r+ek2_r));  //��������

                   out_r += out_increment;       //�������
                   if(out_r>8000) out_r=8000;
                   if(out_r<0) out_r=0;//����޷� ���ܳ���ռ�ձ����ֵ

                   motor_duty = (int32)out_r;    //ǿ��ת��Ϊ������ֵ�����ռ�ձȱ���
                   return  motor_duty;


}

IFX_INTERRUPT(cc60_pit_ch0_isr, 0, CCU6_0_CH0_ISR_PRIORITY)
{
              interrupt_global_enable(0);                     // �����ж�Ƕ��
              pit_clear_flag(CCU60_CH0);


              my_encoder_data_dir_l = -encoder_get_count(ENCODER_DIR_L);                          // ��ȡ����������

              encoder_clear_count(ENCODER_DIR_L);                                           // ��ձ���������
              my_encoder_data_dir_r =encoder_get_count(ENCODER_DIR_R);                          // ��ȡ����������

              encoder_clear_count(ENCODER_DIR_R);                                           // ��ձ���������
              pd_s();
              my_servo_duty(smotor_duty);
             my_motor_SetSpeed( pid_l(set_speed_l,my_encoder_data_dir_l),pid_r(set_speed_r,my_encoder_data_dir_r));

}


