/*
 * RD_Mess_Data.h
 *
 *  Created on: Oct 7, 2021
 *      Author: PC2
 */

#ifndef RD_MESS_DATA_H_
#define RD_MESS_DATA_H_
#include "proj_lib/sig_mesh/app_mesh.h"
#include "../RD_Type_Device/RD_Type_Device.h"
#include "vendor/common/lighting_model.h"
#include "drivers/8258/flash.h"
#include "../../proj_lib/sig_mesh/app_mesh.h"
#include "vendor/Training_CCT/Training_CCT.h"

#define RD_MAXRESPONESEND 		(2)
#define RD_CODE_PRODONE_L 		 0x06
#define RD_CODE_PRODONE_H 		 0x13

#define mesh_cmd_sig_RD_respone_status_type      (0)

extern int flag_kickout;
extern int flag_training_test2;

extern char UART_TempSend[128];
extern u16 unicast_id;
extern _Bool flag_unicast_id;
extern _Bool flag_check_mess;
extern _Bool flag_process_security;

int RD_Messenger_Training_Test2(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par);
int RD_Messenger_BindAll(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par);

int RD_Messenger_Security(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par);
void Process_Kickout_Security();
unsigned char modulo_calculate(unsigned short par1,unsigned short par2,unsigned short *out);
int crypt(unsigned char *data);

void KickoutALL(void);
void Tranining_2(void);

#endif /* RD_MESS_DATA_H_ */
