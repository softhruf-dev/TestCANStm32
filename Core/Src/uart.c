#include "main.h"
#include "uart.h"
#include <string.h>

#if defined(RTT_SEGGER_DEBUGER)
#include "SEGGER_RTT.h"
#endif

uint8_t rx_buffer[RXBUF_SIZE] = {0};
uint8_t tx_buffer[TXBUF_SIZE] = {0};

uint8_t flg_packetReceived = 0;
UART_Packet sendPacket;

static uint16_t rx_index = 0;
uint8_t checksum;

void UartInit(void)
{
	sendPacket.start_delimiter = CMD_ST;
	sendPacket.end_delimiter = CMD_END;
	sendPacket.payload_length = 0;
	sendPacket.checksum = 0;
	memset(sendPacket.payload, 0, sizeof(sendPacket.payload));
	
	UART2_Send_data(tx_buffer, strlen((char*) tx_buffer));
	HAL_UART_Receive_IT(&huart2, &rx_buffer[0], 1);
}

void UART2_Send_data(uint8_t* pData, uint16_t len)
{	
	HAL_UART_Transmit(&huart2, pData, len+4, 15);	
}

uint8_t calculate_checksum(uint8_t* payload, uint8_t len) {
    uint8_t sum = 0;
    for (int i = 0; i < len; i++) {
        sum += payload[i];
    }
    return ~sum;  // Return the one's complement of the sum
}

uint8_t makePacket(uint8_t* pData, uint16_t len) 
{
	uint8_t nRet = 0;
	tx_buffer[0] = CMD_ST;
	tx_buffer[1] = len;
	memcpy(&tx_buffer[2], pData, len);
	tx_buffer[2+len] = calculate_checksum(&tx_buffer[2], len);
	tx_buffer[3+len] = CMD_END;
	tx_buffer[5+len] = 0;
	return nRet;	
}

void UartPacketSend(uint8_t* pData, uint16_t len)
{
	makePacket(pData, len);
	UART2_Send_data((uint8_t*) &tx_buffer, sizeof(len+3));
}

void UartRxCallback(UART_HandleTypeDef *huart)
{
		static uint8_t trigerStart = 0;
		static uint32_t __tm = 0;
    // Receive data continuously and check for the start of packet
    if (rx_buffer[rx_index] == 0xAA) {  // Check for start delimiter
			trigerStart = 1;
			rx_index = 0;
			__tm = HAL_GetTick();
    }
		if (trigerStart && rx_index >= (3 + rx_buffer[1])) {  // Check if full packet is received
				checksum = calculate_checksum(&rx_buffer[2], rx_buffer[1]);
				if (checksum == rx_buffer[rx_index-1] && rx_buffer[rx_index]) {
					flg_packetReceived = 1;
					rx_index = 0;  // Reset index after processing
				} else {
						// Handle checksum error
#if defined(RTT_SEGGER_DEBUGER)
					 SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);
					 SEGGER_RTT_WriteString(0, "packet checksum error");
#endif
				}
				trigerStart = 0;
		} else {
//			if(HAL_GetTick() - __tm > 1000)
//				trigerStart = 0;
		}

    rx_index++; if(rx_index >= RXBUF_SIZE) rx_index = 0;
    HAL_UART_Receive_IT(huart, &rx_buffer[rx_index], 1);  // Receive next byte
}



