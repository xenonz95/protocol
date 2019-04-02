//
// Created by root on 18-8-9.
//

#include <cstring>
#include "protocol.h"
#include "rawData.h"
#include "ins_process.h"

uint8_t *command_temp;


void PROTOCOL_send(uint16_t length, PROTOCOL_INS *ins)
{
	PROTOCOL_HEAD temp_head;
	uint16_t i = 0;
	temp_head.magic = PROTOCOL_MAGIC;
	temp_head.length = length;

	size_t full_length = 0;
	full_length = sizeof(temp_head) + length * sizeof(PROTOCOL_INS);
	uint8_t *data = (uint8_t *) malloc(full_length);
	memcpy(data, &temp_head, sizeof(temp_head));
	for (i = 0; i < length; i++) {
		memcpy(data + sizeof(temp_head) + sizeof(PROTOCOL_INS) * i, (uint8_t *) (ins + i), sizeof
				(PROTOCOL_INS));
	}
	sendData(data, (int) full_length);
	free(data);
}

int32_t PROTOCOL_decode()
{
	uint16_t length = 0;
	uint16_t i = 0;
	uint8_t tempc;
	uint16_t endless_loop = 0;

	while (i < 2) {
		endless_loop++;
		if ( endless_loop > 10000 ) {
			printf("[protocol] endless loop");
			exit(-1);
		}
		getData(1, &tempc);
		if ( tempc == (PROTOCOL_MAGIC & 0xFF)) {
			i++;
		} else {
			//putchar(tempc);
			continue;
		}
		getData(1, &tempc);
		if ( tempc == (PROTOCOL_MAGIC >> 8 & 0xFF)) {
			i++;
		} else {
			i = 0;
			continue;
		}
	}
	getData(2, (uint8_t *) &length);
	//printf("[protocol] length = %d\n",length);
	PROTOCOL_INS temp_ins;
	for (i = 0; i < length; i++) {
		getData(sizeof(temp_ins), (uint8_t *) &temp_ins);
//		for(int j = 0; j < sizeof(temp_ins); j++)
//		{
//			printf("%x ", ((char*)&temp_ins)[j]);
//		}putchar('\n');
		//fflush(stdout);
		save_ins(temp_ins);
	}
	return process();
}
