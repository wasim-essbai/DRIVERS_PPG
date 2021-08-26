/*
 * FSM.c
 *
 *  Created on: Aug 26, 2021
 *      Author: Matteo Verzeroli
 */
#include "FSM.h"

void setSystemState(DISCOVERY_FSM* discovery, SystemState state){
	if(discovery->state != state){
		switch(state){
		case SYS_ERROR:
			break;
		case SYS_IDLE:
			break;
		case SYS_START_UP:
			break;
		case SYS_STOP:
			break;
		case SYS_STREAM:
			break;
		default:
			break;
		}
		discovery->state = state;
	}
}

