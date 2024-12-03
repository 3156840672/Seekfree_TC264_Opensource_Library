/*
 * my_usart.c
 *
 *  Created on: 2024年1月1日
 *      Author: 86152
 */
#include "zf_common_headfile.h"


#define FLASH_SECTION_INDEX       (0)                                 // 存储数据用的扇区
#define FLASH_PAGE_INDEX          (8)                                // 存储数据用的页码 倒数第一个页码


uint8 data_received ;

void my_usart_init(void)
{
    uart_init(UART_2,9600,UART2_TX_P10_5,UART2_RX_P10_6);
    uart_rx_interrupt(UART_2, 1);
    flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区

    kp=25+flash_union_buffer[0].float_type;
    ki=2+flash_union_buffer[1].float_type;
    kd=8+flash_union_buffer[2].float_type;
    kp_s=0.5+flash_union_buffer[3].float_type;
    kd_s=0.2+flash_union_buffer[4].float_type;
    set_speed_l=set_speed_r=40+flash_union_buffer[5].int16_type;
    flash_buffer_clear();                                                       // 清空缓冲区

    uart_write_string(UART_2, "usart init");
}


void my_usart(void)
{
    if(data_received)
         {
             uart_write_byte(UART_2, data_received);

             if(data_received==121)         //y
             {
                 my_motor_SetSpeed(0,0);
                 uart_write_string(UART_2, "stop");
                 assert_interrupt_config();

                 system_delay_ms(5000);
                 uart_write_string(UART_2, "stop");
                 interrupt_global_enable(1);
             }
             if(data_received==97)           //a
             {


                uart_write_string(UART_2, "kp+\n");
                flash_buffer_clear();                                                       // 清空缓冲区
                flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
                flash_union_buffer[0].float_type+=0.1;
                kp=25+flash_union_buffer[0].float_type;
                printf("kp=%f",kp);
                flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
              }
             if(data_received==98)           //b
            {


                uart_write_string(UART_2, "ki+\n");
                flash_buffer_clear();                                                       // 清空缓冲区
                flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
                flash_union_buffer[1].float_type+=0.1;
                ki=2+flash_union_buffer[1].float_type;
                printf("ki=%f",ki);
                flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
            }
            if(data_received==99)           //c
            {


                uart_write_string(UART_2, "kd+\n");
                flash_buffer_clear();                                                       // 清空缓冲区
                flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
                flash_union_buffer[2].float_type+=0.1;
                kd=8+flash_union_buffer[2].float_type;
                printf("kd=%f",kd);
                flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
            }
             if(data_received==100)           //d
            {


                uart_write_string(UART_2, "kp_s+\n");
                flash_buffer_clear();                                                       // 清空缓冲区
                flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
                flash_union_buffer[3].float_type+=0.01;
                kp_s=0.5+flash_union_buffer[3].float_type;
                printf("kp_s=%f",kp_s);
                flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
            }
            if(data_received==101)           //e
            {


                uart_write_string(UART_2, "kd_s+\n");
                flash_buffer_clear();                                                       // 清空缓冲区
                flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
                flash_union_buffer[4].float_type+=0.01;
                kd_s=0.2+flash_union_buffer[4].float_type;
                printf("kd_s=%f",kd_s);
                flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
            }
            if(data_received==102)           //f
             {


                uart_write_string(UART_2, "kp-\n");
                flash_buffer_clear();                                                       // 清空缓冲区
                flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
                flash_union_buffer[0].float_type-=0.1;
                kp=25+flash_union_buffer[0].float_type;
                printf("kp=%f",kp);
                flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
              }
              if(data_received==103)           //g
             {


                 uart_write_string(UART_2, "ki-\n");
                 flash_buffer_clear();                                                       // 清空缓冲区
                 flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
                 flash_union_buffer[1].float_type-=0.1;
                 ki=2+flash_union_buffer[1].float_type;
                 printf("ki=%f",ki);
                 flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
             }
             if(data_received==104)           //h
             {


                 uart_write_string(UART_2, "kd-\n");
                 flash_buffer_clear();                                                       // 清空缓冲区
                 flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
                 flash_union_buffer[2].float_type-=0.1;
                 kd=8+flash_union_buffer[2].float_type;
                 printf("kd=%f",kd);
                 flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
             }
              if(data_received==105)           //i
             {


                 uart_write_string(UART_2, "kp_s-\n");
                 flash_buffer_clear();                                                       // 清空缓冲区
                 flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
                 flash_union_buffer[3].float_type-=0.01;
                 kp_s=0.5+flash_union_buffer[3].float_type;
                 printf("kp_s=%f",kp_s);
                 flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
             }
             if(data_received==106)           //j
             {


                 uart_write_string(UART_2, "kd_s-\n");
                 flash_buffer_clear();                                                       // 清空缓冲区
                 flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
                 flash_union_buffer[4].float_type-=0.01;
                 kd_s=0.2+flash_union_buffer[4].float_type;
                 printf("kd_s=%f",kd_s);
                 flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
             }
             if(data_received==107)           //k speed+
             {


                 uart_write_string(UART_2, "speed+\n");
                 flash_buffer_clear();                                                       // 清空缓冲区
                 flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
                 flash_union_buffer[5].int16_type+=5;
                 set_speed_l=set_speed_r=40+flash_union_buffer[5].int16_type;
                 printf("speed=%d\n",set_speed_l);
                 flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
             }
             if(data_received==108)           //l speed-
             {


                 uart_write_string(UART_2, "speed-\n");
                 flash_buffer_clear();                                                       // 清空缓冲区
                 flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);           // 将数据从 flash 读取到缓冲区
                 flash_union_buffer[5].int16_type-=5;
                 set_speed_l=set_speed_r=40+flash_union_buffer[5].int16_type;
                 printf("speed=%d\n",set_speed_l);
                 flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
              }
             if(data_received==114)           //r
            {
                 uart_write_string(UART_2, "reset");
                flash_buffer_clear();
                flash_union_buffer[0].float_type=0;
                flash_union_buffer[1].float_type=0;
                flash_union_buffer[2].float_type=0;
                flash_union_buffer[3].float_type=0;
                flash_union_buffer[4].float_type=0;
                flash_union_buffer[5].float_type=0;
                flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);        // 向指定 Flash 扇区的页码写入缓冲区数据
            }


             data_received=0;
         }

}




IFX_INTERRUPT(uart2_rx_isr, 0, UART2_RX_INT_PRIO)
{
    interrupt_global_enable(0);                     // 开启中断嵌套
    wireless_module_uart_handler();                 // 无线模块统一回调函数

    uint8 dat;
    if(uart_query_byte(UART_2, &dat) == 1)
    {

                data_received = dat;

     }


}
