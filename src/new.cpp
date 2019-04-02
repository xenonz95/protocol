//
// Created by root on 18-10-15.
//

#include "lib.h"
#include "vm.h"


#include <iostream>

#include <cstring>
#include <ctime>

using namespace std;

struct  timeval  tv1;
void print_time()
{


}


int main()
{
	clock_t t1 = clock();
/*
//	uint8_t ret = PWM_setting(21);
//	printf("ret = %d\n", ret);
//	//fflush(stdout);
//	//Protocol_debug(100000, 200000, 300000, 400000);
//	//Protocol_debug(120, 2020, 30200, 40200);
//

//	PWM_setting(16);
//	cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
//	t1 = clock();
//	Protocol_debug(10020, 20100, 3001000, 40100);
//	cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
//	t1 = clock();
//	PWM_setting(16);
//	cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
//	t1 = clock();
//	Protocol_debug(10020, 20100, 3001000, 40100);
//	cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
//	t1 = clock();

	char *str = const_cast<char *>("test string qwertyuioplkjhgfd");
	cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
	t1 = clock();

	Data_data_n(LIB_DATA1, (uint8_t *) str, (int) strlen((str)));
	Protocol_debug(100000, 200000, 300000, 4000);
	cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
	t1 = clock();
	char buf[100] = {0,};
	Data_back(LIB_DATA1, (uint8_t *) str, (uint8_t *) buf, (int) strlen((str)));
	printf("[back] %s\n", buf);
	cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
	t1 = clock();
*/


	PROTOCOL_INS inss[] = {
			//pack_function(VM_MODULE,VM_DEBUG,0,0,0,0),
			//pack_function(VM_MODULE,VM_DEBUG,0,0,0,0),
			pack_vm(VM_CACULATE_I, ADD, ZERO, 56, AX, 0),
			//pack_function(VM_MODULE,VM_DEBUG,0,0,0,0),
			pack_vm(VM_CACULATE_I, ADD, ZERO, 28, BX, 0),
			//pack_function(VM_MODULE,VM_DEBUG,0,0,0,0),
			pack_vm(VM_CACULATE_R, ADD, AX, BX, CX, 0),
			pack_function(VM_MODULE, VM_DEBUG, 0, 0, 0, 0),
			pack_vm(VM_CACULATE_I, ADD, ZERO, 0, AX, 0),
			pack_vm(VM_CACULATE_I, ADD, ZERO, 0, BX, 0),
			pack_vm(VM_CACULATE_I, ADD, ZERO, 0, CX, 0),
	};

	PROTOCOL_INS jump_inss[] = {
			pack_vm(JUMP_IF, 0, ZERO, ZERO, 1, 0),
			pack_function(VM_MODULE, VM_DEBUG, 0, 0, 0, 0),
			pack_function(VM_MODULE, VM_DEBUG, 0, 0, 0, 0),
			pack_vm(JUMP_IF, 0, ZERO, ZERO, 1, 0),
			pack_function(VM_MODULE, VM_DEBUG, 0, 0, 0, 0),
			pack_function(VM_MODULE, VM_DEBUG, 0, 0, 0, 0),
			pack_function(VM_MODULE, VM_DEBUG, 0, 0, 0, 0),
			pack_function(VM_MODULE, VM_DEBUG, 0, 0, 0, 0),
	};

	PROTOCOL_INS loop_inss[] = {
			pack_vm(VM_CACULATE_I, ADD, ZERO, 0, AX, 0),
			pack_vm(VM_CACULATE_I, ADD, ZERO, 3, BX, 0),
			pack_function(VM_MODULE, VM_DEBUG, 0, 0, 0, 0),
			pack_vm(VM_CACULATE_I, ADD, AX, 1, AX, 0),
			pack_function(VM_MODULE, VM_DEBUG, 0, 0, 0, 0),
			pack_vm(JUMP_IF, 0, AX, BX, 1, 0),
			pack_vm(JUMP_IF, 0, ZERO, ZERO, -4, 0),
			pack_function(VM_MODULE, VM_DEBUG, 0, 0, 0, 0),
	};

	PROTOCOL_INS use_reg[] = {
			pack_function(PROTOCOL_MODULE, PROTOCOL_DEBUG, 312, 123, 543, 654),
			pack_function(VM_MODULE, VM_USE_REG, 0, 0, 0, 0),
			pack_function(PROTOCOL_MODULE, PROTOCOL_DEBUG, 312, 123, 543, 654),
			pack_function(VM_MODULE, VM_NOTUSE_REG, 0, 0, 0, 0),
	};

	PROTOCOL_INS fun_loop[] = {

			pack_vm(VM_CACULATE_I, ADD, ZERO, 0, AX, 0),
			pack_vm(VM_CACULATE_I, ADD, ZERO, 256, BX, 0),

			//pack_function(VM_MODULE, VM_DEBUG, 0, 0, 0, 0),

			pack_vm(VM_CACULATE_I, ADD, AX, 0, P1, 0),

			pack_function(VM_MODULE, VM_USE_REG, 0, 0, 0, 0),
			pack_function(PWM_MODULE, PWM_SETTING, 0, 0, 0, 0),
			pack_function(VM_MODULE, VM_NOTUSE_REG, 0, 0, 0, 0),

			pack_vm(VM_CACULATE_I, ADD, AX, 1, AX, 0),

			pack_vm(JUMP_IF, 0, AX, BX, 1, 0),
			pack_vm(JUMP_IF, 0, ZERO, ZERO, -7, 0),


	};
	PROTOCOL_INS fun_no_work_loop[] = {

			pack_vm(VM_CACULATE_I, ADD, ZERO, 0, AX, 0),
			pack_vm(VM_CACULATE_I, ADD, ZERO, 1024, BX, 0),

			//pack_function(VM_MODULE, VM_DEBUG, 0, 0, 0, 0),

			pack_vm(VM_CACULATE_I, ADD, AX, 0, P1, 0),

			pack_function(VM_MODULE, VM_USE_REG, 0, 0, 0, 0),
			pack_function(PWM_MODULE, PWM_SETTING, 0, 0, 0, 0),
			pack_function(VM_MODULE, VM_NOTUSE_REG, 0, 0, 0, 0),

			pack_vm(VM_CACULATE_I, ADD, AX, 1, AX, 0),

			pack_vm(JUMP_IF, 0, AX, BX, 1, 0),
			pack_vm(JUMP_IF, 0, ZERO, ZERO, -6, 0),

	};

	PROTOCOL_INS test[] = {
			pack_function(PROTOCOL_MODULE, PROTOCOL_TEST, 12, 0, 0, 0),

	};



#define SEND_INS(ins) sizeof(ins)/sizeof(ins[0]),ins
	printf("=================\n");
	PROTOCOL_send(SEND_INS(test));
	PROTOCOL_decode();
	cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
//	t1 = clock();
//	PROTOCOL_send(SEND_INS(fun_loop));
//	PROTOCOL_decode();
//	cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
//	t1 = clock();
//for(int i = 1; i< 256 ; i++)
//{
//	PWM_setting((uint8_t)i);
//	usleep(10000);
//
//}
//	cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
//	t1 = clock();

	return 0;

}
