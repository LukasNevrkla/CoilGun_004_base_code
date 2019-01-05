#pragma once

#define ALL_SENSORS_CNT 6
#define ALL_COILS_CNT 6

#define SENSORS_CNT 6
#define COILS_CNT 6

#define MESUREMENT_ON true
#define COILS_ON false  

#define TWO_DETECTS_PER_SENSOR true
#define START_BY_BUTTON false	//Else by first sensor detect

#define CUT_OFF_TIME 300

#define PR_LEN 6.8	//PROJECTILE_LENGTH

#define DETECTION_CNT (TWO_DETECTS_PER_SENSOR? SENSORS_CNT * 2 : SENSORS_CNT)
#define MESUREMENTS (DETECTION_CNT)

#define COILS_OFF 200
#define DETECTION_END 201	//Ends whole detection  //dela problemy pri START_BY_BUTTON false

         // 26 k ohm na senzorech   
         //Kdyz je senzor pred 1. civkou (hrebik je v senzoru), nepricte se state... funguje to tatalne de**ne, ..I_1 I_1 I_3 I_4
                   
const byte CoilsSeq[DETECTION_CNT] = { 
	4,COILS_OFF,
	COILS_OFF,COILS_OFF,
	COILS_OFF,COILS_OFF,
	COILS_OFF,COILS_OFF,
	COILS_OFF,COILS_OFF, 
  COILS_OFF,COILS_OFF 
};	//Define wich and when should be coils turned on

const byte SensorSeq[DETECTION_CNT] = { 
	0,0,
	1,1,
  2,2,
	3,3,
	4,4,
  5,5
	//DETECTION_END,DETECTION_END
};	//Define wich sequention in which will be sensors trigger

const double SpeedCalculation[][3] = {
	{0,2,7},
	{2,4,7},
	{4,6,7},
  {6,8,7},
  {8,10,7}
};	//Define between wich detection should be speed calculated (3. number is distance [cm])

const byte AccelerationCalculation[][2] = {
	{0,2},
	{2,4},
	{4,6},
};	//Define between wich detection should be acceleration calculated 

/*
const double Distances[MESUREMENTS] = {
	0, PR_LEN,
	11- PR_LEN,PR_LEN,
	16- PR_LEN,PR_LEN,
	7.5- PR_LEN,PR_LEN,
	7.5- PR_LEN,PR_LEN
};	//If not started by button first distance will not be used (but must be here) 
*/
