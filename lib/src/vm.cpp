//
// Created by root on 18-10-26.
//

#include "vm.h"

PROTOCOL_DATA
pack_vm_ins(uint8_t opcode, uint8_t funt, uint8_t rs1, int32_t ris2, int8_t rt, uint8_t sw)
{
	PROTOCOL_DATA ins = {0,};
	ins.ins.opcode = opcode;
	ins.ins.funt = funt;
	ins.ins.rs1 = rs1;
	ins.ins.ris2 = ris2;
	ins.ins.rt = rt;
	ins.ins.sw = sw;
	return ins;
}


