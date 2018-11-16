//
// Created by root on 18-8-29.
//

#include <cstring>
#include "../include/lib.h"
#include "../include/protocol.h"
#include "../include/vm.h"

uint8_t data_holder1[1024];
uint8_t DATA_counter = 0;


PROTOCOL_INS pack_vm(uint8_t opcode, uint8_t funt, uint8_t rs1, int32_t ris2, int8_t rt, uint8_t sw)
{
	return pack_data_i(VM_MODULE,VM_COMMAND,pack_vm_ins(opcode, funt, rs1, ris2, rt, sw));
}

PROTOCOL_INS pack_data_i(uint16_t module,
                       uint16_t command,
                       PROTOCOL_DATA data)
{
	PROTOCOL_INS temp_ins;
	temp_ins.moudle = module;
	temp_ins.command = command;
	memcpy(temp_ins.data.pure.data, &data, 16);
	return temp_ins;
}

PROTOCOL_INS pack_data(uint16_t module,
                                     uint16_t command,
                                     uint8_t data[16])
{
	PROTOCOL_INS temp_ins;
	temp_ins.moudle = module;
	temp_ins.command = command;
	memcpy(temp_ins.data.pure.data, data, 16);
	return temp_ins;
}

PROTOCOL_INS pack_function(uint16_t module,
                                         uint16_t command,
                                         int32_t p1,
                                         int32_t p2,
                                         int32_t p3,
                                         int32_t p4)
{
	PROTOCOL_INS temp_ins;
	temp_ins.moudle = module;
	temp_ins.command = command;
	temp_ins.data.normal.p1 = p1;
	temp_ins.data.normal.p2 = p2;
	temp_ins.data.normal.p3 = p3;
	temp_ins.data.normal.p4 = p4;
	return temp_ins;
}
