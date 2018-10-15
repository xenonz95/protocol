//
// Created by root on 18-8-9.
//

#include <cstring>
#include "type.h"
#include "protocol.h"

uint8_t *command_temp;


int file_d = 0;

int8_t protocol_init()
{
	struct termios oldtio;
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
	return 0;
}

void protocol_deinit()
{
	close(file_d);
}

ssize_t send_commend_with_arg(uint16_t module_code, uint16_t command_code, int num, PARAMETER *
args, uint8_t *data_from_sender)
{
	COMMAND_HEADER head;
	head.magic = PROTOCOL_MAGIC;
	head.command_code = command_code;
	head.module_code = module_code;
	head.command_length = 10;

	head.end_magic = PROTOCOL_MAGIC;

	size_t len = 0;
	int i = 0, j = 0;
	char *data = NULL;
	char *datap = NULL;
	uint8_t *sdatap = data_from_sender;
	ssize_t ret = 0;


	for (i = 0; i < num; i++) {
		len += sizeof(args->parameter_length) + args[i].parameter_length;
	}

	data = (char *) malloc(len + sizeof(head));

	head.command_length = (uint16_t) (len + sizeof(head));
	*((COMMAND_HEADER *) data) = head;

	datap = data + sizeof(head);

	for (i = 0; i < num; i++) {
		*((uint16_t *) datap) = args[i].parameter_length;
		datap += 2;
		for (j = 0; j < args[i].parameter_length; j++, datap++) {
			*datap = sdatap[j];
			//printf("num=%d %d data=%d\n",num,j,sdatap[j]);
		}
		sdatap += args[i].parameter_length;
	}
	free(args);
	free(data_from_sender);
	ret = write(file_d, data, len + sizeof(head));
	if ( ret != len + sizeof(head)) {
		exit(-1);
	}
	//printf("[send_commend_with_arg]ret = %zi\n", ret);
	return ret;
}

ssize_t send_command(uint16_t module_code, uint16_t command_code)
{
	return send_commend_with_arg(module_code, command_code, 0, NULL, NULL);
}

char get_data_buf[1024] = {0,};

uint32_t get_data(uint8_t *data_holder)
{
	ssize_t ret;
	ssize_t ret_temp = 0;
	uint8_t data_buf[12] = {0};
	uint32_t return_buf = 0;
	uint16_t len = 0;
	uint8_t *datap = NULL;


	COMMAND_HEADER head;
	bool isData = 0;
	while (isData == 0) {
		//memset(data_buf, 0, 10);
		ret = 0;
		return_buf = 0;
		while (ret < 12) {
			ret_temp = read(file_d, data_buf + ret, 1);
			if ( ret_temp > 0 ) {
				//printf("[%d] %d %x %c\n", int(ret), data_buf[ret], data_buf[ret], \
        data_buf[ret]);
				//fflush((stdout));
				if ( data_buf[0] == 0x55 ) {
					ret += ret_temp;
				}
				else
				{
					putchar(data_buf[0]);
					putchar('\n');
				}
			}
		}
		head = *(COMMAND_HEADER *) data_buf;
		if ( head.magic != PROTOCOL_MAGIC || head.end_magic != PROTOCOL_MAGIC ) {
			printf("[ERROR] head wrong. got %x %x\n", head.magic, head.end_magic);
		}
		len = *(uint16_t *) (data_buf + 10);
		if ( head.command_code == PROTOCOL_PRINT && head.module_code == PROTOCOL_MODULE ) {
			datap = (uint8_t *) get_data_buf;
			memset(get_data_buf, 0, 1024);
		} else {
			datap = data_holder;
		}
		//printf("len is %d\n", len);
		//fflush(stdout);
		if ( len == 4 | datap == nullptr ) {
			for (int i = 0; i < 4; i++) {
				ret_temp = read(file_d, ((uint8_t *) &return_buf) + i, 1);
				if ( ret_temp < 0 ) {
					i--;
				}
			}
		} else {
			for (int i = 0; i < len; i++) {
				ret_temp = read(file_d, datap + i, 1);
				//printf("[%d] %d %x %c\n", i, datap[i], datap[i], datap[i]);
				//fflush((stdout));
				if ( ret_temp < 0 ) {
					i--;
				}
			}
		}
		//printf("code is %d", head.command_code);
		if ( head.command_code == PROTOCOL_PRINT && head.module_code == PROTOCOL_MODULE ) {
			printf("[core]%s", datap);
			fflush(stdout);
		} else {
			isData = 1;
		}
	}
	return return_buf;
}

ssize_t send_data(uint8_t data_holder, uint8_t *data_from_sender, uint16_t len)
{
	uint8_t *data = nullptr;
	COMMAND_HEADER head;
	ssize_t ret = 0;

	head.magic = PROTOCOL_MAGIC;
	head.end_magic = PROTOCOL_MAGIC;
	head.module_code = PROTOCOL_MODULE;
	head.command_code = data_holder;
	head.command_length = (uint16_t) 12 + len;
	data = (uint8_t *) malloc(head.command_length);

	*(COMMAND_HEADER *) data = head;
	*(uint16_t *) (data + 10) = len;
	for (int i = 0; i < len; i++) {
		(data + 12)[i] = data_from_sender[i];
	}

//	printf("send data ====================\n");
//	for(int i = 0; i<(12+len); i++)
//	{
//		printf("[%x] %d %c\n",data[i],data[i],data[i]);
//	}
//	printf("send end  ====================\n");
	ret = write(file_d, data, len + 12);
	return ret;
}







