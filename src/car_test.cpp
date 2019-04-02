//
// Created by root on 18-12-18.
//

#include "lib.h"
#include "vm.h"


#include <iostream>
#include <termio.h>
#include <linux/input.h>
#include <cstring>
#include <ctime>

using namespace std;

clock_t t1 = clock();



#define SEND_INS(ins) sizeof(ins)/sizeof(ins[0]),ins

void run(int dir)
{
	int l = 0;
	int r = 0;
	switch (dir) {
		case 1:
			l = 0;
			r = -1;
			break;
		case 2:
			l = -1;
			r = -1;
			break;
		case 3:
			l = -1;
			r = 0;
			break;
		case 4:
			l = -1;
			r = 1;
			break;
		case 5:
			l = 0;
			r = 0;
			break;
		case 6:
			l = 1;
			r = -1;
			break;
		case 7:
			l = 0;
			r = 1;
			break;
		case 8:
			l = 1;
			r = 1;
			break;
		case 9:
			l = 1;
			r = 0;
			break;
		default:break;
	}

	r *= -1;

	{
		// the cable have a mistake
		//l *= -1;
		//r *= -1;

	}
	cout << (clock()- t1)*1.0/CLOCKS_PER_SEC*1000 << endl;t1 = clock();
	if ( l != 0 ) {
		PROTOCOL_INS run[] = {
				pack_function(STEPPER_MODULE, STEPPER_RUN, 2, l, 0, 0),
		};
		PROTOCOL_send(SEND_INS(run));

	} else {
		PROTOCOL_INS run[] = {
				pack_function(STEPPER_MODULE, STEPPER_STOP, 2, 0, 0, 0),
		};
		PROTOCOL_send(SEND_INS(run));
	}


	if ( r != 0 ) {
		PROTOCOL_INS run[] = {
				pack_function(STEPPER_MODULE, STEPPER_RUN, 3, r, 0, 0),
		};
		PROTOCOL_send(SEND_INS(run));
	} else {
		PROTOCOL_INS run[] = {
				pack_function(STEPPER_MODULE, STEPPER_STOP, 3, 0, 0, 0),
		};
		PROTOCOL_send(SEND_INS(run));
	}

	PROTOCOL_decode();
	PROTOCOL_decode();
	cout << (clock()- t1)*1.0/CLOCKS_PER_SEC*1000 << endl;t1 = clock();

}


int main()
{
	int32_t ret;
	PROTOCOL_INS setting[] = {
			pack_function(STEPPER_MODULE, STEPPER_INIT, 2, 0, 0, 0),
			pack_function(STEPPER_MODULE, STEPPER_INIT, 3, 0, 0, 0),
			pack_function(STEPPER_MODULE, STEPPER_SET_SPEED, 2, 3000, 500, 0),
			pack_function(STEPPER_MODULE, STEPPER_SET_SPEED, 3, 3000, 500, 0),
			pack_function(STEPPER_MODULE, STEPPER_RUN, 2, 1, 0, 0),
			pack_function(STEPPER_MODULE, STEPPER_RUN, 3, -1, 0, 0),
//			pack_function(STEPPER_MODULE, STEPPER_MOVE, 2, 1, 1000, 0),
//			pack_function(STEPPER_MODULE, STEPPER_MOVE, 3, 1, 1000, 0),

	};
	PROTOCOL_send(SEND_INS(setting));
	ret = PROTOCOL_decode();


	termios nts{}, ots{};


	int key = 8;

	while(key != 'q')
	{
		if(tcgetattr(0, &ots) < 0)
		{
			return EOF;
		}

		nts = ots;
		cfmakeraw(&nts);

		if(tcsetattr(0,TCSANOW ,&nts) < 0)
		{
			return EOF;
		}
		key = getchar();
		if(tcsetattr(0,TCSANOW ,&ots) < 0)
		{
			return EOF;
		}
		run(key - '0');

		//printf("%d | %d \n",key, key-'0');
	}


	printf("exit\n");

}