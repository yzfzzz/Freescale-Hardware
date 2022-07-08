/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC16F40K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/

#include "headfile.h"


/*
 *关于内核频率的设定，可以查看board.h文件
 *在board_init中,已经将P54引脚设置为复位
 *如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可
 */
uint16 steer_duty;
uint16 speed_duty;

void main()
{
	DisableGlobalIRQ();	//关闭总中断	

    //sys_clk可选值:30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600。
    //设置系统频率，此频率需要跟STC-ISP软件中的 <输入用户程序运行的IRC频率>选项的频率一致。
    //如果频率设置不对，将会导致串口的数据不正常,PWM的工作不正常等等。
    sys_clk = 30000000;     //设置系统频率为30MHz
	
	board_init();	
	gpio_mode(P6_0,GPO_PP);
	gpio_mode(P6_4,GPO_PP);
	//gpio_mode(P7_4,GPO_PP);
	pwm_init(PWMA_CH2P_P62, 10000, 0);     //初始化PWM5  使用引脚P2.5  输出PWM频率10000HZ   占空比为百分之 pwm_duty / PWM_DUTY_MAX * 100
	pwm_init(PWMA_CH4P_P66, 10000, 0);
	pwm_init(PWMB_CH1_P74, 50, 705);
	//delay_ms(2000);
	
	steer_duty = 705;
	speed_duty = 600;
	
	EnableGlobalIRQ();	//开启总中断
    while(1)
	{
		P60=1;
		P64=0;
		pwm_duty(PWMB_CH1_P74, steer_duty);
		pwm_duty(PWMA_CH2P_P62, speed_duty);
		pwm_duty(PWMA_CH4P_P66, speed_duty);
		
		if(steer_duty >=805)
		{
			steer_duty = 605;
		}
		
		if(speed_duty >=1500)
		{
			speed_duty = 600;
		}
		
		steer_duty = steer_duty+10;
		speed_duty = speed_duty+100;
		
		delay_ms(1000);
    }
}

