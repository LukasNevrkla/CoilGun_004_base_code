#pragma once

#define ALL_SENSORS_CNT 6
#define ALL_COILS_CNT 6

#define SENSORS_CNT 3
#define COILS_CNT 6

#define MESUREMENT_ON true
#define COILS_ON false  //dokonefie!!!!!!!!!!!

#define TWO_DETECTS_PER_SENSOR true
#define START_BY_BUTTON true	//Else by first sensor detect

#define CUT_OFF_TIME 1000

#define PR_LEN 6.5	//PROJECTILE_LENGTH

#define DETECTION_CNT (TWO_DETECTS_PER_SENSOR? SENSORS_CNT * 2 : SENSORS_CNT)
#define MESUREMENTS (DETECTION_CNT)// - (START_BY_BUTTON ? 0 : 1))

#define COILS_OFF 200

const byte CoilsSeq[DETECTION_CNT] = { 0,1,COILS_OFF,COILS_OFF};	//Define wich and when should be coils turned on
const byte SensorSeq[DETECTION_CNT] = { 0,0,2,2,3,3};	//Define wich sensors will increase the state (after they trigger)
const double Distances[MESUREMENTS] = { 10, PR_LEN,15-PR_LEN, PR_LEN,15-PR_LEN, PR_LEN };	//If not started by button first distance will not be used (but must be here) 



