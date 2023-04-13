/**************************************************************************
   FILE          :    EEPROM_24C0x.h 
 
   PURPOSE       :    24C02 EEPROM header 
 
   AUTHOR        :    K.M. Arun Kumar alias Arunkumar Murugeswaran 
 
  KNOWN BUGS     :
	
  NOTE           :   
  
  CHANGE LOGS    :
	   
 **************************************************************************/
 /* to avoid this header file to be included more than once, conditional directive is used  */
#ifndef _EEPROM_24C0x_H
#define _EEPROM_24C0x_H

/* -------------------- macro  defination ---------------------------------------- */
#define REQ_TIME_CNT_BEFORE_SENT_STOP_BIT            (100UL)
#define REQ_TIME_CNT_TIME_WAIT                      (1000UL)
#define MAX_COMM_NUM_CHARS                            (20U)

#define DATA_TERMINATOR_CHAR                          ('\\')                 
#define NULL_CHAR                                     ('\0')
#define ENQ_CHAR                                    ('\x05')
#define PADDED_CHAR                                 ('\x80')

/* -------------------- data type defination ---------------------------------------- */

typedef enum {MASTER_I2C_FRAME_FSM_IDLE, MASTER_I2C_FRAME_FSM_WAIT_PASSIVE_OPEN, MASTER_I2C_FRAME_FSM_PASSIVE_OPEN, MASTER_I2C_FRAME_FSM_SENT_START_BIT, MASTER_I2C_FRAME_FSM_SENT_ADDR_WRITE,\
   MASTER_I2C_FRAME_FSM_DATA_SENT_INTR_CMD, MASTER_I2C_FRAME_FSM_SENT_DATA, MASTER_I2C_FRAME_FSM_SENT_ADDR_READ, MASTER_I2C_FRAME_FSM_RCV_DATA, MASTER_I2C_FRAME_FSM_SENT_RESTART_BIT,\
   MASTER_I2C_FRAME_FSM_SENT_STOP_BIT, MASTER_I2C_FRAME_FSM_PROC_RCVD_DATA, MASTER_I2C_FRAME_FSM_TIME_WAIT,  MASTER_I2C_FRAME_FSM_SENT_ADDR_READ1 } master_i2c_frame_fsm_states;

typedef enum { I2C_MASTER_TYPE, I2C_SLAVE_TYPE } i2c_device_types; 
  
typedef enum {I2C_NO_ERROR = 0,  I2C_ERROR} i2c_error_status_types;

typedef struct 
{
	unsigned int is_rcvd_end_data_char_flag: 1;
	unsigned int is_rcvd_data_terminator_flag: 1;
	unsigned int is_tx_data_terminator_flag: 1;
	unsigned int is_tx_end_data_char_flag: 1;
	unsigned int i2c_state               : 4;
} i2c_flag_status_t;
 
typedef struct
{
	char i2c_rcvd_data_str[MAX_COMM_NUM_CHARS + 1];
	char i2c_tx_data_str[MAX_COMM_NUM_CHARS + 1];	
	unsigned char i2c_num_data_chars_received;
	unsigned char i2c_num_data_chars_transmitted;
	unsigned char i2c_error_status_type;
	i2c_flag_status_t i2c_flag_status;
} i2c_datas_t;

/* -------------------- public variable  declaration---------------------------------------- */
extern i2c_datas_t i2c_datas;

/* -------------------- public prototype declaration --------------------------------------- */
void I2C_Write_EEPROM_24C02_Byte(const unsigned long int data_addr, unsigned char tx_char);
unsigned char I2C_Read_EEPROM_24C02_Byte(const unsigned long int data_addr);
void I2C_Send_Str(const unsigned char addr, const unsigned char *str);
void I2C_Read_Str(unsigned char addr);
void Reset_Transfer_Parameters();

#endif

/*------------------------------------------------------------------*-
  ------------------------ END OF FILE ------------------------------
-*------------------------------------------------------------------*/
