//
// Created by root on 18-8-9.
//

#ifndef PROTOCOL_PROTOCOL_H
#define PROTOCOL_PROTOCOL_H

/*
    Procotol: COMMAND_HEADER + PARAMETER_1 + PARAMETER_2 + ... + PARAMETER_N
    N >= 0
*/

#define PROTOCOL_MAGIC  0xAA55

#include <fcntl.h>
#include <termio.h>
#include <termios.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstdint>


extern uint8_t command_flag;

typedef struct {
	int32_t p1; //four parameter
	int32_t p2;
	int32_t p3;
	int32_t p4;
} PROTOCOL_DATA_normal;

typedef struct {
	uint8_t data[16]; //pure data
} PROTOCOL_DATA_pure;

typedef struct
{
	uint8_t opcode;
	uint8_t funt;
	uint8_t rs1;
	int32_t ris2;
	int8_t rt;
	uint8_t sw;
	uint8_t null[7];
}VM_INS;

typedef union
{
	PROTOCOL_DATA_normal normal;
	PROTOCOL_DATA_pure pure;
	VM_INS ins;
} PROTOCOL_DATA;


typedef struct {
	uint16_t moudle;
	uint16_t command;
	PROTOCOL_DATA data;
} PROTOCOL_INS;

typedef struct {
	uint16_t magic; //PROTOCOL_MAGIC
	uint16_t length; //maximum 64K bytes
} PROTOCOL_HEAD;


extern uint8_t command_flag;
extern "C" {
void PROTOCOL_send(uint16_t length, PROTOCOL_INS *ins);
int32_t PROTOCOL_decode();
}


#endif //PROTOCOL_PROTOCOL_H
