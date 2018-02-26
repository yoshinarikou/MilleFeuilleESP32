#ifndef ___MILLE_FEUILLE_H___
#define ___MILLE_FEUILLE_H___
 
#include "MILLE.h"

//////////////
//IO setting//
//////////////
//#define ARDUNOUNO
//#define ESP32

#define NUM_OUTPUT 6
#define NUM_INPUT 5

#ifdef ARDUNOUNO
#define mySoftTX 3
#define mySoftRX 2
#define myMOSI 11
#define myMISO 12
#define mySCK 13
#define myNCS 10
#define mySDA 18
#define mySCL 19
#define myNC 0
#endif

#ifdef ESP32
#define mySoftTX 4
#define mySoftRX 27
#define myMOSI 23
#define myMISO 19
#define mySCK 18
#define myNCS 25
#define mySDA 21
#define mySCL 22
#define myNC 0
#endif


void getWireSetting(uint8_t myPin[4],sDevInfo *DeviceInfomation);
void getWire(uint64_t myAddress, uint8_t *wire, uint8_t connectorNo);
#endif
