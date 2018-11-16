//
// Created by root on 18-10-26.
//

#ifndef PROTOCOL_VM_H
#define PROTOCOL_VM_H

#include <cstdint>
#include "../include/lib.h"
#include "../include/protocol.h"

typedef union
{
	int32_t reg[14];
	struct
	{
		int32_t PC;
		int32_t AX;
		int32_t BX;
		int32_t CX;
		int32_t DX;
		int32_t RET;
		int32_t ERR;
		int32_t LINE;
		int32_t P0;
		int32_t P1;
		int32_t P2;
		int32_t P3;
		int32_t P4;
		int32_t ZERO;
	};
}VM_Register;

enum
{
	PC,
	AX,
	BX,
	CX,
	DX,
	RET,
	ERR,
	LINE,
	P0,
	P1,
	P2,
	P3,
	P4,
	ZERO,
};

//here need a typedef, but will cause recursive include
//the define of VM_INS at protocol.h

enum
{
	VM_CACULATE_R,
	VM_CACULATE_I,
	JUMP_IF,
};

enum
{
	ADD,
	SUB,
	MUT,
	DVI,
	BIGER,
	LESS,
	AND,
	OR,
	NOT,
	XOR,
	LEFET,
	RIGHT,
	EQUAL,
};

typedef enum
{
	NORMAL,
	NO_CODE = 2,

}ERR_state;


PROTOCOL_DATA
pack_vm_ins(uint8_t opcode, uint8_t funt, uint8_t rs1, int32_t ris2, int8_t rt, uint8_t sw);



#endif //PROTOCOL_VM_H
