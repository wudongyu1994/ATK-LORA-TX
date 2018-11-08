#include "exti.h"

extern bool flagControl;
extern bool flagExti;
extern bool first;

//�ⲿ�ж�1�������
void EXTIX_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

    //GPIOA.1	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1);
    EXTI_InitStructure.EXTI_Line=EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;	//1--->0
    EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

}

//�ⲿ�ж�1�������
void EXTI1_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line1);  //���LINE1�ϵ��жϱ�־λ

    }
}

