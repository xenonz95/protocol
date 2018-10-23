//
// Created by root on 18-10-16.
//

#include <termios.h>
#include <fcntl.h>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include "rawData.h"

bool init_is_ok = 0;
int file_d = 0;

int8_t data_init()
{
	if ( init_is_ok != 0 ) {
		return 0;
	}
	termios oldtio;
	uint8_t trash;
	file_d = open("/dev/ttyACM0", O_RDWR | O_NDELAY | O_NOCTTY);
	if ( file_d <= 0 ) {
		perror("[open tty fail]");
		return -1;
	}
	if ( tcflush(file_d, TCIFLUSH) < 0 ) {
		perror("[flush tty fail]");
	}
	if ( tcgetattr(file_d, &oldtio) != 0 ) {
		perror("[SetupSerial]");
		return -1;
	}

	oldtio.c_cflag |= (CLOCAL | CREAD);

	oldtio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // 禁用各种控制字符生效

	oldtio.c_oflag &= ~OPOST;
	oldtio.c_oflag &= ~(ONLCR | OCRNL); //禁用转换回车与换行

	oldtio.c_iflag &= ~(ICRNL | INLCR);
	oldtio.c_iflag &= ~(IXON | IXOFF | IXANY);

	oldtio.c_cflag &= ~CRTSCTS; //no flow control

	tcflush(file_d, TCIOFLUSH);

	oldtio.c_cc[VTIME] = 0;
	oldtio.c_cc[VMIN] = 0;

	tcsetattr(file_d, TCIOFLUSH, &oldtio);
	init_is_ok = 1;
	return 0;
}

void data_deinit()
{
	close(file_d);
}

void getData(int num, uint8_t *data_holder)
{
	int loop_i = 0;
	data_init();
	ssize_t ret = 0;
	char *debug = (char *) data_holder;
	for (int i = 0; i < num; i++) {
		ret = read(file_d, data_holder + i, 1);
		if ( ret <= 0 ) {
			i--;
		} else {
			//putchar(data_holder[i]);
			//fflush(stdout);
		}
		loop_i++;
		if ( loop_i > 1000000 ) {
			printf("[rawData get] infinity loop\n");
			fflush(stdout);
			exit(-1);
		}
	}
}

void sendData(uint8_t *data, int num)
{
	int loop_i = 0;
	ssize_t ret = 0;
	size_t sended = 0;
	data_init();
	for (int i = 0; i < num; i++) {
		//printf("[%x %c]",data[i],data[i]);
	}
	while (num > sended) {
		ret = write(file_d, data + sended, num - sended);
		//printf("sended %d\n", ret);
		if ( ret < 0 ) {
			ret = 0;
		}
		sended += ret;
		loop_i++;
		if ( loop_i > 1000000 ) {
			printf("[rawData send] infinity loop\n");
			fflush(stdout);
			exit(-1);
		}
	}
}
