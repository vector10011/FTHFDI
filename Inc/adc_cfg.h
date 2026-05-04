#include "stm32h723xx.h"

#define                 CUR_SEN_ADC_IN                                  2UL
#define                 ADC1_INP2_PORT_EN()                             (RCC->AHB4ENR |= RCC_AHB4ENR_GPIOFEN)
#define                 ADC1_INP2_PORT                                  GPIOF
#define                 ADC1_INP2_PIN                                   11UL

#define                 ADC1_IRQn                                       ADC_IRQn
#define                 ADC1_IRQHandler                                 ADC1_2_IRQHandler
#define                 ADC1_DMA_EN()                                   (RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN)
#define                 ADC1_DMA                                        DMA1
#define                 ADC1_DMA_STREAM                                 DMA1_Stream4

#define                 ADC1_DMAMUX_INPUT                               9UL
#define                 ADC1_DMAMUX_CH                                  DMAMUX1_Channel4

#define                 ADC1_DMA_STREAM_IRQn                            DMA1_Stream4_IRQn
#define                 ADC1_DMA_STREAM_IRQHandler                      DMA_STR4_IRQHandler

#define                 CUR_SEN_PORT_EN()                               ADC1_INP2_PORT_EN()
#define                 CUR_SEN_PORT                                    ADC1_INP2_PORT
#define                 CUR_SEN_PIN                                     ADC1_INP2_PIN

#define                 CUR_SEN_ADC_EN()                                (RCC->AHB1ENR |= RCC_AHB1ENR_ADC12EN)
#define                 CUR_SEN_ADC                                     ADC1
#define                 CUR_SEN_ADC_IRQn                                ADC1_IRQn
#define                 CUR_SEN_ADC_IRQHandler                          ADC1_IRQHandler

#define                 CUR_SEN_DMA_EN()                                ADC1_DMA_EN()
#define                 CUR_SEN_DMA                                     ADC1_DMA
#define                 CUR_SEN_DMA_STREAM                              ADC1_DMA_STREAM

#define                 CUR_SEN_DMAMUX_INPUT                            ADC1_DMAMUX_INPUT
#define                 CUR_SEN_DMAMUX_CH                               ADC1_DMAMUX_CH

#define                 CUR_SEN_DMA_STREAM_IRQn                         ADC1_DMA_STREAM_IRQn
#define                 CUR_SEN_DMA_STREAM_IRQHandler                   ADC1_DMA_STREAM_IRQHandler

extern volatile uint16_t cur_sen_adc_val;

void cur_sen_adc_init(void);