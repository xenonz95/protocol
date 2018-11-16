//
// Created by root on 18-10-8.
//

#include <cstdio>
#include <cstring>
#include "../lib/include/lib.h"
#include <ctime>
#include <iostream>

using namespace std;

int main()
{
	int ret = 0;
	clock_t t1 = clock();
	PWM_setting(16);
	cout << (clock()- t1)*1.0/CLOCKS_PER_SEC*1000 << endl;t1 = clock();
	Protocol_debug(10020,20100,3001000,40100);
	cout << (clock()- t1)*1.0/CLOCKS_PER_SEC*1000 << endl;t1 = clock();
	Protocol_debug(40020,30100,2001000,10100);
	cout << (clock()- t1)*1.0/CLOCKS_PER_SEC*1000 << endl;t1 = clock();
	ret = Stepper_Init(2);
	cout << (clock()- t1)*1.0/CLOCKS_PER_SEC*1000 << endl;t1 = clock();
	printf("ret11 = %d\n",ret);
	//ret = Stepper_Init(3);
	cout << (clock()- t1)*1.0/CLOCKS_PER_SEC*1000 << endl;t1 = clock();
	printf("ret21 = %d\n",ret);
	ret = Stepper_Set_Speed(2,500,100);
	cout << (clock()- t1)*1.0/CLOCKS_PER_SEC*1000 << endl;t1 = clock();
	printf("ret12 = %d\n",ret);
	//ret = Stepper_Set_Speed(3,150,150);
	cout << (clock()- t1)*1.0/CLOCKS_PER_SEC*1000 << endl;t1 = clock();
	printf("ret22 = %d\n",ret);
	ret = Stepper_Move(2,0,500);
	cout << (clock()- t1)*1.0/CLOCKS_PER_SEC*1000 << endl;t1 = clock();
	printf("ret13 = %d\n",ret);
	//ret = Stepper_Move(3,0,100);
	cout << (clock()- t1)*1.0/CLOCKS_PER_SEC*1000 << endl;t1 = clock();
	printf("ret23 = %d\n",ret);
	
	return 0;
}


