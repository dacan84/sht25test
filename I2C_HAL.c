//==============================================================================
//    S E N S I R I O N   AG,  Laubisruetistr. 50, CH-8712 Staefa, Switzerland
//==============================================================================
// Project   :  SHT2x Sample Code (V1.2)
// File      :  I2C_HAL.c
// Author    :  MST
// Controller:  NEC V850/SG3 (uPD70F3740)
// Compiler  :  IAR compiler for V850 (3.50A)
// Brief     :  I2C Hardware abstraction layer
//==============================================================================

//---------- Includes ----------------------------------------------------------
#include "I2C_HAL.h"


//==============================================================================
void I2c_Init()
//==============================================================================
{

	GPIO_setAsOutputPin(GPIO_PORT_P1, SDA); // SDA as output
	GPIO_setAsOutputPin(GPIO_PORT_P1, SCL); //SCL as output
	//SDA = LOW;                // Set port as output for configuration
	//SCL = LOW;                // Set port as output for configuration

	//TODO: Estas dos funciones siguientes Igual sobran
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, SDA);	//set SDA	LOW
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, SCL);	//set SCL	LOW
	//SDA_CONF = LOW;           // Set SDA level as low for output mode
	//SCL_CONF = LOW;           // Set SCL level as low for output mode

	GPIO_setOutputHighOnPin(GPIO_PORT_P1, SDA);	//set SDA  HIGH
	GPIO_setOutputHighOnPin(GPIO_PORT_P1, SCL);	//set SCL  HIGH
	//SDA = HIGH;               // I2C-bus idle mode SDA released (input)
	//SCL = HIGH;               // I2C-bus idle mode SCL released (input)
}

//==============================================================================
void I2c_StartCondition()
//==============================================================================
{
	GPIO_setOutputHighOnPin(GPIO_PORT_P1, SDA);	//set SDA  HIGH
	GPIO_setOutputHighOnPin(GPIO_PORT_P1, SCL);	//set SCL  HIGH
	//SDA = HIGH;
	//SCL = HIGH;
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, SDA);
	//SDA = LOW;
	DelayMicroSeconds(10);  // hold time start condition (t_HD;STA)
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, SCL);
	//SCL = LOW;
	DelayMicroSeconds(10);
}

//==============================================================================
void I2c_StopCondition()
//==============================================================================
{
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, SDA);  //set SDA	LOW
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, SCL);  //set SCL	LOW
	//SDA = LOW;
	//SCL = LOW;
	GPIO_setOutputHighOnPin(GPIO_PORT_P1, SCL);
	//SCL = HIGH;
	DelayMicroSeconds(10);  // set-up time stop condition (t_SU;STO)
	GPIO_setOutputHighOnPin(GPIO_PORT_P1, SDA);
	//SDA = HIGH;
	DelayMicroSeconds(10);
}

//==============================================================================
u8t I2c_WriteByte(u8t txByte)
//==============================================================================
{
	u8t mask, error = 0;
	for (mask = 0x80; mask > 0; mask >>= 1)   //shift bit for masking (8 times)
			{
		if ((mask & txByte) == 0)
			GPIO_setOutputLowOnPin(GPIO_PORT_P1,SDA);//set SDA	LOW
			//SDA = LOW;   //masking txByte, write bit to SDA-Line
		else
			GPIO_setOutputHighOnPin(GPIO_PORT_P1,SDA);//set SDA  HIGH
			//SDA = HIGH;
		DelayMicroSeconds(1);             //data set-up time (t_SU;DAT)
		GPIO_setOutputHighOnPin(GPIO_PORT_P1,SCL);//set SCL HIGH
		//SCL = HIGH;                         //generate clock pulse on SCL
		DelayMicroSeconds(5);             //SCL high time (t_HIGH)
		GPIO_setOutputLowOnPin(GPIO_PORT_P1,SCL);//set SCL	LOW
		//SCL = LOW;
		DelayMicroSeconds(1);             //data hold time(t_HD;DAT)
	}

	GPIO_setOutputHighOnPin(GPIO_PORT_P1,SDA);//set SDA  HIGH
	GPIO_setOutputHighOnPin(GPIO_PORT_P1,SCL);//set SCL HIGH
	//SDA = HIGH;                           //release SDA-line
	//SCL = HIGH;                           //clk #9 for ack
	DelayMicroSeconds(1);               //data set-up time (t_SU;DAT)
	GPIO_setAsInputPin(GPIO_PORT_P1,SDA);//SDA as input
	if ( GPIO_getInputPinValue(GPIO_PORT_P1,SDA) == HIGH)
		error = ACK_ERROR; //check ack from i2c slave
	GPIO_setOutputLowOnPin(GPIO_PORT_P1,SCL);//set SCL	LOW
	//SCL = LOW;
	DelayMicroSeconds(20);              //wait time to see byte package on scope
	return error;                       //return error code
}

//==============================================================================
u8t I2c_ReadByte(etI2cAck ack)
//==============================================================================
{
	u8t mask, rxByte = 0;
	GPIO_setAsInputPin(GPIO_PORT_P1, SDA);
	//SDA = HIGH;                           //release SDA-line
	for (mask = 0x80; mask > 0; mask >>= 1)   //shift bit for masking (8 times)
			{
		GPIO_setOutputHighOnPin(GPIO_PORT_P1, SCL);   //set SCL  HIGH
		//SCL = HIGH;                         //start clock on SCL-line
		DelayMicroSeconds(1);             //data set-up time (t_SU;DAT)
		DelayMicroSeconds(3);             //SCL high time (t_HIGH)
		if (GPIO_getInputPinValue(GPIO_PORT_P1, SDA) == 1)
			rxByte = (rxByte | mask); //read bit
		GPIO_setOutputLowOnPin(GPIO_PORT_P1, SCL); //set SCL  LOW
		//SCL = LOW;
		DelayMicroSeconds(1);             //data hold time(t_HD;DAT)
	}

	// De aqui para abajo es el envío del ACK
	GPIO_setAsOutputPin(GPIO_PORT_P1, SDA);  		// SDA as output
	if (ack == ACK) {
		GPIO_setOutputLowOnPin(GPIO_PORT_P1, SDA);  //set SDA	LOW
	} else {
		GPIO_setOutputHighOnPin(GPIO_PORT_P1, SDA);  //set SDA  HIGH
	}
	//SDA = ack;                            //send acknowledge if necessary

	DelayMicroSeconds(1);               //data set-up time (t_SU;DAT)
	GPIO_setOutputHighOnPin(GPIO_PORT_P1, SCL);               //set SCL  HIGH
	//SCL = HIGH;                           //clk #9 for ack
	DelayMicroSeconds(5);               //SCL high time (t_HIGH)
	GPIO_setOutputLowOnPin(GPIO_PORT_P1, SCL);               //set SCL	LOW
	//SCL = LOW;
	GPIO_setOutputHighOnPin(GPIO_PORT_P1, SDA); //TODO: esta linea no la tengo muy clara,
						// si es esto o definirlo como entrada otra vez para liberar la linea.
						// puede que sea definirla como salida para liberar la linea para el siguiente byte.

	//SDA = HIGH;                           //release SDA-line
	DelayMicroSeconds(20);              //wait time to see byte package on scope
	return rxByte;                      //return error code
}

