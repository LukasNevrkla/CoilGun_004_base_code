
#include "Arduino.h"
#include "CoilGunCoils.h"

Coils::Coils()
{
}

void Coils::Init()
{
}

void Coils::TurnCoil(byte _stage)
{
	if (CoilsSeq[_stage] != COILS_OFF)
		PORTD = 1 << COIL[CoilsSeq[_stage]];	//COIL[_coil];
	else
		TurnOffCoils();
/*
   Serial.print("Turning on ");
   Serial.print(CoilsSeq[_stage]);
   Serial.println(" coil.");*/
}

void Coils::TurnOffCoils()
{
	PORTD = 0;
	//Serial.print("Turning off coils");
}

