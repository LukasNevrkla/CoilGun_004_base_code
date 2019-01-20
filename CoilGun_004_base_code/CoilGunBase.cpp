#include "CoilGunBase.h"
#include "Arduino.h"


Base::Base()
{
  sensorsClass=new Sensors(); 
  coilsClass = new Coils();
}

void Base::Init()
{
	Serial.begin(9600);
	Serial.println("Initialization");

	PinsInit();
	InterruptsInit();

	sensorsClass->Init();
	coilsClass->Init();

	#if START_BY_BUTTON
		stage = 0;
	#else
		stage = 1;	//Bcs there will be no stage++; on button click
	#endif // START_BY_BUTTON

	/*	//Not finished yet
  delay (50);
   
	for (int i = 0; i < SENSORS_CNT; i++)
	{
		if (digitalRead(SENSOR[i])==1)
		{
		  Serial.print("Some error on sensor: ");
		  Serial.print(digitalRead(SENSOR[i]));
		  Serial.println(i);
		}
  }*/

	Serial.println("Complete");
}

void Base::ButtonInterrupt()
{
	#if START_BY_BUTTON
		if (!inProgress)
		{
			inProgress = true;
			stage = 0;

			SetTimer(CUT_OFF_TIME);
			sensorsClass->Start();
			coilsClass->TurnCoil(stage);

			stage++;
		}
	#endif // START_BY_BUTTON
}

void Base::SensorsInterrupt()
{
	//cli();
  sensorsClass->HandleInterrupt(stage);

	#if COILS_ON
		if (stage< COILS_CNT)
			coilsClass->TurnCoil(stage);
		else
			coilsClass->TurnOffCoils();
	#endif //COILS_ON

	//sensorsClass->HandleInterrupt(stage);

	#ifdef DETECTION_END
		if (SensorSeq[stage] == DETECTION_END)
			Stop();
	#endif // DETECTION_END
 
	stage++;

	  if (stage > DETECTION_CNT)
		  Stop();

   //sei();
}

void Base::Stop()
{
	coilsClass->TurnOffCoils();
	#if !START_BY_BUTTON
		stage = 1;
	#endif 
	sensorsClass->Stop();
	inProgress = false;
}


void Base::Timer_1_Interrupt()
{
  coilsClass->TurnOffCoils();
  inProgress = false;
  TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12)); //Stop timer
}

void Base :: PinsInit()
{
	for (byte i=0 ; i< ALL_SENSORS_CNT ; i++)
	{
		pinMode(SENSOR[i], INPUT_PULLUP);
	}
	 for (byte i=0 ; i< ALL_COILS_CNT ; i++)
	 {
		pinMode(COIL[i], OUTPUT);
		digitalWrite(COIL[i], LOW);
	 }	

  pinMode(BUTTON_PIN, INPUT);
}

void Base :: InterruptsInit()
{
	cli();

	#ifdef OLD_CG
		PCICR |= 1 << 1;	//Port C interrup enabled (sensors)
		PCICR |= 1 << 0;      //Port B interrup enabled (button)
		PCMSK0 |= 1 << BUTTON_PIN;
	#endif // OLD_CG

	#ifdef TEST_CG
		PCICR |= (1 << 2);    //Port D interrup enabled (sensors)
	#endif // TEST_CG

    //Must be set or it will produce error when timer will be enabled
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B

	sei();
}

void Base::SetTimer(int time)
{
  double t_seconds=(double) time/1000;
  int frequency=1/t_seconds;

  if (frequency >= 1 && frequency < 1000)
  {
    noInterrupts();
    
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1 = 0;//initialize counter value to 0
    // set compare match register for 1hz increments
    OCR1A = 15625 / frequency;  // = (16*10^6) / (1*1024) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    
    interrupts();
  }
}
