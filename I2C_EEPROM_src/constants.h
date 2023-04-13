#ifndef _CONSTANTS_H
#define _CONSTANTS_H

typedef unsigned char tByte;
typedef unsigned int tWord;
typedef unsigned long tLong;

#define STATE_YES                               (1)
#define STATE_NO                                (0) 

#define STATE_ON                               (1)
#define STATE_OFF                              (0) 

#define NULL_PTR                               ((void *) 0)
#define BACKSPACE_CHAR                         ('\b')
#define NULL_CHAR                              ('\0')
#define NEXT_LINE_CHAR                         ('\r')          
#define TERMINATOR_CHAR                        ('\n')

 /* Bit Operation macros */
     /* Set bit pos  in byte data   */
#define Set_Bit_in_Data(data_ptr , bit_pos)                          ((*data_ptr) |=   (1 << (bit_pos)))     
      /* Clear bit pos in byte data */ 
#define Clear_Bit_in_Data(data_ptr ,bit_pos)                         ((*data_ptr) &= (~(1 << (bit_pos))))      
    /* flip bit pos in byte data  */ 
#define Toggle_Bit_in_Data(data_ptr , bit_pos)                       ((*data_ptr) ^=   (1 << (bit_pos)))        
    /* Test if bit pos in byte data  is set   */
#define Test_Bit_Is_Set_in_Data(data_ptr ,bit_pos)                   (((*data_ptr) & (1 << (bit_pos))) &&  (1 << bit_pos))     
   /* Test if bit pos in byte data is clear */  
#define Test_Bit_Is_Clear_in_Data(data_ptr ,bit_pos)                 (!(Test_Bit_Is_Set_in_Data(data_ptr ,bit_pos)))  

typedef enum 
{  
   DISP_NUM_DIGIT1 = 0x01, DISP_NUM_DIGIT2, DISP_NUM_DIGIT3, DISP_NUM_DIGIT4, DISP_NUM_DIGIT5, 
   DISP_HEX_DIGIT4, DISP_HEX_DIGIT3, DISP_HEX_DIGIT2,  DISP_HEX_DIGIT1
} disp_num_t;

typedef struct
{
	long disp_data; 	
	unsigned int  disp_sign           : 1;
	unsigned int  num_digits_format   : 7;		
} disp_format_t;

typedef enum 
{
	 INVALID_EVENT, POLLING, INTERRUPT 
} event_t;

typedef enum
{
	  SUCCESS, ERR_NULL_PTR, ERR_INVALID_DATA  
} system_status_t;

#endif