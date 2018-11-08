实验器材:
	STM32F103 C8T6
	
硬件资源:
	delay.c适用于8M晶振的情况。
	x.引脚	引脚名		连接对象
	1.PA9	TX			电脑端RX
	2.PA10	RX			电脑端TX
	PA4					LORA_MU0
	PA15				LORA_AUX
	PB10	TX3			LORA_RX
	PB11	RX3			LORA_TX

实验现象:
	每1s，给lora发送一次数据包“ATK-LORA-01 TEST xx”，xx递增。电脑端可以看到显示“data sent!”

	
注意事项:
	1.keilkill.bat,是一个批处理文件，双击自动运行，删除程序编译过程中生成的中间文件，方便打包传输。