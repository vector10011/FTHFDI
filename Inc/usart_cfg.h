#include "stm32h723xx.h"
#include <stdint.h>

#define                 USART3_EN()                                       (RCC->APB1LENR |= RCC_APB1LENR_USART3EN)
#define                 USART3_DMA_EN()                                   (RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN)
#define                 USART3_DMA                                        DMA1
#define                 USART3_IRQn                                       USART3_IRQn
#define                 USART3_IRQHandler                                 USART3_IRQHandler

#define                 USART3_TX_PORT_EN()                               (RCC->AHB4ENR |= RCC_AHB4ENR_GPIODEN)
#define                 USART3_TX_PORT                                    GPIOD
#define                 USART3_TX_PIN                                     8UL
#define                 USART3_TX_DMA_STREAM                              DMA1_Stream2
#define                 USART3_TX_DMAMUX_INPUT                            46UL
#define                 USART3_TX_DMAMUX_CH                               DMAMUX1_Channel2
#define                 USART3_TX_DMA_STREAM_IRQn                         DMA1_Stream2_IRQn
#define                 USART3_TX_DMA_STREAM_IRQHandler                   DMA_STR2_IRQHandler

#define                 USART3_RX_PORT_EN()                               (RCC->AHB4ENR |= RCC_AHB4ENR_GPIODEN)
#define                 USART3_RX_PORT                                    GPIOD
#define                 USART3_RX_PIN                                     9UL
#define                 USART3_RX_DMA_STREAM                              DMA1_Stream3
#define                 USART3_RX_DMAMUX_INPUT                            45UL
#define                 USART3_RX_DMAMUX_CH                               DMAMUX1_Channel3
#define                 USART3_RX_DMA_STREAM_IRQn                         DMA1_Stream3_IRQn
#define                 USART3_RX_DMA_STREAM_IRQHandler                   DMA_STR3_IRQHandler

extern volatile uint8_t usart3_tx_buf[0xFF];
extern volatile uint8_t usart3_rx_buf[0xFF];

void usart3_init(void);