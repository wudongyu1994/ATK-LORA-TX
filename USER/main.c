#include "sys.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "exti.h"
#include "lora_app.h"
#include "usart3.h"

/************************************************
逻辑摘要
    1.初始化lora模块
    2.lora模块设置（设置过程波特率必须为115200，设置完后波特率设为自定义波特率）
    3.每1s，给lora模块发送数据（通讯时波特率为自定义波特率）


************************************************/

int main(void)
{

//	SystemInit();
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart1_init(115200);
    printf("uart1_init success!\n");
    LED_Init();

    while(LoRa_Init())  //初始化ATK-LORA-01模块,若初始化失败则300ms后重试，直到成功
    {
        printf("LoRa undetected...\n");
        delay_ms(300);
    }
    printf("LoRa detected!\n");
    
    LoRa_Set();     //LoRa配置(进入配置需设置串口波特率为115200)

    printf("start while(1)\n");
    while(1)
    {
        LoRa_SendData();            //发送数据
        delay_ms(1000);
    }
}
