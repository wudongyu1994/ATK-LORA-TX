#include "sys.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "exti.h"
#include "lora_app.h"
#include "usart3.h"

/************************************************
�߼�ժҪ
    1.��ʼ��loraģ��
    2.loraģ�����ã����ù��̲����ʱ���Ϊ115200���������������Ϊ�Զ��岨���ʣ�
    3.ÿ1s����loraģ�鷢�����ݣ�ͨѶʱ������Ϊ�Զ��岨���ʣ�


************************************************/

int main(void)
{

//	SystemInit();
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    uart1_init(115200);
    printf("uart1_init success!\n");
    LED_Init();

    while(LoRa_Init())  //��ʼ��ATK-LORA-01ģ��,����ʼ��ʧ����300ms�����ԣ�ֱ���ɹ�
    {
        printf("LoRa undetected...\n");
        delay_ms(300);
    }
    printf("LoRa detected!\n");
    
    LoRa_Set();     //LoRa����(�������������ô��ڲ�����Ϊ115200)

    printf("start while(1)\n");
    while(1)
    {
        LoRa_SendData();            //��������
        delay_ms(1000);
    }
}
