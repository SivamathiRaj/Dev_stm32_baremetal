#include <stdint.h>
#define RCC_APB1ENR (*(volatile uint32_t *)0x4002101C)
#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018)

typedef struct
{
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
} GPIO_TypeDef;

typedef struct
{
    volatile uint32_t CR1;   
    volatile uint32_t CR2;   
    volatile uint32_t SMCR;  
    volatile uint32_t DIER;  
    volatile uint32_t SR;    
    volatile uint32_t EGR;   
    volatile uint32_t CCMR1; 
    volatile uint32_t CCMR2; 
    volatile uint32_t CCER;  
    volatile uint32_t CNT;   
    volatile uint32_t PSC;   
    volatile uint32_t ARR;   
} TIM_TypeDef;

#define PORTC ((GPIO_TypeDef *)0x40011000)
#define TIM2  ((TIM_TypeDef *)0x40000000)

void timer2_init(void);
void delay_us(uint16_t us);
void delay_ms(uint16_t ms);

int main(void)
{
   
        timer2_init();

        RCC_APB2ENR |= (1 << 4);
        PORTC->CRH &= ~(0xF << 20);
        PORTC->CRH |=  (0x2 << 20);

        while (1)
        {
            PORTC->ODR ^= (1 << 13);
            delay_ms(1000);
        }

}

void timer2_init(void)
{
    RCC_APB1ENR |= (1 << 0); 
    TIM2->PSC = 7;          
    TIM2->ARR = 0xFFFF;      
    TIM2->CR1 |= (1 << 0);  
}

void delay_us(uint16_t us)
{
    TIM2->CNT = 0; 
    while (TIM2->CNT < us); 
}

void delay_ms(uint16_t ms)
{
    for (uint16_t i = 0; i < ms; i++)
    {
        delay_us(1000); 
    }
}
