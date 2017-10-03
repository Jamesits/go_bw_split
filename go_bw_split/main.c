#include "msp430x14x.h"
#include "pwm.h"
#include "pwm.c"
#define CPU_F ((double)8000000)                          
#define delayus(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))//宏定义延时函数
#define delayms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
//int flag = 0;
void duoji1()     //下方舵机
{

  downEngine(1800); 
  delayms(40);
  downEngine(900);
}

void  main( void )
{
  // Stop watchdog timer to prevent time out reset

  WDTCTL = WDTPW + WDTHOLD;
  Init_PWM();
  Init_TimerA_PWM();  
  P1IES |= BIT0;     //P1.0作外部中断，接收红外信号，下降沿触发
  P1IE |= BIT0;
  P1DIR &= ~BIT0;
  _EINT(); 
  while(1)
  {
    turn_left();
    delayms(12);
    
    turn_right();
    delayms(6);
    stop();
    delayms(200);

  }
}

#pragma vector = PORT1_VECTOR    //P1口中断向量
__interrupt void PORT1_ISR(void)
{
  P1IFG &=~BIT0;
  if(!(P1IN & BIT0))
  {

    stop();
    duoji1();

  }
}



