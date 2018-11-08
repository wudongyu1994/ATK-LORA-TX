#include "sys.h"
#include "usart.h"	 


u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	

#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 


#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������	
  
  
void uart1_init(u32 bound){
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��

	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//USART1_RX	  GPIOA.10��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	

	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure); 
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);                    

}

void USART1_IRQHandler(void)  
{
	u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
			Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
				 
     } 
} 

// ���ڷ������ݺ���
// USART_SendData(USART1,ch);

#endif	


#if EN_USART2_RX
void uart2_init(u32 bound) {     
	//GPIO�˿�����                            
	GPIO_InitTypeDef GPIO_InitStructure;     
	USART_InitTypeDef USART_InitStructure;     
	NVIC_InitTypeDef NVIC_InitStructure;     
	USART_ClockInitTypeDef USART_ClockInitStructure;             

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);     
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);         
	//USART2_TX   PA.2     
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;     
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     
	GPIO_Init(GPIOA, &GPIO_InitStructure);          
	//USART3_RX   PA.3     
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;     
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;     
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);                         //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART1   

	USART_InitStructure.USART_BaudRate = bound;     
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;     
	USART_InitStructure.USART_StopBits = USART_StopBits_1;     
	USART_InitStructure.USART_Parity = USART_Parity_No;     
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;     
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;     
	//---------------------------------------------------------------------------------     
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;     
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;     
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;     
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;     
	USART_ClockInit(USART2, &USART_ClockInitStructure);     
	//---------------------------------------------------------------------------------     
	USART_Init(USART2, &USART_InitStructure);     
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�     
	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���    
}

void USART2_IRQHandler(void)  
{
	u8 Res;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
			Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
			USART_SendData(USART2,Res);	 
     } 
} 

#endif
