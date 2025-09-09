#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

#define RED_LED (1<<1)
#define BLUE_LED (1<<2)
#define GREEN_LED (1<<3)
#define SW1 (1<<0)
#define SW2 (1<<4)

#define ENABLE (1<<0)
#define COUNT (1<<16)
#define CLK_SRC (1<<2)

#define STCTRL (*((volatile uint32_t *)0xE000E010))
#define STRELOAD (*((volatile uint32_t *)0xE000E014))
#define STCURRENT (*((volatile uint32_t *)0xE000E018))

int main(void)
{
    SYSCTL_RCGC2_R |= 0x00000020;//Enable GPIO

    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R = 0x1F;

    GPIO_PORTF_DEN_R |= 0x1F;
    GPIO_PORTF_DIR_R |= 0x0E;

    GPIO_PORTF_PUR_R = 0x11;

    GPIO_PORTF_DATA_R = 0x00;

    //SETUP
    STRELOAD = 0x7A1200; //clkfreq = 16 MHz
    STCTRL |= (1<<2);
    int x;
    while(1){
        STCTRL |= 1;
        x=0;

        GPIO_PORTF_DATA_R ^= RED_LED;
        //DELAY_LOOP
        while (x==0){
            x = STCTRL & (1<<16); //CHECK IF COUNT == 1, IF YES THEN THE TIMER HAS CROSSED 0 THEN COME OUT OF LOOP
        }


        //disable the timer
        STCTRL &= ~ENABLE;
        STCURRENT = 0x0;
        STCTRL |= ENABLE;
        }
}
