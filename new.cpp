//
// Created by root on 18-10-15.
//

#include "ins_process.h"
#include "lib.h"
#include "protocol.h"
#include "rawData.h"

#include <iostream>

#include <cstring>
#include <ctime>

using namespace std;

int main()
{
//	uint8_t ret = PWM_setting(21);
//	printf("ret = %d\n", ret);
//	//fflush(stdout);
//	//Protocol_debug(100000, 200000, 300000, 400000);
//	//Protocol_debug(120, 2020, 30200, 40200);
//
	clock_t t1 = clock();
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

	char* str = const_cast<char *>("test string qwertyuioplkjhgfd");
	cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;t1 = clock();

	Data_data_n(LIB_DATA1,(uint8_t*)str,(int)strlen((str)));
	Protocol_debug(100000, 200000, 300000, 4000);
	cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;t1 = clock();
	char buf[100] = {0,};
	Data_back(LIB_DATA1,(uint8_t*)str,(uint8_t*)buf, (int)strlen((str)));
	printf("[back] %s\n",buf);
	cout << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;t1 = clock();

	return 0;

}
