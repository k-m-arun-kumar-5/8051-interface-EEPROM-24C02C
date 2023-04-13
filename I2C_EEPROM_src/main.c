/* ********************************************************************
FILE                   : main.c

PROGRAM DESCRIPTION    : Program for the 8051/8052 with I2C interface to EEPROM module 24C04
                          (Application Task) to write data in EEPROM and read th written data in LCD using 4 bit interface. 
                      									 
	 
AUTHOR                : K.M. Arun Kumar alias Arunkumar Murugeswaran
	 
KNOWN BUGS            : 

NOTE                  :  	   							
                                    
CHANGE LOGS           : 

*****************************************************************************/

#include "main.h"


/*------------------------------------------------------------*-
FUNCTION NAME  : main

DESCRIPTION    :          
								
INPUT          : none

OUTPUT         : 

NOTE           : 
-*------------------------------------------------------------*/

void main(void)
{
	
	/* ========= begin : USER CODE INITIALIZE ========== */
	 ERROR_LED = 0;         //output for MCU
	 UART_Init();  		
	 Reset_Transfer_Parameters();
	 strcpy(i2c_datas.i2c_tx_data_str, "Hello");
	 UART_Tx_Str("EEPROM Written: ");
	 UART_Tx_Str(i2c_datas.i2c_tx_data_str);
	 UART_Tx_Str("\r\n");
	 I2C_Send_Str(I2C_24C02_EEPROM_DATA_ADDR, i2c_datas.i2c_tx_data_str);	 
	 Delay_in_Milli_Sec(50);
	 I2C_Read_Str(I2C_24C02_EEPROM_DATA_ADDR);	
	 UART_Tx_Str("EEPROM Retrieved: ");
	 UART_Tx_Str(i2c_datas.i2c_rcvd_data_str);
	 UART_Tx_Str("\r\n");
	 Delay_in_Milli_Sec(50);
	 ERROR_LED = STATE_OFF;
	 /* ========= end : USER CODE INITIALIZE ========== */	   
     while(1) // Super Loop
     {
		   	
     }
	 return; 
}

/*------------------------------------------------------------*
FUNCTION NAME  : Delay_in_Micro_Sec

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        :   
-*------------------------------------------------------------*/
void Delay_in_Micro_Sec(const unsigned long num_micro_seconds)
{
	unsigned int i = 0;
	
	for (i = 0;  i < num_micro_seconds; ++i);
	return; 	
}

/*------------------------------------------------------------*
FUNCTION NAME  : Delay_in_Milli_Sec

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           :  mSec Delay 11.0592 Mhz 

Func ID        :   
-*------------------------------------------------------------*/
void Delay_in_Milli_Sec (unsigned long int count) 
{  
   
    unsigned int i;		       		// Keil v7.5a 

    while(count) 
    {
        i = 110; 
	while(i>0) i--;
        count--;
    }
}

/*------------------------------------------------------------*
FUNCTION NAME  : Delay_Time_By_Count

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        :    
-*------------------------------------------------------------*/
void Delay_Time_By_Count(long count_val)
{
	 while(count_val--);
	 return;
}

/*------------------------------------------------------------*-
FUNCTION NAME  : Write_Bit_in_Data

DESCRIPTION     : write bit valve to data's bit, without affecting other bits of data .
                . 0 is the least bit pos and 7 is the most bit pos 

INPUT          : 

OUTPUT         : none

NOTE           : 
-*------------------------------------------------------------*/
void Write_Bit_in_Data(unsigned int *const data_ptr, const unsigned int bit_pos, const unsigned int set_bit_val )
{
    /* unsigned int bit_pos_data_val = 0x01; // 00000001
	 
      // Left shift appropriate number of places, 	 so for bit_pos = 2, then bit_pos_data_val = 00000100 /
      bit_pos_data_val <<= bit_pos;
     // If we want 1 to be written at this bit_pos of data
     if (set_bit_val == 1)
     {
	    // set 1 to bit_pos and all other bits of data are unchanged 
        *data |= bit_pos_data_val; 
        return;
     }
      // If we want 0 bit value at bit_pos, then only that bit_pos of data is set to 0   and all other bits of data are unchanged. /
     bit_pos_data_val = ~bit_pos_data_val; // Complement
     // if bit_pos = 2, then  bit_pos_data_val= 11111011 /
	 // Bitwise AND 
     *data &= bit_pos_data_val; */
	 
	 if (set_bit_val == 1)
        Set_Bit_in_Data(data_ptr, bit_pos);
     else
       Clear_Bit_in_Data(data_ptr, bit_pos ); 
   return;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Str_Fill_Char

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        :    
-*------------------------------------------------------------*/
unsigned int Str_Fill_Char(char *const dest_str, const unsigned char num_chars, const char fill_char)
{
	unsigned char index;
	
	if(dest_str == NULL_PTR || num_chars > STR_MAX_NUM_CHARS)
	{
		UART_Tx_Str("ERR: Str_Fill\r");
		return ERR_INVALID_DATA;
	}
	for (index = 0 ; index < num_chars ; ++index)
	   *(dest_str + index)  = fill_char;
    *(dest_str + index) = NULL_CHAR;
	
	return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Interrupt_Init

DESCRIPTION    :
								
INPUT          : 

OUTPUT         : 

NOTE           : 

Func ID        :   
-*------------------------------------------------------------*/
void Global_Interrupt_Enable()
{
	EA = 1;
    return; 	
}
/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/	 
