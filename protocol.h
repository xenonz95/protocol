//
// Created by root on 18-8-9.
//

#ifndef PROTOCOL_PROTOCOL_H
#define PROTOCOL_PROTOCOL_H

/*
    Procotol: COMMAND_HEADER + PARAMETER_1 + PARAMETER_2 + ... + PARAMETER_N
    N >= 0
*/

#define PROTOCOL_MAGIC  0xAA55

#include <fcntl.h>
#include <termio.h>
#include <termios.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "type.h"


extern uint8_t command_flag ;

enum{
	PROTOCOL_MODULE = 0,
	SPI_MODULE = 1,
	PWM_MODULE,
	MPU6500_MODULE,
	GPIO_MODULE,
	STEPPER_MODULE,
};

enum{
	PROTOCOL_FAIL = 0,
	PROTOCOL_DATA1 = 1,
	PROTOCOL_DATA2,
	PROTOCOL_PURE_DATA,

};

enum{
	SPI_SETSPEED = 1,
	SPI_RW_1, // u16 u16
};

enum{
	PWM_SETTING = 1, // u8
};

enum{
	MPU6500_RWREG = 1,
	MPU6500_INIT,
	MPU6500_CHECK,
	MPU6500_GETDATA,
	MPU6500_GETRAWDATA,
};

// TODO: need separate GPIO module from SPI

enum{
	STEPPER_INIT = 1,
	STEPPER_ENABLE,
	STEPPER_SET_SPEED,
	STEPPER_SET_HOME,       //TODO
	STEPPER_GET_POSITION,   //TODO
	STEPPER_MOVE,
	STEPPER_RUN,            //TODO
	STEPPER_STOP,           //TODO
	STEPPER_HARD_STOP,      //TODO
	STEPPER_IS_BUSY,        //TODO

};

typedef struct
{
	uint16_t magic; //PROTOCOL_MAGIC
	uint16_t command_length; //maximum 64K bytes

	uint16_t module_code;
	uint16_t command_code;
	uint16_t end_magic;
} COMMAND_HEADER;

typedef struct
{
	uint16_t parameter_length; //bytes of current parameter
	uint8_t* parametar_value;
} PARAMETER;

typedef struct
{
	uint16_t return_length; //bytes of current parameter
	uint8_t return_value[];
} RETURN;

enum{
	COMMAND_STATE_IDLE,
	COMMAND_STATE_DECODING,
};
extern "C" {
int8_t protocol_init();
void protocol_deinit();

uint32_t get_data(uint8_t *data_holder);
ssize_t send_data(uint8_t data_holder, uint8_t *data_from_sender, uint16_t len);

ssize_t send_commend_with_arg(uint16_t module_code, uint16_t command_code, int num, PARAMETER *
args, uint8_t *data_from_sender);
ssize_t send_command(uint16_t module_code, uint16_t command_code);
}



#endif //PROTOCOL_PROTOCOL_H
