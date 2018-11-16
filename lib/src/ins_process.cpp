//
// Created by root on 18-10-16.
//

#include <cstring>
#include "../include/ins_process.h"
#include "../include/lib.h"
#include "../include/vm.h"

PROTOCOL_INS inss[100] = {0,};
VM_Register Reg = {0,};

void save_ins(PROTOCOL_INS ins)
{
	inss[Reg.LINE] = ins;
	Reg.LINE++;
}

int32_t process()
{
	PROTOCOL_INS ins;
	if ( Reg.LINE == 0 ) {
		Reg.ERR = NO_CODE;
		return 0;
	}
	Reg.PC = 0;
	bool is_first_c = true;
	DATA_counter = 0;
	for (Reg.PC = 0; Reg.PC < Reg.LINE; Reg.PC++) {
		ins = inss[Reg.PC];
		if(ins.moudle == PROTOCOL_MODULE)
		{
			switch (ins.command)
			{
				case PROTOCOL_NORMAL:
					Reg.RET = ins.data.normal.p1;
					break;
				case PROTOCOL_PRINT:
					if(is_first_c)
					{
						printf("\t[core]\t");
					}
					is_first_c = false;
					printf("%s", ins.data.pure.data);
					if(ins.data.pure.data[15] == 0 || ins.data.pure.data[15] == '\n')
					{
						is_first_c = true;
					}
					break;
				case PROTOCOL_PURE_DATA:
					memcpy(data_holder1+DATA_counter, ins.data.pure.data, 16);
					DATA_counter += 16;
					Reg.RET = 0;
					break;
					;
				default:
					break;
			}
		}
	}
	Reg.LINE = 0;
	return Reg.RET;
}
