#define                 NANOPRINTF_USE_FIELD_WIDTH_FORMAT_SPECIFIERS    1
#define                 NANOPRINTF_USE_PRECISION_FORMAT_SPECIFIERS      0
#define                 NANOPRINTF_USE_LARGE_FORMAT_SPECIFIERS          0
#define                 NANOPRINTF_USE_SMALL_FORMAT_SPECIFIERS          0
#define                 NANOPRINTF_USE_FLOAT_FORMAT_SPECIFIERS          0
#define                 NANOPRINTF_USE_BINARY_FORMAT_SPECIFIERS         1
#define                 NANOPRINTF_USE_WRITEBACK_FORMAT_SPECIFIERS      0

#define NANOPRINTF_IMPLEMENTATION
#include "nanoprintf.h"

#include "usart_cfg.h"
#include "stm32h723xx.h"

volatile uint8_t usart3_tx_buf[0xFF];
volatile uint8_t usart3_rx_buf[0xFF];

void usart3_init(void)
{
    USART3_TX_PORT_EN();
    USART3_TX_PORT->MODER &= ~(0x3UL << (USART3_TX_PIN * 2));
    USART3_TX_PORT->MODER |= 0x2UL << (USART3_TX_PIN * 2);
    USART3_TX_PORT->AFR[USART3_TX_PIN / 8] &= ~(0xFUL << ((USART3_TX_PIN % 8) * 4));
    USART3_TX_PORT->AFR[USART3_TX_PIN / 8] |= 7UL << ((USART3_TX_PIN % 8) * 4);

    USART3_RX_PORT_EN();
    USART3_RX_PORT->MODER &= ~(0x3UL << (USART3_RX_PIN * 2));
    USART3_RX_PORT->MODER |= 0x2UL << (USART3_RX_PIN * 2);
    USART3_RX_PORT->AFR[USART3_RX_PIN / 8] &= ~(0xFUL << ((USART3_RX_PIN % 8) * 4));
    USART3_RX_PORT->AFR[USART3_RX_PIN / 8] |= 7UL << ((USART3_RX_PIN % 8) * 4);

    // ====================================================================================================

    USART3_DMA_EN();

    USART3_TX_DMAMUX_CH->CCR &= ~DMAMUX_CxCR_DMAREQ_ID;
    USART3_TX_DMAMUX_CH->CCR |= USART3_TX_DMAMUX_INPUT << DMAMUX_CxCR_DMAREQ_ID_Pos;
    // DMAMUX1_RequestGenerator2->RGCR |=  0x3UL << DMAMUX_RGxCR_SIG_ID_Pos |
    //                                     0x1UL << DMAMUX_RGxCR_GPOL_Pos;
    // DMAMUX1_RequestGenerator2->RGCR |= DMAMUX_RGxCR_GE;
    USART3_TX_DMAMUX_CH->CCR |= 0x3UL << DMAMUX_CxCR_SYNC_ID_Pos |
                                0x1UL << DMAMUX_CxCR_SPOL_Pos;
    
    USART3_TX_DMAMUX_CH->CCR |= DMAMUX_CxCR_SE;


    USART3_TX_DMA_STREAM->CR &= ~DMA_SxCR_EN;
    USART3_TX_DMA_STREAM->CR =  0x1U << DMA_SxCR_DIR_Pos |
                                DMA_SxCR_MINC |
                                0x0U << DMA_SxCR_PSIZE_Pos |
                                0x0U << DMA_SxCR_MSIZE_Pos;
    USART3_TX_DMA_STREAM->NDTR = 0UL;
    USART3_TX_DMA_STREAM->PAR = (uint32_t)&USART3->TDR;
    USART3_TX_DMA_STREAM->M0AR = (uint32_t)usart3_tx_buf;
    USART3_TX_DMA_STREAM->CR |= DMA_SxCR_TCIE;
    NVIC_EnableIRQ(USART3_TX_DMA_STREAM_IRQn);
    // USART3_TX_DMA_STREAM->CR |= DMA_SxCR_EN;

    USART3_RX_DMAMUX_CH->CCR &= ~DMAMUX_CxCR_DMAREQ_ID;
    USART3_RX_DMAMUX_CH->CCR |= USART3_RX_DMAMUX_INPUT << DMAMUX_CxCR_DMAREQ_ID_Pos;

    USART3_RX_DMA_STREAM->CR &= ~DMA_SxCR_EN;
    USART3_RX_DMA_STREAM->CR =  0x0U << DMA_SxCR_DIR_Pos |
                                DMA_SxCR_CIRC |
                                DMA_SxCR_MINC |
                                0x0U << DMA_SxCR_PSIZE_Pos |
                                0x0U << DMA_SxCR_MSIZE_Pos;
    USART3_RX_DMA_STREAM->NDTR = 0xFFUL;
    USART3_RX_DMA_STREAM->PAR = (uint32_t)&USART3->RDR;
    USART3_RX_DMA_STREAM->M0AR = (uint32_t)usart3_rx_buf;
    // USART3_RX_DMA_STREAM->CR |= DMA_SxCR_TCIE;
    // NVIC_EnableIRQ(USART3_RX_DMA_STREAM_IRQn);
    // USART3_RX_DMA_STREAM->CR |= DMA_SxCR_EN;

    // ====================================================================================================

    USART3_EN();
    USART3->CR1 |= USART_CR1_TE;
    USART3->CR1 |= USART_CR1_RE;
    USART3->CR3 |= USART_CR3_DMAT;
    USART3->CR3 |= USART_CR3_DMAR;
    USART3->BRR = 275000000 / 2 / 115200;
    // USART3->CR1 |= USART_CR1_IDLEIE;
    NVIC_EnableIRQ(USART3_IRQn);
    
    // ====================================================================================================

    USART3->CR1 |= USART_CR1_UE;
}

void USART3_TX_DMA_STREAM_IRQHandler(void)
{
    if (USART3_DMA->LISR & DMA_LISR_TCIF2)
    {
        USART3_DMA->LIFCR |= DMA_LIFCR_CTCIF2;
        USART3_TX_DMA_STREAM->CR |= DMA_SxCR_EN;
        // Handle transmission complete event
    }
}