#include <cstdio>
#include <cstring>
#include "lib.h"
#include <ctime>
#include <iostream>

#include "rawData.h"

using namespace std;

#define SEND_INS(ins) sizeof(ins)/sizeof(ins[0]),ins


#define MPU6500_InitRegNum 11

int main()
{
	clock_t t1 = clock();
	int i = 1;
	while (i --> 0) {
		int32_t ret;
		PROTOCOL_INS setting[] = {
				pack_function(GPIO_MODULE, GPIO_GET, 1, 11, 1, 0),
				pack_function(GPIO_MODULE, GPIO_GET, 1, 11, 1, 0),
				pack_function(GPIO_MODULE, GPIO_GET, 1, 11, 1, 0),
				pack_function(GPIO_MODULE, GPIO_GET, 1, 11, 1, 0),
				pack_function(GPIO_MODULE, GPIO_GET, 1, 11, 1, 0),


		};
		PROTOCOL_send(SEND_INS(setting));
		ret = PROTOCOL_decode();
		cout << "ret = " << ret << " "<< (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
		t1 = clock();

	}

	return 0;
}