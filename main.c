#include "stm32f10x.h"

#define CR1_EN			(1<<0)
#define TIM2_EN			(1<<0)
#define SR_UIF			(1<<0)

#define GPIOC_EN		(1<<4)
#define	PIN13				(1<<13)
#define	LED					 PIN13

void tim2_1hz_init(void);

void tim2_1hz_init(void)
{
			/* Enable clock access to timer 2*/
			RCC->APB1ENR |= TIM2_EN;
			
			/* Set prescalar value */
			//TIM2->PSC = 1600 - 1;
			TIM2->PSC = 10000 - 1;
	
			/* Set Auto reload value */
			//TIM2->ARR = 10000 - 1;
			TIM2->ARR = 7200 - 1;
	
			/* Clear counter */
			TIM2->CNT = 0;
	
			/* Enable timer */
			TIM2->CR1 = CR1_EN;
}	

int main()
{
			/*Enable clock access to GPIOA*/
			RCC->APB2ENR	|= GPIOC_EN;
	
			/*Set PC13 output pin*/
			GPIOC->CRH &= ~((1UL<<23) | (1UL<<22) | (1UL<<20));
			GPIOC->CRH |= (1<<21);
	
			/* Initialize the timer function */
			tim2_1hz_init();
	
			while(1)
			{
					/* Wait for Update Interrupt Flag (UIF)*/
					while(!(TIM2->SR & SR_UIF)){}
						
					/* Clear UIF*/
					TIM2->SR &=~SR_UIF;
						
					/* Toggle the LED*/	
					GPIOC->ODR ^= LED;	
			}	
}	

