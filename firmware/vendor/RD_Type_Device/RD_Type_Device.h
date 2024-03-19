/*
 * RD_Type_Device.h
 *
 *  Created on: Oct 7, 2021
 *      Author: PC2
 */

#ifndef RD_TYPE_DEVICE_H_
#define RD_TYPE_DEVICE_H_

#include "proj/tl_common.h"
#include "proj/mcu/watchdog_i.h"
#include "vendor/common/user_config.h"
#include "proj_lib/rf_drv.h"
#include "proj_lib/pm.h"
#include "proj_lib/ble/blt_config.h"
#include "proj_lib/ble/ll/ll.h"
#include "proj_lib/sig_mesh/app_mesh.h"
#include "../RD_Mess_Data/RD_Mess_Data.h"

typedef struct{
	unsigned char Used[4];
	unsigned char step;
	unsigned char cnt_cycle;
}Flash_Save_Training;

typedef struct{
	u8     Used[4];
	_Bool  Unicast_ID;
	_Bool  Check_mess;
	_Bool  Process_security;
	u8 	   Future;
}Flash_Save_Security;

#define FLASH_SAVE_SECURE_SIZE   8
#define RD_SECURE_FLASH_AREA 	(0x78000)
#define RD_TRAINING_FLASH_AREA 	(0x79000)
#define FLASH_SAVE_TRAINING_SIZE   6
#define RD_CHECK_FLASH_H	0x55
#define RD_CHECK_FLASH_L	0xAA

extern Flash_Save_Security Flash_Save_Security_Val;
void RD_Flash_Security_Init(void);
void RD_Flash_CleanSecurityFlash(void);
void RD_Flash_SaveSecurity(_Bool unicast_id, _Bool process_security, _Bool check_mess);

extern Flash_Save_Training Flash_Save_Training_Val;
void RD_Flash_Training_Init(void);
void RD_Flash_CleanTraining(void);
void RD_Flash_SaveTraining(unsigned char step, unsigned char cycle );
#endif /* RD_TYPE_DEVICE_H_ */
