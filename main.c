#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "pwm.h"
#include "wave.h"
#include "led1.h"
#include "stdio.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "oled.h"
#include "pid.h"
#include "vl53l0x.h"
#include "24cxx.h" 

//////////////////////////////////////////////////////////////////////////////////	 
//未经作者许可，不得用于其它任何用途
//STM32f103c8t6滚球系统
//作者：锅锅  QQ:2469335032
//修改日期:2023/07/20
//版本：V2.1
//版权所有，盗版必究。
//All rights reserved
//主要控制函数在control.c中，部分初始化外设没用上请忽略
////////////////////////////////////////////////////////////////////////////////// 	  


int main(void)
{
	float pitch,roll,yaw,Yaw=0; 		//欧拉角
	short aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	short temp;					//温度	
	
	SystemInit();  //系统时钟的初始化
	delay_init();  //延时时钟的初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断分组，也就是程序先后执行的优先级

	LED1_Init();	 //STM32f103c8t6最小系统板上的LED灯的初始化
	LED1=0;   
	
	Wave_IO_Init();  //初始化超声波
	OLED_Init();    //初始化OLED

	uart_init(115200);  //串口通信的初始化并设置相应的波推率9600，用于USB232口下载.hex工程文件时用
	
	TIM3_PWM_Init(1999,71);  //初始化舵机f=72M/(72*2000)=500hz

  TIM4_Int_Init(499,7199);//10Khz的计数频率，计数到500为50ms触发一次定时器中断 
	AT24CXX_Init();			//IIC初始化 与激光测距模块通信 

	Set_Aimangle(50);  //舵机回位
	delay_ms(100);
	
  //显示距离和舵机角度
	OLED_ShowString(0,32,"Distance:",16,1);
	OLED_ShowString(100,32,"cm",16,1);
	OLED_ShowString(0,48,"Psc:",16,1);
	OLED_Refresh();	
	
	while(1) {
		
//方案二 激光测距 具体原理不用了解 调用一次可以刷新全局变量Distance_data，获取实时位置
		vl53l0x_test();//vl53l0x测试   
		
		
//超声波测距  方案一 超声波测距		
//		LED1=!LED1;


//		distance=0;
//		for(i=0;i<3;i++){
//			distance+=Wave_Start();
//			delay_ms(10);
//		}
//		My_Distance=distance/3;

//		delay_ms(500);





	}


	
}
	

			 
			  


			
		



	
		


	
	

