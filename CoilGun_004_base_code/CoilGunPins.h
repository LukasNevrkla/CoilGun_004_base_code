#pragma once

//Sellect you device (just one)

#define OLD_CG
//#define TEST_CG



#ifdef OLD_CG

#define BUTTON_PIN PB3

const byte SENSOR[] = { PC0, PC1, PC2,PC3,PC4,PC5 };      
const byte COIL[] = { PD2, PD3, PD2, PD5, PD6, PD7 };

#endif // OLD_CG


#ifdef TEST_CG

const byte SENSOR[] = { PD2, PD3, PD4,PD5,PD6,PD7 };	

#define BUTTON_PIN 11          
const byte COILS_PINS[6] = { 2,3,4,5,6,7 }; //PORTD 2-7

#endif // TEST_CG

