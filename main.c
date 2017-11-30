#include <msp430.h>

void backUp();
void turnRight();
void turnLeft();
void reverse();
void straight();

int main() {
    volatile int pcount=0,k,rx,ry,lx,ly,rxt,ryt,idx;
    WDTCTL = WDTPW | WDTHOLD;

    volatile unsigned int i;
    P1REN |= 0x20;

    P2DIR |= BIT1 | BIT4; // P2.1 and P2.4 for outputs to servo with PWM
    P2SEL |= BIT1 | BIT4; // associate P2.1 and 2.4 with Timer_A1

    P1DIR |= BIT6; // P1.6 - infrared LED output with PWM
    P1SEL |= BIT6; // associate P1.6 Timer_A0

    TA0CCR0 = 26; // Length of period for PWM for timer A0 (1MHz / 38000Hz)
    TA0CCR1 = 13; // 50% duty cycle on infrared LED (P1.6)
    TA0CCTL1 = OUTMOD_7; //Mode7 reset/set
    TA0CTL = TASSEL_2 + MC_1; // Timer SMCLK Mode UP

    TA1CCR0 = 20000; // Length of period for PWM for timer A1 (20000Hz / 1MHz -> .002 sec (2 msec))
    TA1CCTL1 = OUTMOD_7; // Mode7 reset/set
    TA1CCTL2 = OUTMOD_7; // Mode7 reset/set
    TA1CTL = TASSEL_2 + MC_1; // Timer SMCLK Mode UP

    while(1){
        if(!(0x20 & P1IN)){                 //
            backUp();
            turnLeft();
        }
        else{
            straight();
        }
    }
}

void backUp() {
    volatile unsigned int i, j;

    for(i = 0; i < 2; i++) {
        for(j = 0; j < 60000; j++) {
                reverse();
        }
    }
}

void straight() {
    TA1CCR1 = 1000;
    TA1CCR2 = 2000;
}

void reverse() {
    TA1CCR1 = 2000;
    TA1CCR2 = 1000;
}

void turnRight() {
    TA1CCR1 = 2000;
    TA1CCR2 = 2000;
}

void turnLeft() {
    TA1CCR1 = 1000;
    TA1CCR2 = 1000;

    volatile unsigned int i, j;

    for(i = 0; i < 2; i++) {
        for(j = 0; j < 60000; j++) {

        }
    }
}

