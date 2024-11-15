/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H__
#define __UART_H__
#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f1xx_hal.h"

#define RXBUF_SIZE		64
#define TXBUF_SIZE		64

#define PACK_LEN		5
#define	CMD_ST			0x03
#define CMD_END			0x0a
#define SBUF_SIZE		128
#define RBUF_SIZE		32

typedef struct {
    uint8_t start_delimiter;  // A unique value indicating the start of a packet
    uint8_t payload_length;   // Length of the payload
    uint8_t payload[PACK_LEN];     // Payload data
    uint8_t checksum;         // Simple checksum
		uint8_t end_delimiter;
} UART_Packet;


extern uint8_t tx_buffer[TXBUF_SIZE];
extern uint8_t rx_buffer[RXBUF_SIZE];
extern uint8_t flg_packetReceived;

void UartInit(void);
void UartRxCallback(UART_HandleTypeDef *huart);
void UART2_Send_data(uint8_t* pData, uint16_t len);
void UartPacketSend(uint8_t* pData, uint16_t len);
#ifdef __cplusplus
}
#endif
#endif /*__UART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
