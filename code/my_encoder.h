/*
 * my_encoder.h
 *
 *  Created on: 2023��12��16��
 *      Author: 86152
 */

#ifndef CODE_MY_ENCODER_H_
#define CODE_MY_ENCODER_H_

extern int16 my_encoder_data_dir_l ;
extern int16 my_encoder_data_dir_r ;
extern int32 motor_duty;   //���ռ�ձ�
extern int16 set_speed_l;    //�����ٶ�
extern int16 set_speed_r;    //�����ٶ�
//����ʽPID
extern float out_l;          //�����
extern int16 ek_l,ek1_l,ek2_l;   //ǰ���������

extern float out_r;          //�����
extern int16 ek_r,ek1_r,ek2_r;   //ǰ���������

extern float kp,ki,kd;     //����ʽPID����
//����PD
//extern int ek1_t;


void my_encoder_init(void);



#endif /* CODE_MY_ENCODER_H_ */
