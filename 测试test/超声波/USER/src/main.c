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
void main()
{
	int count = 0;
	int Distance_test;
	uint16 SRF_05_time;
	DisableGlobalIRQ();	//�ر����ж�	

    //sys_clk��ѡֵ:30000000, 27000000. 24000000, 22118400, 20000000, 18432000, 12000000, 11059200, 6000000, 5529600��
    //����ϵͳƵ�ʣ���Ƶ����Ҫ��STC-ISP����е� <�����û��������е�IRCƵ��>ѡ���Ƶ��һ�¡�
    //���Ƶ�����ò��ԣ����ᵼ�´��ڵ����ݲ�����,PWM�Ĺ����������ȵȡ�
    sys_clk = 30000000;     //����ϵͳƵ��Ϊ30MHz
	
	board_init();	
	gpio_mode(P3_7,GPI_IMPEDANCE);
	P37 = 0;
	gpio_mode(P3_3,GPO_PP);
	P33=1;
	EnableGlobalIRQ();	//�������ж�
    while(1)
	{
						 
		P33 = 1;
		delay_us(20);
		P33 = 0;
		while(P37!=1);
			TL1 = 0x00;
			TH1 = 0x00;
			TMOD |= 0x40; // �ⲿ����ģʽ
			TR1 = 1; // ������ʱ��
		count = 0;
		while(P37 ==1)
		{
			count ++;
			delay_us(1);
			
		}TR1 = 0;
		  
			SRF_05_time = (uint16)TH1 << 8;
		  printf("SRF_05_time_H=%d\r\n",SRF_05_time);
			SRF_05_time = ((uint8)TL1) | SRF_05_time;
			printf("SRF_05_time=%d\r\n",SRF_05_time);
			
			Distance_test = (int)(count*0.017);//SRF_05_time*340/200;		
			printf("%d,%d\r\n",count,Distance_test);
//		delay_ms(200);

  }
}
