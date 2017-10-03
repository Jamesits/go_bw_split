
#include "PWM.h"
void Init_PWM()
{
/*  WDTCTL = WDTPW + WDTHOLD;  
  TACTL=TASSEL_2+TACLR+MC_1;    //MCLKϵͳ��ʱ��,����,��������ģʽ
  TACCTL1=OUTMOD_7;             //PWM��λ/��λ
  CCR0=22183;                    //SMCLKʱ���� CCR0=22183Ƶ��50HZ.20ms
  CCR1=10000;
  TACCTL2=OUTMOD_7;
  CCR2=5000;
  P1SEL|=BIT2+BIT3;
  P1DIR|=BIT2+BIT3;                  //P1.2��ΪPWM��CCR1��� */
  TBCTL=TBSSEL_2 + TBCLR+MC_1;
  TBCCTL1=OUTMOD_7;
  TBCCR0=16000;
  TBCCR1=1000;
  TBCCTL2=OUTMOD_7;
  TBCCR2=1000;
  P4SEL|=BIT2+BIT1;
  P4DIR|=BIT2+BIT1;
}

void Init_TimerA_PWM()    //PWM����ֱ�����ٵ����P2.4��ΪPWM�����
{
  TACTL=TASSEL_2+TACLR+MC_1;    //MCLKϵͳ��ʱ��,����,��������ģʽ
  CCR0=1000;                    //SMCLKʱ���� CCR0=22183Ƶ��50HZ.20ms
  TACCTL2=OUTMOD_7;
  CCR2=900;
  P2SEL|=BIT4;
  P2DIR|=BIT4;                  //P2.4��ΪPWM��CCR1��� 
}

void downEngine(unsigned int Left)//�·��������P4.1��
{
  TBCCR1=Left;
}
/*
void upEngine(unsigned int Left,unsigned int Right)
{
  TBCCR1=Left;
  TBCCR2=Right;
}*/
void turn_left()        //ֱ�����ٵ����ת
{
  P3DIR |= BIT0 + BIT1;
  P3OUT |= BIT0;
  P3OUT &= ~BIT1;
}

void turn_right()      //ֱ�����ٵ����ת
{
  P3DIR |= BIT0 + BIT1;
  P3OUT &= ~BIT0;
  P3OUT |= BIT1;
}

void stop()            //ֱ�����ٵ��ֹͣ
{
  P3DIR |= BIT0 + BIT1;
  P3DIR &= ~(BIT0 + BIT1);  
}