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

// ----------------------------------------------------------------------------------------------------

#define                 VOL_SEN_ADC_IN                                  2UL
#define                 ADC3_INP2_PORT_EN()                             (RCC->AHB4ENR |= RCC_AHB4ENR_GPIOFEN)
#define                 ADC3_INP2_PORT                                  GPIOF
#define                 ADC3_INP2_PIN                                   9UL

#define                 ADC3_IRQn                                       ADC3_IRQn
#define                 ADC3_IRQHandler                                 ADC3_IRQHandler
#define                 ADC3_DMA_EN()                                   (RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN)
#define                 ADC3_DMA                                        DMA1
#define                 ADC3_DMA_STREAM                                 DMA1_Stream5

#define                 ADC3_DMAMUX_INPUT                               115UL
#define                 ADC3_DMAMUX_CH                                  DMAMUX1_Channel5

#define                 ADC3_DMA_STREAM_IRQn                            DMA1_Stream5_IRQn
#define                 ADC3_DMA_STREAM_IRQHandler                      DMA_STR5_IRQHandler

#define                 VOL_SEN_PORT_EN()                               ADC3_INP2_PORT_EN()
#define                 VOL_SEN_PORT                                    ADC3_INP2_PORT
#define                 VOL_SEN_PIN                                     ADC3_INP2_PIN

#define                 VOL_SEN_ADC_EN()                                (RCC->AHB4ENR |= RCC_AHB4ENR_ADC3EN)
#define                 VOL_SEN_ADC                                     ADC3
#define                 VOL_SEN_ADC_IRQn                                ADC3_IRQn
#define                 VOL_SEN_ADC_IRQHandler                          ADC3_IRQHandler

#define                 VOL_SEN_DMA_EN()                                ADC3_DMA_EN()
#define                 VOL_SEN_DMA                                     ADC3_DMA
#define                 VOL_SEN_DMA_STREAM                              ADC3_DMA_STREAM

#define                 VOL_SEN_DMAMUX_INPUT                            ADC3_DMAMUX_INPUT
#define                 VOL_SEN_DMAMUX_CH                               ADC3_DMAMUX_CH

#define                 VOL_SEN_DMA_STREAM_IRQn                         ADC3_DMA_STREAM_IRQn
#define                 VOL_SEN_DMA_STREAM_IRQHandler                   ADC3_DMA_STREAM_IRQHandler

// ----------------------------------------------------------------------------------------------------

extern volatile uint16_t cur_sen_adc_val;
extern volatile uint16_t vol_sen_adc_val;

void cur_sen_adc_init(void);

void vol_sen_adc_init(void);