// CoilGunBase.h

#pragma once

#include "Arduino.h"
#include "CoilGunPins.h"
#include "CoilGunConfiguration.h"
#include "CoilGunCoils.h"
#include "CoilGunSensors.h"

class Base
{
public:
	Sensors *sensorsClass;
	Coils *coilsClass;

	Base();
	void Init();
	void SensorsInterrupt();
	void ButtonInterrupt();
	void Timer_1_Interrupt();

private:
	volatile bool inProgress = false;
	volatile byte stage = 0;

	void Stop();
	void PinsInit();
	void InterruptsInit();
	void SetTimer(int time);
};

