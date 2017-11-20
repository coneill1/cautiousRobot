#include <msp430.h>

void turnRight();
void turnLeft();
void reverse();
void straight();

int main() {
    volatile int pcount=0,k,rx,ry,lx,ly,rxt,ryt,idx;
    WDTCTL = WDTPW | WDTHOLD;

    P1DIR |= 0x41;                            // P1.0 output
    P1REN |= 0x20;
    CCTL0 = CCIE;                             // CCR0 interrupt enabled
    CCR0 = 0;
    TACTL = TASSEL_2 + MC_2;                  // SMCLK, contmode
    volatile unsigned int i;


    _BIS_SR( GIE);                 // Enter LPM0 w/ interrupt

    P2DIR |= BIT1 | BIT4; // P2.1 and P2.4 como salida
    P2SEL |= BIT1 | BIT4; // Asociado al Timer_A1

    TA1CCR0 = 20000; // Cargamos el periodo PWM
    //reverse();
    TA1CCTL1 = OUTMOD_7; //Modo7 reset/set
    TA1CCTL2 = OUTMOD_7; //Modo7 reset/set
    TA1CTL = TASSEL_2 + MC_1; // Timer SMCLK Modo UP
    _BIS_SR( GIE);                 // Enter LPM0 w/ interrupt
    while(1){
        if(!(0x20 & P1IN)){                 //
            reverse();
        }
        else{
            straight();
        }
    }
}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{

    P1OUT ^= 0x01;

    CCR0 +=26;                            // Add Offset to CCR0
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
}

