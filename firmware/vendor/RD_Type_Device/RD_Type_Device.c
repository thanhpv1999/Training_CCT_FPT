/*
 * RD_Type_Device.c
 *
 *  Created on: Oct 7, 2021
 *      Author: PC2
 */

#include "RD_Type_Device.h"

Flash_Save_Security Flash_Save_Security_Val;
Flash_Save_Training Flash_Save_Training_Val;

void RD_Flash_Training_Init(void)
{
	flash_read_page(RD_TRAINING_FLASH_AREA, FLASH_SAVE_TRAINING_SIZE, (unsigned char *) (&Flash_Save_Training_Val.Used[0]));

	if((Flash_Save_Training_Val.Used[0] != RD_CHECK_FLASH_H) && (Flash_Save_Training_Val.Used[1] != RD_CHECK_FLASH_L)  && (Flash_Save_Training_Val.Used[2] != RD_CHECK_FLASH_H)	&& (Flash_Save_Training_Val.Used[3] != RD_CHECK_FLASH_L) )														// fist time to read reset memory
	{
		RD_Flash_CleanTraining();
	}
	else{
	}
}

void RD_Flash_SaveTraining(unsigned char step, unsigned char cycle )
{
	Flash_Save_Training_Val.step		=  step;
	Flash_Save_Training_Val.cnt_cycle	=  cycle;

	unsigned char *Flash_Data_Buff;
	Flash_Data_Buff = (unsigned char *) (&Flash_Save_Training_Val.Used[0]);

   	flash_erase_sector(RD_TRAINING_FLASH_AREA);
	flash_write_page(RD_TRAINING_FLASH_AREA, FLASH_SAVE_TRAINING_SIZE, Flash_Data_Buff );

	flash_read_page(RD_TRAINING_FLASH_AREA, FLASH_SAVE_TRAINING_SIZE, (unsigned char *)(&Flash_Save_Training_Val.Used[0]));
}

void RD_Flash_CleanTraining(void)
{
	Flash_Save_Training_Val.Used[0] = RD_CHECK_FLASH_H;
	Flash_Save_Training_Val.Used[1] = RD_CHECK_FLASH_L;
	Flash_Save_Training_Val.Used[2] = RD_CHECK_FLASH_H;
	Flash_Save_Training_Val.Used[3] = RD_CHECK_FLASH_L;

	Flash_Save_Training_Val.step			=  0;
	Flash_Save_Training_Val.cnt_cycle		=  0;

	unsigned char *Flash_Data_Buff;
	Flash_Data_Buff = (unsigned char *) (&Flash_Save_Training_Val.Used[0]);

   	flash_erase_sector(RD_TRAINING_FLASH_AREA);
	flash_write_page(RD_TRAINING_FLASH_AREA, FLASH_SAVE_TRAINING_SIZE, Flash_Data_Buff );

	flash_read_page(RD_TRAINING_FLASH_AREA, FLASH_SAVE_TRAINING_SIZE, (unsigned char *) (&Flash_Save_Training_Val.Used[0]));
}


void RD_Flash_Security_Init(void)
{
	flash_read_page(RD_SECURE_FLASH_AREA, FLASH_SAVE_SECURE_SIZE, (unsigned char *) (&Flash_Save_Security_Val.Used[0]));
	if((Flash_Save_Security_Val.Used[0] != RD_CHECK_FLASH_H) && (Flash_Save_Security_Val.Used[1] != RD_CHECK_FLASH_L)  && (Flash_Save_Security_Val.Used[2] != RD_CHECK_FLASH_H)	&& (Flash_Save_Security_Val.Used[3] != RD_CHECK_FLASH_L) )														// fist time to read reset memory
	{
		RD_Flash_CleanSecurityFlash();
	}
	else
	{
		flag_check_mess       = Flash_Save_Security_Val.Check_mess;
		flag_process_security = Flash_Save_Security_Val.Process_security;
		flag_unicast_id		  = Flash_Save_Security_Val.Unicast_ID;

		if((flag_process_security == TRUE) && (flag_check_mess == FALSE)){
			factory_reset();
			start_reboot();
		}
		else{

		}
	}
}

void RD_Flash_CleanSecurityFlash(void)
{
	Flash_Save_Security_Val.Used[0] = RD_CHECK_FLASH_H;
	Flash_Save_Security_Val.Used[1] = RD_CHECK_FLASH_L;
	Flash_Save_Security_Val.Used[2] = RD_CHECK_FLASH_H;
	Flash_Save_Security_Val.Used[3] = RD_CHECK_FLASH_L;

	Flash_Save_Security_Val.Check_mess				=  FALSE;
	Flash_Save_Security_Val.Process_security		=  FALSE;
	Flash_Save_Security_Val.Unicast_ID     			=  FALSE;

	unsigned char *Flash_Data_Buff;
	Flash_Data_Buff = (unsigned char *) (&Flash_Save_Security_Val.Used[0]);

   	flash_erase_sector(RD_SECURE_FLASH_AREA);
	flash_write_page(RD_SECURE_FLASH_AREA, FLASH_SAVE_SECURE_SIZE,Flash_Data_Buff );

	flash_read_page(RD_SECURE_FLASH_AREA, FLASH_SAVE_SECURE_SIZE, (unsigned char *) (&Flash_Save_Security_Val.Used[0]));

	flag_check_mess       = Flash_Save_Security_Val.Check_mess;
	flag_process_security = Flash_Save_Security_Val.Process_security;
	flag_unicast_id			  = Flash_Save_Security_Val.Unicast_ID;
}

void RD_Flash_SaveSecurity(_Bool unicast_id, _Bool process_security, _Bool check_mess)
{
	Flash_Save_Security_Val.Process_security	= process_security;
	Flash_Save_Security_Val.Unicast_ID			= unicast_id;
	Flash_Save_Security_Val.Check_mess			= check_mess;

	unsigned char *Flash_Data_Buff;
	Flash_Data_Buff = (unsigned char *) (&Flash_Save_Security_Val.Used[0]);

   	flash_erase_sector(RD_SECURE_FLASH_AREA);
	flash_write_page(RD_SECURE_FLASH_AREA, FLASH_SAVE_SECURE_SIZE, Flash_Data_Buff );

	flash_read_page(RD_SECURE_FLASH_AREA, FLASH_SAVE_SECURE_SIZE, (unsigned char *) (&Flash_Save_Security_Val.Used[0]));

	flag_check_mess       = Flash_Save_Security_Val.Check_mess;
	flag_process_security = Flash_Save_Security_Val.Process_security;
	flag_unicast_id			  = Flash_Save_Security_Val.Unicast_ID;
}
