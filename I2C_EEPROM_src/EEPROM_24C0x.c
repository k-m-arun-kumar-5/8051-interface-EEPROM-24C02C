/* ********************************************************************
   FILE                   : EEPROM_24C0x.c

   PROGRAM DESCRIPTION    : 
                      									 
	 
   AUTHOR                :  K.M. Arun Kumar alias Arunkumar Murugeswaran 
	 
   KNOWN BUGS            : 

   NOTE                  :  										
                                    
   CHANGE LOGS           : 

*****************************************************************************/
#include "main.h"

 i2c_datas_t i2c_datas;
/*------------------------------------------------------------*
FUNCTION NAME  : I2C_Write_EEPROM_24C02

DESCRIPTION    :
								
INPUT          : none

OUTPUT         : 

NOTE           : 

Func ID        : 21   
-*------------------------------------------------------------*/
void I2C_Write_EEPROM_24C02_Byte(const unsigned long int data_addr, unsigned char tx_char)
{    
    bit ack_flag = NO_ACK;
	 
      I2C_Sent_Start();
			i2c_datas.i2c_flag_status.i2c_state = I2C_START;
		  I2C_Send_Dev_Addr(I2C_24C02_EEPROM_DEV_ADDR, I2C_WRITE);
		  i2c_datas.i2c_flag_status.i2c_state = I2C_ADDR;
	      I2C_Write((unsigned char)( data_addr >> 8) & 0xFF);	// send address high
	     I2C_Write((unsigned char) data_addr & 0xFF);		// send address low
			i2c_datas.i2c_flag_status.i2c_state = I2C_WRITE_SEQ;
         i2c_datas.i2c_num_data_chars_transmitted = strlen(i2c_datas.i2c_tx_data_str); 
	    ack_flag = I2C_Write(tx_char);                				
		 
			i2c_datas.i2c_flag_status.i2c_state = I2C_STOP;
		  I2C_Sent_Stop();
		  i2c_datas.i2c_flag_status.i2c_state = I2C_IDLE;		
}

/*------------------------------------------------------------*
FUNCTION NAME  : I2C_Read_EEPROM_24C02

DESCRIPTION    :
								
INPUT          : none

OUTPUT         : 

NOTE           : 

Func ID        : 21   
-*------------------------------------------------------------*/
unsigned char I2C_Read_EEPROM_24C02_Byte(const unsigned long int data_addr)
{    
    char rcvd_data;
	 bit ack_flag = NO_ACK;
	 
     I2C_Sent_Start();
	 i2c_datas.i2c_flag_status.i2c_state = I2C_START;
	 ack_flag = I2C_Send_Dev_Addr(I2C_24C02_EEPROM_DEV_ADDR, I2C_WRITE);
	 ack_flag = I2C_Write((unsigned char)(data_addr >> 8) & 0xFF);	// send address high
	 ack_flag = I2C_Write((unsigned char) data_addr & 0xFF);		// send address low
	 I2C_Sent_Start();
	 I2C_Send_Dev_Addr(I2C_24C02_EEPROM_DEV_ADDR, I2C_READ);
	 rcvd_data = I2C_Read(NO_ACK);
	 i2c_datas.i2c_flag_status.i2c_state = I2C_STOP;
	 I2C_Sent_Stop();
	 i2c_datas.i2c_flag_status.i2c_state = I2C_IDLE;	
     return rcvd_data;	 
}

/*------------------------------------------------------------*
FUNCTION NAME  : I2C_Send_Str

DESCRIPTION    :
								
INPUT          : none

OUTPUT         : 

NOTE           : 

Func ID        : 21   
-*------------------------------------------------------------*/
void I2C_Send_Str(const unsigned char addr, const unsigned char *str)
{
  I2C_Sent_Start();
  I2C_Send_Dev_Addr(I2C_24C02_EEPROM_DEV_ADDR, I2C_WRITE);
  I2C_Write(addr);
  while(*str)
  {
     I2C_Write(*str++);
  }
  I2C_Sent_Stop();
}

/*------------------------------------------------------------*
FUNCTION NAME  : I2C_Send_Str

DESCRIPTION    :
								
INPUT          : none

OUTPUT         : 

NOTE           : 

Func ID        : 21   
-*------------------------------------------------------------*/
void I2C_Read_Str(unsigned char data_addr)
{
  unsigned char i, j, rcvd_char;
  bit ack_flag;
	
  I2C_Sent_Start();
  ack_flag = I2C_Send_Dev_Addr(I2C_24C02_EEPROM_DEV_ADDR, I2C_WRITE);
  ack_flag = I2C_Write((unsigned char)(data_addr >> 8) & 0xFF);	// send address high
  ack_flag = I2C_Write((unsigned char) data_addr & 0xFF);		// send address low
  for(i=0, j =0; i < 10; i++)
  {
	  I2C_Sent_Start();
      I2C_Send_Dev_Addr(I2C_24C02_EEPROM_DEV_ADDR, I2C_READ); 
      rcvd_char = I2C_Read(NO_ACK);
	  if(rcvd_char != INVALID_I2C_OPER_CHAR)
	  {
		  i2c_datas.i2c_rcvd_data_str[j++] = rcvd_char;
	  }		  
      I2C_Sent_Stop();	  
  } 
  i2c_datas.i2c_rcvd_data_str[j] = NULL_CHAR;
  return;
}
/*------------------------------------------------------------*
FUNCTION NAME  : 

DESCRIPTION    :
								
INPUT          : none

OUTPUT         : 

NOTE           : 

Func ID        : 32   
-*------------------------------------------------------------*/
 void Reset_Transfer_Parameters()
{
	i2c_datas.i2c_error_status_type = I2C_NO_ERROR;
	i2c_datas.i2c_num_data_chars_received = 0;
	memset(i2c_datas.i2c_rcvd_data_str, NULL_CHAR, MAX_COMM_NUM_CHARS + 1);
	i2c_datas.i2c_flag_status.is_rcvd_end_data_char_flag = STATE_NO;
	i2c_datas.i2c_flag_status.is_rcvd_data_terminator_flag = STATE_NO;
	
	i2c_datas.i2c_flag_status.is_tx_data_terminator_flag = STATE_NO; 
	i2c_datas.i2c_num_data_chars_transmitted = 0;
	memset(i2c_datas.i2c_tx_data_str, NULL_CHAR, MAX_COMM_NUM_CHARS + 1);	
	i2c_datas.i2c_flag_status.is_tx_end_data_char_flag = STATE_NO;
  i2c_datas.i2c_flag_status.i2c_state	= I2C_IDLE;
} 


 /*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
