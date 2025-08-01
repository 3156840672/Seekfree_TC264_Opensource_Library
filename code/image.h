/*
 * image.h
 *
 *  Created on: 2023年12月18日
 *      Author: 86152
 */

#ifndef CODE_IMAGE_H_
#define CODE_IMAGE_H_




////数据类型声明（方便移植——移植的时候可以删掉，改成你自己的）
//typedef   signed          char int8;
//typedef   signed short     int int16;
//typedef   signed           int int32;
//typedef unsigned          char uint8;
//typedef unsigned short     int uint16;
//typedef unsigned           int uint32;
//
//颜色定义  因为有先例，连颜色都改不来，我直接放这了
#define uesr_RED     0XF800    //红色
#define uesr_GREEN   0X07E0    //绿色
#define uesr_BLUE    0X001F    //蓝色




//宏定义
#define image_h 120//图像高度
#define image_w 188//图像宽度

#define white_pixel 255
#define black_pixel 0

#define bin_jump_num    1//跳过的点数
#define border_max  image_w-2 //边界最大值
#define border_min  1   //边界最小值
extern uint8 original_image[image_h][image_w];
extern uint8 bin_image[image_h][image_w];//图像数组
extern int error_t;

extern void image_process(void); //直接在中断或循环里调用此程序就可以循环执行了



#endif /* CODE_IMAGE_H_ */
