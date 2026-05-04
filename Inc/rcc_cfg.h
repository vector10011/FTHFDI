#include "stm32h723xx.h"

#define                 HSE_FREQ                    8

#define                 PLL1_M                      1UL
#define                 PLL1_N                      110UL
#define                 PLL1_P                      1UL

#define                 HPRE                        RCC_D1CFGR_HPRE_DIV2
#define                 D1PPRE                      RCC_D1CFGR_D1PPRE_DIV2
#define                 D1CPRE                      RCC_D1CFGR_D1CPRE_DIV1
#define                 D2PPRE1                     RCC_D2CFGR_D2PPRE1_DIV2
#define                 D2PPRE2                     RCC_D2CFGR_D2PPRE2_DIV2
#define                 D3PPRE                      RCC_D3CFGR_D3PPRE_DIV2

#define                 PLL2_M                      1UL
#define                 PLL2_N                      80UL
#define                 PLL2_P                      4UL

void rcc_init(void);

void pll2_init(void);