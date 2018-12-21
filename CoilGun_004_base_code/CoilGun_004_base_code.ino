/*
  Name:		CoilGun_004_base_code.ino
  Created:	16.12.2018 15:01:15
  Author:	luky
*/


#include "CoilGunBase.h"

Base base = Base();

void setup()
{
  base.Init();
}

void loop()
{

}

#ifdef OLD_CG

ISR(PCINT1_vect)
{
	base.SensorsInterrupt();
}

ISR(PCINT0_vect)
{
	base.ButtonInterrupt();
}

ISR(TIMER1_COMPA_vect)
{
	base.Timer_1_Interrupt();
}


#endif // OLD_CG


