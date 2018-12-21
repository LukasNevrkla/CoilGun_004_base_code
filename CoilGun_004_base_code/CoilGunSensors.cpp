
#include "CoilGunSensors.h"
#include "Arduino.h"


Sensors::Sensors()
{

}

void Sensors::Init()
{
#if !START_BY_BUTTON
	SetInterrupt(SensorSeq[0]);
#endif // !START_BY_BUTTON
}

void Sensors::HandleInterrupt(byte _stage)
{
	//Serial.print("I_");
	//Serial.println(_stage);

	#if !START_BY_BUTTON
		if (_stage == 1)
			Start();
	#endif // !START_BY_BUTTON

	#if MESUREMENT_ON
		allTimes[_stage - 1] = micros() - t;
	#endif // MESUREMENT_ON

	SetInterrupt(SensorSeq[_stage]);
}

void Sensors::Start()
{
	#if START_BY_BUTTON
		SetInterrupt(SensorSeq[0]);
	#endif // START_BY_BUTTON

	#if MESUREMENT_ON
		t = micros();
	#endif // MESUREMENT_ON
}

void Sensors::Stop()
{
	#if START_BY_BUTTON
		StopInterrupt();
	#else
		SetInterrupt(SensorSeq[0]);
	#endif // START_BY_BUTTON

	#if MESUREMENT_ON
		CalculateSpeeds();
	#endif // MESUREMENT_ON
}

void Sensors :: SetInterrupt(byte sensor)
{
	cli();
	#ifdef OLD_CG
		PCMSK1 = 1 << SENSOR[sensor];
	#endif // OLD_CG

	#ifdef TEST_CG
		PCMSK2 = 1 << SENSOR[sensor];
	#endif // TEST_CG
	sei();
}

void Sensors :: StopInterrupt()
{
  cli();
  #ifdef OLD_CG
    PCMSK1 = 0;
  #endif // OLD_CG

  #ifdef TEST_CG
    PCMSK2 = 0;
  #endif // TEST_CG
  sei();
}

void Sensors::CalculateSpeeds()
{
	if (MESUREMENTS < 2)	//There is nothing to calculate
		return;

	Serial.println("\tTime \tSpeed");

	for (int i = 0; i < MESUREMENTS; i++)
	{
		double time_1, time_2;

		if (i==0)
			time_1 = 0;
		else
			time_1 = (double)allTimes[i - 1];

		time_2 = (double)allTimes[i];

		time_1 /= 1000000.0;
		time_2 /= 1000000.0;

		double speed = (double)Distances[i] / (time_2 - time_1);

		speed /= 100.0; //to m/s

		Serial.print("\t");
		Serial.print(time_2 - time_1, 6);

		Serial.print(" \t");
		Serial.print(speed, 10);
		Serial.println(" m/s");
	}
}
