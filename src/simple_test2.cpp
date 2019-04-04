#include <cstdio>
#include <cstring>
#include "lib.h"
#include <ctime>
#include <iostream>

#include "rawData.h"
#include "vm.h"

using namespace std;

#define SEND_INS(ins) sizeof(ins)/sizeof(ins[0]),ins


#define MPU6500_InitRegNum 11
int32_t ret;

int main()
{


	clock_t t1 = clock();
	int i = 1;
	change_endpoint(1, "ttyACM1");


	PROTOCOL_INS setting1[] = {
			pack_function(GPIO_MODULE, GPIO_SET, 2, 13, 0, 0),
			pack_function(PROTOCOL_MODULE, PROTOCOL_TEST_TEST, 1, 10, 1, 11),
	};
	PROTOCOL_send(SEND_INS(setting1));
	ret = PROTOCOL_decode();
	cout << "ret = " << ret << " " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
	t1 = clock();

	PROTOCOL_INS setting2[] = {
			pack_function(GPIO_MODULE, GPIO_SET, 1, 11, 0, 0),
	};
	PROTOCOL_send(SEND_INS(setting2));
	ret = PROTOCOL_decode();
	cout << "ret = " << ret << " " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
	t1 = clock();

	return 0;
}