// CoilGunSensors.h

#pragma once
#include "Arduino.h"
#include "CoilGunPins.h"
#include "CoilGunConfiguration.h"


class Sensors
{
public:
	Sensors();
	void Init();
	void Start();
	void Stop();
	void HandleInterrupt(byte _stage);
	void SetInterrupt(byte sensor);

private:
	unsigned volatile long t = 0;
	unsigned volatile long *allTimes = new unsigned volatile long[MESUREMENTS];
	unsigned volatile long *allSpeeds = new unsigned volatile long[MESUREMENTS];

	void StopInterrupt();
	void CalculateSpeeds();
};

