#include "sys.h"
#include "usart.h"	 


u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	

#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 


#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序	
  
  
void uart1_init(u32 bound){
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟

	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//USART1_RX	  GPIOA.10初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	

	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure); 
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);                    

}

void USART1_IRQHandler(void)  
{
	u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
			Res =USART_ReceiveData(USART1);	//读取接收到的数据
				 
     } 
} 

// 串口发送数据函数
// USART_SendData(USART1,ch);

#endif	


#if EN_USART2_RX
void uart2_init(u32 bound) {     
	//GPIO端口设置                            
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
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);                         //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器USART1   

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
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断     
	USART_Cmd(USART2, ENABLE);                    //使能串口    
}

void USART2_IRQHandler(void)  
{
	u8 Res;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
			Res =USART_ReceiveData(USART2);	//读取接收到的数据
			USART_SendData(USART2,Res);	 
     } 
} 

#endif
