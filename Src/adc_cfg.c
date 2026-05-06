#include "adc_cfg.h"

volatile uint16_t cur_sen_adc_val;
volatile uint16_t vol_sen_adc_val;

void cur_sen_adc_init(void)
{
    CUR_SEN_PORT_EN();

    CUR_SEN_PORT->MODER &= ~(0x3UL << (CUR_SEN_PIN * 2));
    CUR_SEN_PORT->MODER |= 0x3UL << (CUR_SEN_PIN * 2);
    // ====================================================================================================
    CUR_SEN_DMA_EN();

    CUR_SEN_DMA_STREAM->CR &= ~DMA_SxCR_EN;
    CUR_SEN_DMA_STREAM->CR = 0x0U << DMA_SxCR_DIR_Pos |
                             DMA_SxCR_CIRC |
                             DMA_SxCR_MINC |
                             0x1U << DMA_SxCR_PSIZE_Pos |
                             0x1U << DMA_SxCR_MSIZE_Pos;
    
    CUR_SEN_DMA_STREAM->NDTR = 1UL;
    CUR_SEN_DMA_STREAM->PAR = (uint32_t)&CUR_SEN_ADC->DR;
    CUR_SEN_DMA_STREAM->M0AR = (uint32_t)&cur_sen_adc_val;

    CUR_SEN_DMAMUX_CH->CCR &= ~DMAMUX_CxCR_DMAREQ_ID;
    CUR_SEN_DMAMUX_CH->CCR |= CUR_SEN_DMAMUX_INPUT << DMAMUX_CxCR_DMAREQ_ID_Pos;

    // CUR_SEN_DMA_STREAM->CR |= DMA_SxCR_TCIE;
    // NVIC_EnableIRQ(CUR_SEN_DMA_STREAM_IRQn);

    CUR_SEN_DMA_STREAM->CR |= DMA_SxCR_EN;
    // ====================================================================================================

    CUR_SEN_ADC_EN();

    ADC12_COMMON->CCR &= ~(ADC_CCR_CKMODE | ADC_CCR_PRESC);
    // ADC12_COMMON->CCR |= 0x3UL << ADC_CCR_CKMODE_Pos;
    
    CUR_SEN_ADC->CR &= ~ADC_CR_BOOST;
    CUR_SEN_ADC->CR |= (0x3UL << ADC_CR_BOOST_Pos);

    CUR_SEN_ADC->CR &= ~ADC_CR_DEEPPWD;
    CUR_SEN_ADC->CR |= ADC_CR_ADVREGEN;
    // for(uint32_t n = 0; n < 10000; n++) __NOP();
    while(!(CUR_SEN_ADC->ISR & ADC_ISR_LDORDY)) __NOP();

    CUR_SEN_ADC->CR &= ~ADC_CR_ADEN;

    CUR_SEN_ADC->CR &= ~ADC_CR_ADCALDIF;
    CUR_SEN_ADC->CR |= ADC_CR_ADCALLIN;
    CUR_SEN_ADC->CR |= ADC_CR_ADCAL;
    while(CUR_SEN_ADC->CR & ADC_CR_ADCAL) __NOP();

    CUR_SEN_ADC->ISR |= ADC_ISR_ADRDY;
    CUR_SEN_ADC->CR  |= ADC_CR_ADEN;
    while (!(CUR_SEN_ADC->ISR & ADC_ISR_ADRDY)) __NOP();

    CUR_SEN_ADC->PCSEL_RES0 |= 1UL << CUR_SEN_ADC_IN;
    CUR_SEN_ADC->DIFSEL_RES12 &= ~(1 << CUR_SEN_ADC_IN);

    CUR_SEN_ADC->CFGR |= 0x3U << ADC_CFGR_DMNGT_Pos |
                         0x5U << ADC_CFGR_RES_Pos |
                         ADC_CFGR_OVRMOD;

    CUR_SEN_ADC->CFGR |= 13U << ADC_CFGR_EXTSEL_Pos |
                         ADC_CFGR_EXTEN_0;
    
    CUR_SEN_ADC->SQR1 = 0x0U;
    CUR_SEN_ADC->SQR1 |= (2UL << ADC_SQR1_SQ1_Pos);

    CUR_SEN_ADC->SMPR1 = 0x0U;
    CUR_SEN_ADC->SMPR1 |= (0x1UL << ADC_SMPR1_SMP2_Pos);

    // CUR_SEN_ADC->IER |= ADC_IER_EOSIE;
    // NVIC_EnableIRQ(CUR_SEN_ADC_IRQn);

    CUR_SEN_ADC->CR |= ADC_CR_ADSTART;
}

void vol_sen_adc_init(void)
{
    VOL_SEN_PORT_EN();

    VOL_SEN_PORT->MODER &= ~(0x3UL << (VOL_SEN_PIN * 2));
    VOL_SEN_PORT->MODER |= 0x3UL << (VOL_SEN_PIN * 2);
    // ====================================================================================================
    VOL_SEN_DMA_EN();

    VOL_SEN_DMA_STREAM->CR &= ~DMA_SxCR_EN;
    VOL_SEN_DMA_STREAM->CR = 0x0U << DMA_SxCR_DIR_Pos |
                             DMA_SxCR_CIRC |
                             DMA_SxCR_MINC |
                             0x1U << DMA_SxCR_PSIZE_Pos |
                             0x1U << DMA_SxCR_MSIZE_Pos;
    
    VOL_SEN_DMA_STREAM->NDTR = 1UL;
    VOL_SEN_DMA_STREAM->PAR = (uint32_t)&VOL_SEN_ADC->DR;
    VOL_SEN_DMA_STREAM->M0AR = (uint32_t)&vol_sen_adc_val;

    VOL_SEN_DMAMUX_CH->CCR &= ~DMAMUX_CxCR_DMAREQ_ID;
    VOL_SEN_DMAMUX_CH->CCR |= VOL_SEN_DMAMUX_INPUT << DMAMUX_CxCR_DMAREQ_ID_Pos;

    // VOL_SEN_DMA_STREAM->CR |= DMA_SxCR_TCIE;
    // NVIC_EnableIRQ(VOL_SEN_DMA_STREAM_IRQn);

    VOL_SEN_DMA_STREAM->CR |= DMA_SxCR_EN;
    // ====================================================================================================

    VOL_SEN_ADC_EN();

    ADC3_COMMON->CCR &= ~(ADC_CCR_CKMODE | ADC_CCR_PRESC);
    // ADC12_COMMON->CCR |= 0x3UL << ADC_CCR_CKMODE_Pos;
    
    // VOL_SEN_ADC->CR &= ~ADC_CR_BOOST;
    // VOL_SEN_ADC->CR |= (0x3UL << ADC_CR_BOOST_Pos);

    VOL_SEN_ADC->CR &= ~ADC_CR_DEEPPWD;
    VOL_SEN_ADC->CR |= ADC_CR_ADVREGEN;
    for(uint32_t n = 0; n < 100000; n++) __NOP();

    VOL_SEN_ADC->CR &= ~ADC_CR_ADEN;

    VOL_SEN_ADC->CR &= ~ADC_CR_ADCALDIF;
    VOL_SEN_ADC->CR |= ADC_CR_ADCALLIN;
    VOL_SEN_ADC->CR |= ADC_CR_ADCAL;
    while(VOL_SEN_ADC->CR & ADC_CR_ADCAL) __NOP();

    VOL_SEN_ADC->ISR |= ADC_ISR_ADRDY;
    VOL_SEN_ADC->CR  |= ADC_CR_ADEN;
    while (!(VOL_SEN_ADC->ISR & ADC_ISR_ADRDY)) __NOP();

    // VOL_SEN_ADC->PCSEL_RES0 |= 1UL << VOL_SEN_ADC_IN;
    VOL_SEN_ADC->LTR2_DIFSEL &= ~(1 << VOL_SEN_ADC_IN);

    VOL_SEN_ADC->CFGR |= ADC3_CFGR_DMAEN |
                         0x1U << ADC3_CFGR_DMACFG_Pos |
                         0x0U << ADC3_CFGR_RES_Pos |
                         ADC_CFGR_OVRMOD;

    VOL_SEN_ADC->CFGR |= 13U << ADC_CFGR_EXTSEL_Pos |
                         ADC_CFGR_EXTEN_0;
    
    VOL_SEN_ADC->SQR1 = 0x0U;
    VOL_SEN_ADC->SQR1 |= (2UL << ADC_SQR1_SQ1_Pos);

    VOL_SEN_ADC->SMPR1 = 0x0U;
    VOL_SEN_ADC->SMPR1 |= (0x1UL << ADC_SMPR1_SMP2_Pos);

    // VOL_SEN_ADC->IER |= ADC_IER_EOSIE;
    // NVIC_EnableIRQ(VOL_SEN_ADC_IRQn);

    VOL_SEN_ADC->CR |= ADC_CR_ADSTART;
}