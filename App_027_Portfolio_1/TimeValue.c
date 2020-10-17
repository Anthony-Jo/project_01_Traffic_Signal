/*
 * TimeValue.c
 *
 * Created: 2019-09-16 오후 7:56:37
 *  Author: kccistc
 */ 
#include "TIMEVALUE.h"

volatile static uint64_t systick = 0;
static TIME GlobalTime = {0,0,0};

void getTime(TIME *pTime)
{
   *pTime = GlobalTime;
}

void Timer0_OVF_Interrupt_Callback()
{
   static uint64_t pretick = 0;
   systick++;
   
   if(systick - pretick >= 1000)
   {
      pretick = systick;
      (GlobalTime.second)++;
   }
   
   if((GlobalTime.second) >= 60)
   {
      (GlobalTime.second) = 0;
      (GlobalTime.minute)++;
   }

   if((GlobalTime.minute) >= 60)
   {
      (GlobalTime.minute) = 0;
      (GlobalTime.time)++;
   }

   if((GlobalTime.minute) >= 60)
   {
      (GlobalTime.minute) = 0;
      (GlobalTime.time)++;
   }
   
   if((GlobalTime.time) >= 24)
   {
      (GlobalTime.time) = 0;
   }

   TCNT0 = 5;
}


void Timer0Init()
{
   TCNT0 = 5;
   
   TCCR0 |= (1 << CS02 | 0 << CS01 | 0<< CS00);
   TIMSK |= (1 << TOIE0);
}

uint8_t Delay(uint32_t timeDelay)            //딜레이 값을 인자로 받아서 함수 최초 호출 시간을 기록 호출 될 때 마다 현재시간과 비교하여 딜레이 값 만큼 경과하면 함수를 초기화 후 딜레이가 끝났음(1)을 반환하는 함수
{                                    //딜레이 값만큼 경과 하지 않으면 0일 반환 후 다음 호출에 다시 비교
   static uint8_t delayOnFlag = 0;
   static uint32_t prevTime = 0;
   uint32_t curTime = 0;
   
   curTime = GetSystick();
   
   if (delayOnFlag == 0)
   {
      delayOnFlag = 1;
      prevTime = curTime;
   }
   else if (curTime - prevTime > timeDelay)
   {
      delayOnFlag = 0;
      return 1;
   }
   return 0;
}

uint64_t GetSystick()
{
   return systick;
}