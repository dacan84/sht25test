//==============================================================================
//    S E N S I R I O N   AG,  Laubisruetistr. 50, CH-8712 Staefa, Switzerland
//==============================================================================
// Project   :  SHT2x Sample Code (V1.2)
// File      :  System.c
// Author    :  MST
// Controller:  NEC V850/SG3 (uPD70F3740)
// Compiler  :  IAR compiler for V850 (3.50A)
// Brief     :  System functions
//==============================================================================

//---------- Includes ----------------------------------------------------------
#include "System.h"

//==============================================================================
void Init_HW (void)
//==============================================================================
{
}

//==============================================================================
//#pragma optimize = s none
void DelayMicroSeconds (u32t nbrOfUs)
//==============================================================================
{
	u32t i=0;
  for(i=0; i<nbrOfUs; i++)
  {  //__asm("nop");  //nop's may be added for timing adjustment
  }
}
