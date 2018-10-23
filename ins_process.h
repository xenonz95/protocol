//
// Created by root on 18-10-16.
//

#ifndef PROTOCOL_INS_PROCESS_H
#define PROTOCOL_INS_PROCESS_H

#include "protocol.h"

typedef struct
{
	int32_t PC;
	int32_t AX;
	int32_t BX;
	int32_t CX;
	int32_t DX;
	int32_t RET;
	int32_t ERR;
	int32_t LINE;
}VM_Register;

typedef enum
{
	NO_CODE,

}ERR_state;

void save_ins(PROTOCOL_INS ins);

int32_t process();


#endif //PROTOCOL_INS_PROCESS_H
