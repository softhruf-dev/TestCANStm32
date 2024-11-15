#include "main.h"
#include "can.h"
#include "system.h"
#include <string.h>

#if defined(RTT_SEGGER_DEBUGER)
#include "SEGGER_RTT.h"
#endif

CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;

uint8_t TxData[8];
uint8_t RxData[8];

uint32_t TxMailbox;
int flgRcvCAN = 0;

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &RxHeader, RxData);
	if(RxHeader.ExtId == 0x18EFFF21)
	{
		flgRcvCAN = 1;		
	}
}

void canInit()
{
		TxHeader.DLC = 8;
	//7ff
	TxHeader.StdId = 0x00;
	TxHeader.ExtId = 0x18EF2100;
	TxHeader.IDE = CAN_ID_EXT;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.TransmitGlobalTime = DISABLE;	
	
	CAN_FilterTypeDef canfilterconfig;

  canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
  canfilterconfig.FilterBank = 10;  // which filter bank to use from the assigned ones
  canfilterconfig.FilterFIFOAssignment = CAN_RX_FIFO1;
  canfilterconfig.FilterIdHigh = 0;
  canfilterconfig.FilterIdLow = 0;
  canfilterconfig.FilterMaskIdHigh = 0;
  canfilterconfig.FilterMaskIdLow = 0;
  canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
  canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
  canfilterconfig.SlaveStartFilterBank = 0;  // how many filters to assign to the CAN1 (master can)

  if(HAL_CAN_ConfigFilter(&hcan, &canfilterconfig) != HAL_OK) {
		Error_Handler();
	}
}

void keyboardCheck()
{
	if(flgRcvCAN)
	{
		flgRcvCAN = 0;
		if(RxData[2] == 0x0A) //encoder state message
		{
			if(RxData[3] == 0x1) flgEvents[EV_PT_ENC_CW]++; else flgEvents[EV_PT_ENC_CCW]++;
		} else if(RxData[2] == 0x01) //key contact state
		{
			switch(RxData[3])
			{
				case 1: if(RxData[4]) flgEvents[EV_PT_K1_ON]++; else flgEvents[EV_PT_K1_OFF]++; break;
				case 2: if(RxData[4]) flgEvents[EV_PT_K2_ON]++; else flgEvents[EV_PT_K2_OFF]++; break;
				case 3: if(RxData[4]) flgEvents[EV_PT_K3_ON]++; else flgEvents[EV_PT_K3_OFF]++; break;
				case 4: if(RxData[4]) flgEvents[EV_PT_K4_ON]++; else flgEvents[EV_PT_K4_OFF]++; break;
				case 5: if(RxData[4]) flgEvents[EV_PT_K5_ON]++; else flgEvents[EV_PT_K5_OFF]++; break;
				case 6: if(RxData[4]) flgEvents[EV_PT_K6_ON]++; else flgEvents[EV_PT_K6_OFF]++; break;
				case 7: if(RxData[4]) flgEvents[EV_PT_K7_ON]++; else flgEvents[EV_PT_K7_OFF]++; break;
			}
		}
	}
}

void kbTest()
{
	TxData[0] = 0x04;
	TxData[1] = 0x1b;
	TxData[2] = 0x7D;
	TxData[3] = 0x00;
	TxData[4] = 0xff;
	TxData[5] = 0xff;
	TxData[6] = 0xff;
	TxData[7] = 0xff;
	HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox);
}
