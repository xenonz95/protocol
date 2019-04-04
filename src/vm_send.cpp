#include <cstdio>
#include <cstring>
#include "lib.h"
#include <ctime>
#include <iostream>

#include "rawData.h"
#include "vm.h"

using namespace std;

#define SEND_INS(ins) sizeof(ins)/sizeof(ins[0]),ins


int32_t ret;

int main()
{

	clock_t t1 = clock();
	int i = 1;
	PROTOCOL_INS setting1[] = {
			pack_vm(VM_CACULATE_I, ADD, ZERO, 8, AX, 0),
			pack_vm(VM_CACULATE_I, ADD, ZERO, 0, BX, 0),

			pack_vm(VM_CACULATE_I, ADD, ZERO, 1, DX, 0),

			pack_function(GPIO_MODULE, GPIO_GET, 1, 10, 0, 0),

			pack_vm(JUMP_IF, 0, RET, DX, 2, 0),

			pack_function(GPIO_MODULE, GPIO_SET, 1, 11, 0, 0),

			pack_vm(JUMP_IF, 0, ZERO, ZERO, 1, 0),
			pack_function(GPIO_MODULE, GPIO_SET, 1, 11, 1, 0),

			pack_vm(JUMP_IF, 0, AX, BX, 1, 0),

			pack_vm(JUMP_IF, 0, ZERO, ZERO, -7, 0),
	};
	PROTOCOL_send(SEND_INS(setting1));
	ret = PROTOCOL_decode();
	cout << "ret = " << ret << " " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
	t1 = clock();
	//continue;
	//usleep(100000);

	getchar();

	PROTOCOL_INS setting2[] = {
			pack_vm(VM_CACULATE_I, ADD, ZERO, 8, BX, 0),
	};
	PROTOCOL_send(SEND_INS(setting2));
	ret = PROTOCOL_decode();
	cout << "ret = " << ret << " " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
	t1 = clock();

	return 0;
}