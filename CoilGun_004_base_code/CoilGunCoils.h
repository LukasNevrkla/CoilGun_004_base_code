// CoilGunCoils.h

#pragma once
#include "Arduino.h"
#include "CoilGunPins.h"
#include "CoilGunConfiguration.h"

class Coils
{
public:
	Coils();
	void Init();
	void TurnCoil(byte _stage);
	void TurnOffCoils();

private:

};
