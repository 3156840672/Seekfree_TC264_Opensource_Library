/*
 * my_encoder.h
 *
 *  Created on: 2023年12月16日
 *      Author: 86152
 */

#ifndef CODE_MY_ENCODER_H_
#define CODE_MY_ENCODER_H_

extern int16 my_encoder_data_dir_l ;
extern int16 my_encoder_data_dir_r ;
extern int32 motor_duty;   //电机占空比
extern int16 set_speed_l;    //期望速度
extern int16 set_speed_r;    //期望速度
//增量式PID
extern float out_l;          //输出量
extern int16 ek_l,ek1_l,ek2_l;   //前后三次误差

extern float out_r;          //输出量
extern int16 ek_r,ek1_r,ek2_r;   //前后三次误差

extern float kp,ki,kd;     //增量式PID参数
//差速PD
//extern int ek1_t;


void my_encoder_init(void);



#endif /* CODE_MY_ENCODER_H_ */
