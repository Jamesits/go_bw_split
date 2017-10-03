
#include "PWM.h"
void Init_PWM()
{
/*  WDTCTL = WDTPW + WDTHOLD;  
  TACTL=TASSEL_2+TACLR+MC_1;    //MCLK系统主时钟,清零,连续计数模式
  TACCTL1=OUTMOD_7;             //PWM复位/置位
  CCR0=22183;                    //SMCLK时钟下 CCR0=22183频率50HZ.20ms
  CCR1=10000;
  TACCTL2=OUTMOD_7;
  CCR2=5000;
  P1SEL|=BIT2+BIT3;
  P1DIR|=BIT2+BIT3;                  //P1.2作为PWM、CCR1输出 */
  TBCTL=TBSSEL_2 + TBCLR+MC_1;
  TBCCTL1=OUTMOD_7;
  TBCCR0=16000;
  TBCCR1=1000;
  TBCCTL2=OUTMOD_7;
  TBCCR2=1000;
  P4SEL|=BIT2+BIT1;
  P4DIR|=BIT2+BIT1;
}

void Init_TimerA_PWM()    //PWM控制直流减速电机，P2.4作为PWM输出口
{
  TACTL=TASSEL_2+TACLR+MC_1;    //MCLK系统主时钟,清零,连续计数模式
  CCR0=1000;                    //SMCLK时钟下 CCR0=22183频率50HZ.20ms
  TACCTL2=OUTMOD_7;
  CCR2=900;
  P2SEL|=BIT4;
  P2DIR|=BIT4;                  //P2.4作为PWM、CCR1输出 
}

void downEngine(unsigned int Left)//下方舵机，接P4.1口
{
  TBCCR1=Left;
}
/*
void upEngine(unsigned int Left,unsigned int Right)
{
  TBCCR1=Left;
  TBCCR2=Right;
}*/
void turn_left()        //直流减速电机左转
{
  P3DIR |= BIT0 + BIT1;
  P3OUT |= BIT0;
  P3OUT &= ~BIT1;
}

void turn_right()      //直流减速电机右转
{
  P3DIR |= BIT0 + BIT1;
  P3OUT &= ~BIT0;
  P3OUT |= BIT1;
}

void stop()            //直流减速电机停止
{
  P3DIR |= BIT0 + BIT1;
  P3DIR &= ~(BIT0 + BIT1);  
}