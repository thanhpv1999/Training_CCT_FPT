/*
 * RD_Mess_Data.c
 *
 *  Created on: Oct 7, 2021
 *      Author: PC2
 */

#include"RD_Mess_Data.h"

int flag_training_test2 = 0;
int vr_count = 1;
int flag_kickout = 0;
unsigned char *BuffData;
extern u8 gatt_adv_send_flag;

u16 unicast_id = 0;
int vrs_time_bindall = 0;
int vrs_time_error_unicast = 0;
_Bool flag_unicast_id = FALSE;
_Bool flag_check_mess = FALSE;
_Bool flag_process_security = FALSE;
char UART_TempSend[128];

int RD_Messenger_Training_Test2(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par)
{
		if(get_provision_state() == STATE_DEV_UNPROV){
			flag_training_test2 = 1;
			gatt_adv_send_flag  = 0;
		}
		else {
			flag_training_test2 = 0;
			gatt_adv_send_flag  = 1;
		}
  return 0;
}

int RD_Messenger_BindAll(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par) {
  extern int mesh_cmd_sig_cfg_bind(u8 * par, int par_len, mesh_cb_fun_par_t *cb_par);

  unicast_id = par[1] << 8 | par[0];
  vrs_time_bindall = clock_time_s();
  flag_process_security = TRUE;
  flag_check_mess		= FALSE;

  if (/*(par[4] == RD_CODE_PRODONE_L) && (par[5] == RD_CODE_PRODONE_H) && */(vr_count == 1)) {
	RD_Flash_SaveSecurity(flag_unicast_id, flag_process_security, flag_check_mess);
    vr_count++;
    RD_light_ev_with_sleep(3, 400 * 1000);
    sleep_ms(300);
    light_dim_set_hw(0, 1, get_pwm_cmp(0xff, 255));
    light_dim_set_hw(0, 0, get_pwm_cmp(0xff, 0));
  }
  return (mesh_cmd_sig_cfg_bind(par, par_len,  cb_par));
}

void Process_Kickout_Security(){
	if((flag_process_security == TRUE) && (clock_time_s() - vrs_time_bindall > 60)){
		if((flag_check_mess == FALSE) || (flag_unicast_id == FALSE)){
			flag_process_security = FALSE;
			factory_reset();
			start_reboot();
		}
		else{
			flag_process_security = FALSE;
		}
	}

	if((flag_process_security == TRUE) && (clock_time_s() - vrs_time_error_unicast > 10)){
		if((flag_check_mess == TRUE) && (flag_unicast_id == FALSE)){
			flag_process_security = FALSE;
			factory_reset();
			start_reboot();
		}
	}
}

int RD_Messenger_Security(u8 *par, int par_len, mesh_cb_fun_par_t *cb_par) {
	int result = crypt(par);
	flag_check_mess = TRUE;

	if(result == unicast_id){
		flag_unicast_id = TRUE;
		flag_process_security = FALSE;
		par[0] = 0x01;
		mesh_tx_cmd2normal_primary(0xE1, par, 1, cb_par ->adr_src , 2);
	}
	else{
		flag_unicast_id = FALSE;
		par[0] = 0x00;
		mesh_tx_cmd2normal_primary(0xE1, par, 1, cb_par ->adr_src , 2);

		vrs_time_error_unicast = clock_time_s();
	}
	RD_Flash_SaveSecurity(flag_unicast_id, flag_process_security, flag_check_mess);
	return 0;
}

unsigned char modulo_calculate(unsigned short par1,unsigned short par2,unsigned short *out){
	if(par1 > par2){
		*out = par1 % par2;
		return 1;
	}
	else if(par1<par2){
		*out = par2 % par1;
		return 1;
	}
	else return 0;
}

int crypt(unsigned char *data){
	unsigned short Param[4];
	unsigned short Modulo;
	Param[0] = (data[0] << 8 | data[1]);
	Param[1] = (data[2] << 8 | data[3]);
	Param[2] = (data[4] << 8 | data[5]);
	Param[3] = (data[6] << 8 | data[7]);
	if(modulo_calculate(Param[0],Param[1],&Modulo)){
		if(	modulo_calculate(Modulo,Param[2],&Modulo)){
			if(modulo_calculate(Modulo,Param[3],&Modulo)){
				return Modulo;
			}
			else return 0;
		}
		else return 0;
	}
	else return 0;
}

void Tranining_2(void){
    if(flag_training_test2 == 1){
		Process_Test2();
	 }
}

void KickoutALL(void){
    if(flag_kickout == 1){
    	Time_kickout();
    }
}
