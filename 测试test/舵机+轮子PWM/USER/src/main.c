/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC16F40K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/

#include "headfile.h"


/*
 *�����ں�Ƶ�ʵ��趨�����Բ鿴board.h�ļ�
 *��board_init��,�Ѿ���P54��������Ϊ��λ
 *�����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����
 */
uint16 steer_duty;
uint16 speed_duty;

void main()
{
	DisableGlobalIRQ();	//�ر����ж�	

    //sys_clk��ѡֵ:30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600��
    //����ϵͳƵ�ʣ���Ƶ����Ҫ��STC-ISP����е� <�����û��������е�IRCƵ��>ѡ���Ƶ��һ�¡�
    //���Ƶ�����ò��ԣ����ᵼ�´��ڵ����ݲ�����,PWM�Ĺ����������ȵȡ�
    sys_clk = 30000000;     //����ϵͳƵ��Ϊ30MHz
	
	board_init();	
	gpio_mode(P6_0,GPO_PP);
	gpio_mode(P6_4,GPO_PP);
	//gpio_mode(P7_4,GPO_PP);
	pwm_init(PWMA_CH2P_P62, 10000, 0);     //��ʼ��PWM5  ʹ������P2.5  ���PWMƵ��10000HZ   ռ�ձ�Ϊ�ٷ�֮ pwm_duty / PWM_DUTY_MAX * 100
	pwm_init(PWMA_CH4P_P66, 10000, 0);
	pwm_init(PWMB_CH1_P74, 50, 705);
	//delay_ms(2000);
	
	steer_duty = 705;
	speed_duty = 600;
	
	EnableGlobalIRQ();	//�������ж�
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

