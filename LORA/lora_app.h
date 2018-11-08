#ifndef _LORA_APP_H_
#define _LORA_APP_H_

#include "sys.h"
#include "lora_cfg.h"

#define LORA_AUX  PAin(4)    //LORA模块状态引脚
#define LORA_MD0  PAout(5)  //LORA模块控制引脚

extern _LoRa_CFG LoRa_CFG;
extern u8 Lora_mode;

u8 LoRa_Init(void);
void Aux_Int(u8 mode);
void LoRa_Set(void);
void LoRa_SendData(void);
void LoRa_ReceData(void);
void LoRa_Process(void);
void Lora_Test(void);
u8 lora_send_cmd(u8 *cmd,u8 *ack,u16 waittime);
u8* lora_check_cmd(u8 *str);

#endif
