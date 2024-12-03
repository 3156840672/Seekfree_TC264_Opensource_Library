/*
 * my_encoder.c
 *
 *  Created on: 2023年12月16日
 *      Author: 86152
 */
#include "zf_common_headfile.h"

#define PIT0                            (CCU60_CH0 )                            // 使用的周期中断编号
#define ENCODER_DIR_L                     (TIM2_ENCODER)                         // 带方向编码器对应使用的编码器接口
#define ENCODER_DIR_PULSE_L               (TIM2_ENCODER_CH1_P33_7)               // PULSE 对应的引脚
#define ENCODER_DIR_DIR_L                 (TIM2_ENCODER_CH2_P33_6)               // DIR 对应的引脚

#define ENCODER_DIR_R                     (TIM5_ENCODER)                         // 带方向编码器对应使用的编码器接口
#define ENCODER_DIR_PULSE_R               (TIM5_ENCODER_CH1_P10_3)               // PULSE 对应的引脚
#define ENCODER_DIR_DIR_R                 (TIM5_ENCODER_CH2_P10_1)               // DIR 对应的引脚
int16 my_encoder_data_dir_l ;
int16 my_encoder_data_dir_r ;

void my_encoder_init(void)
{


encoder_dir_init(ENCODER_DIR_L, ENCODER_DIR_PULSE_L, ENCODER_DIR_DIR_L);          // 初始化编码器模块与引脚 带方向增量编码器模式
encoder_dir_init(ENCODER_DIR_R, ENCODER_DIR_PULSE_R, ENCODER_DIR_DIR_R);          // 初始化编码器模块与引脚 带方向增量编码器模式

          pit_ms_init(PIT0, 5);


          system_delay_ms(500);
}







//差速PD

//int ek1_t;
//
//int pid_t(int error)
//{
//    int16 turn;
//    float er;
//    float kp,kd,k;     //增量式PID参数
//
//        kp = 50;//设置比例系数


//
//        kd = 10;//设置微分系数
//
//        k=0.01;
//        er=error*k*(my_encoder_data_dir_l+my_encoder_data_dir_r)/2;
//
//       turn = (int16)(kp*er + kd*(er-ek1_t));//进行PD运算
//
//
//       ek1_t = er;//保存上次误差
//       if(turn>1000) turn=1000;
//       if(turn<-1000) turn=-1000;
//
//       return turn;
//}
//增量式PID

float out_l;          //输出量
int16 ek_l,ek1_l,ek2_l;   //前后三次误差
float kp=25,ki=2,kd=0;     //增量式PID参数
int16 set_speed_l=50;    //期望速度

int pid_l(int set_speed,int speed)
{

float out_increment;//增量式PID输出增量

int32 motor_duty;   //电机占空比

ek2_l = ek1_l;//保存上上次误差


                    ek1_l = ek_l; //保存上次误差


                    ek_l = set_speed_l - speed;//计算当前误差
                    //设置PID系数
                           //进行增量式PID运算

                    out_increment = (int16)(kp*(ek_l-ek1_l) + ki*ek_l + kd*(ek_l-2*ek2_l+ek2_l));  //计算增量

                    out_l += out_increment;       //输出增量
                    if(out_l>8000) out_l=8000;
                    if(out_l<0) out_l=0;//输出限幅 不能超过占空比最大值

                    motor_duty = (int32)out_l;    //强制转换为整数后赋值给电机占空比变量
                    return  motor_duty;

}

float out_r;          //输出量
int16 ek_r,ek1_r,ek2_r;   //前后三次误差
int16 set_speed_r=50;    //期望速度
int pid_r(int set_speed,int speed)
{

float out_increment;//增量式PID输出增量

int32 motor_duty;   //电机占空比

ek2_r = ek1_r;//保存上上次误差


                    ek1_r = ek_r; //保存上次误差

                    ek_r = set_speed_r - speed;//计算当前误差
                    //设置PID系数
                           //进行增量式PID运算

                   out_increment = (int16)(kp*(ek_r-ek1_r) + ki*ek_r + kd*(ek_r-2*ek2_r+ek2_r));  //计算增量

                   out_r += out_increment;       //输出增量
                   if(out_r>8000) out_r=8000;
                   if(out_r<0) out_r=0;//输出限幅 不能超过占空比最大值

                   motor_duty = (int32)out_r;    //强制转换为整数后赋值给电机占空比变量
                   return  motor_duty;


}

IFX_INTERRUPT(cc60_pit_ch0_isr, 0, CCU6_0_CH0_ISR_PRIORITY)
{
              interrupt_global_enable(0);                     // 开启中断嵌套
              pit_clear_flag(CCU60_CH0);


              my_encoder_data_dir_l = -encoder_get_count(ENCODER_DIR_L);                          // 获取编码器计数

              encoder_clear_count(ENCODER_DIR_L);                                           // 清空编码器计数
              my_encoder_data_dir_r =encoder_get_count(ENCODER_DIR_R);                          // 获取编码器计数

              encoder_clear_count(ENCODER_DIR_R);                                           // 清空编码器计数
              pd_s();
              my_servo_duty(smotor_duty);
             my_motor_SetSpeed( pid_l(set_speed_l,my_encoder_data_dir_l),pid_r(set_speed_r,my_encoder_data_dir_r));

}


