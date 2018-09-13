/*
 * File      : app_gpio.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-1-20       DQL         the first version 
 */

#include <rthw.h>
#include <rtthread.h>

#include "app_gpio.h"
#include <drivers/pin.h>

#define LED0 57 	//PB1--57，在 drv_gpio.c 文件 pin_index pins[]中查到
#define LED1 56 	//PB0--56，在 drv_gpio.c 文件 pin_index pins[]中查到

#define KEY0    44 	//PH3--44，在 drv_gpio.c 文件 pin_index pins[]中查到
#define KEY1    43	//PH2--43，在 drv_gpio.c 文件 pin_index pins[]中查到
#define KEY2    8	//PC13--8，在 drv_gpio.c 文件 pin_index pins[]中查到
#define WK_UP   40	//PA0--40，在 drv_gpio.c 文件 pin_index pins[]中查到

//管脚外部中断回调函数
void hdr_callback(void *args)
{
    //获取参数
    char *a = args;
    rt_kprintf("key0 down! %s\n",a);
}

void irq_thread_entry(void* parameter)
{    
	//上拉输入
    rt_pin_mode(KEY0, PIN_MODE_INPUT_PULLUP);
    //绑定中断，下降沿模式，回调函数名为hdr_callback
    rt_pin_attach_irq(KEY0, PIN_IRQ_MODE_FALLING,hdr_callback,(void*)"callback args");
    //使能中断
    rt_pin_irq_enable(KEY0, PIN_IRQ_ENABLE);    
           
}

void key_thread_entry(void* parameter)
{    
   
    //PE1、PE2设置上拉输入
    rt_pin_mode(KEY1, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY2, PIN_MODE_INPUT_PULLUP);
    //PA0设置为下拉输入
    rt_pin_mode(WK_UP, PIN_MODE_INPUT_PULLDOWN);
          
    while (1)
    {   
        //检测到低电平，即按键1按下了
        if (rt_pin_read(KEY1) == PIN_LOW)
        {
            rt_kprintf("key1 pressed!\n");
        }
        //检测到低电平，即按键2按下了
        if (rt_pin_read(KEY2) == PIN_LOW)
        {
            rt_kprintf("key2 pressed!\n");
        }
        //检测到高电平，即按键wp按下了
        if (rt_pin_read(WK_UP) == PIN_HIGH)
        {
            rt_kprintf("WK_UP pressed!\n");
        }
        //挂起10ms
        rt_thread_delay(rt_tick_from_millisecond(10));        
    }            
}

void led_thread_entry(void* parameter)
{    
    //设置管脚为输出模式      
    rt_pin_mode(LED0, PIN_MODE_OUTPUT); 
    //设置管脚为输出模式
    rt_pin_mode(LED1, PIN_MODE_OUTPUT); 
         
    while (1)
    {   
        //输出低电平，LED0 亮
        rt_pin_write(LED0, PIN_LOW);
        //输出低电平，LED1 亮   
        rt_pin_write(LED1, PIN_LOW);     
        //挂起 500ms
        rt_thread_delay(rt_tick_from_millisecond(500));
        //输出高电平，LED0 灭
        rt_pin_write(LED0, PIN_HIGH);
        //输出高电平，LED1 灭
        rt_pin_write(LED1, PIN_HIGH);
        //挂起 500ms
        rt_thread_delay(rt_tick_from_millisecond(500));       
    }            
}

void gpio_thread_entry(void* parameter)
{
    
    rt_thread_t tid;
       
    /* 创建key线程 */
    tid = rt_thread_create("key",
                    key_thread_entry, 
                    RT_NULL,
                    1024, 
                    4, 
                    10);
    /* 创建成功则启动线程 */
    if (tid != RT_NULL)
        rt_thread_startup(tid);
    
    /* 创建led线程 */
    tid = rt_thread_create("led",
                    led_thread_entry, 
                    RT_NULL,
                    1024, 
                    5, 
                    10);
    /* 创建成功则启动线程 */
    if (tid != RT_NULL)
        rt_thread_startup(tid);
    
    /* 创建irq线程 */
    tid = rt_thread_create("exirq",
                    irq_thread_entry, 
                    RT_NULL,
                    1024, 
                    6, 
                    10);
    /* 创建成功则启动线程 */
    if (tid != RT_NULL)
        rt_thread_startup(tid);
              
//    return 0;
}
