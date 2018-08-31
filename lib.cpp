//
// Created by root on 18-8-29.
//

#include "type.h"
#include "lib.h"


#define add_PARAMETER(arg, len) {int k = 0;\
                                args[i].parameter_length = sizeof(arg);\
                                args[i].parametar_value = datap;\
                                for(k = len - 1;k >= 0; k--)\
                                {args[i].parametar_value[k] = ((uint8_t*)&arg)[k];}\
                                datap += args[i].parameter_length;\
                                i++;}


uint8_t PWM_setting(uint8_t power)
{
	PARAMETER *args;
	uint8_t *data = nullptr;
	uint8_t ret = 0;
	uint8_t *datap = nullptr;
	int i = 0;

	args = (PARAMETER *) malloc(sizeof(PARAMETER) * 1);
	data = (uint8_t *) (malloc(1));

	datap = data;

	add_PARAMETER(power, 1);

	send_commend_with_arg(PWM_MODULE, PWM_SETTING, 1, args, data);
	ret = (uint8_t) get_data(nullptr);
	return ret;
}

uint8_t SPI_setFast()
{
	uint8_t ret = 0;
	send_command(SPI_MODULE, SPI_SETFAST);
	ret = (uint8_t) get_data(nullptr);
	return ret;
}

uint16_t SPI_rw_1(uint16_t readBuf, uint16_t writeBuf)
{
	PARAMETER *args;
	uint8_t *data = nullptr;
	uint8_t *datap = nullptr;
	int i = 0;
	uint16_t ret = 0;

	args = (PARAMETER *) malloc(sizeof(PARAMETER) * 2);
	data = (uint8_t *) (malloc(2 + 2));

	datap = data;

	add_PARAMETER(readBuf, 2);
	add_PARAMETER(writeBuf, 2);

	send_commend_with_arg(SPI_MODULE, SPI_RW_1, 2, args, data);
	ret = (uint16_t) get_data(nullptr);
	return ret;

}

// STEPPER_MODULE

int8_t Stepper_Init(uint8_t ch)
{
	PARAMETER *args;
	uint8_t *data = nullptr;
	int8_t ret = 0;
	uint8_t *datap = nullptr;
	int i = 0;

	args = (PARAMETER *) malloc(sizeof(PARAMETER) * 1);
	data = (uint8_t *) (malloc(1));

	datap = data;

	add_PARAMETER(ch, 1);

	send_commend_with_arg(STEPPER_MODULE, STEPPER_INIT, 1, args, data);
	ret = (int8_t) get_data(nullptr);
	return ret;
}


int8_t Stepper_Set_Speed(uint8_t ch, uint32_t max_speed, uint32_t min_speed)
{
	PARAMETER *args;
	uint8_t *data = nullptr;
	uint8_t *datap = nullptr;
	int i = 0;
	uint8_t ret = 0;

	args = (PARAMETER *) malloc(sizeof(PARAMETER) * 3);
	data = (uint8_t *) (malloc(1 + 4 + 4));

	datap = data;

	add_PARAMETER(ch, 1);
	add_PARAMETER(max_speed, 4);
	add_PARAMETER(min_speed, 4);

	send_commend_with_arg(STEPPER_MODULE, STEPPER_SET_SPEED, 3, args, data);
	ret = (int8_t) get_data(nullptr);
	return ret;
}

int8_t Stepper_Move(uint8_t ch, uint8_t dir, uint32_t steps)
{
	PARAMETER *args;
	uint8_t *data = nullptr;
	uint8_t *datap = nullptr;
	int i = 0;
	uint8_t ret = 0;

	args = (PARAMETER *) malloc(sizeof(PARAMETER) * 3);
	data = (uint8_t *) (malloc(1 + 1 + 4));

	datap = data;

	add_PARAMETER(ch, 1);
	add_PARAMETER(dir, 1);
	add_PARAMETER(steps, 4);

	send_commend_with_arg(STEPPER_MODULE, STEPPER_MOVE, 3, args, data);
	ret = (int8_t) get_data(nullptr);
	return ret;
}


// MPU6500_MODULE
uint16_t MPU6500_RWReg(uint16_t Data, uint8_t addr, uint8_t writeLen)
{
	PARAMETER *args;
	uint8_t *data = nullptr;
	uint8_t *datap = nullptr;
	int i = 0;
	uint16_t ret = 0;

	args = (PARAMETER *) malloc(sizeof(PARAMETER) * 3);
	data = (uint8_t *) (malloc(2 + 1 + 1));

	datap = data;

	add_PARAMETER(Data, 2);
	add_PARAMETER(addr, 1);
	add_PARAMETER(writeLen, 1);

	send_commend_with_arg(MPU6500_MODULE, MPU6500_RWREG, 3, args, data);
	ret = (uint16_t) get_data(nullptr);
	return ret;
}

int8_t MPU6500_Check()
{
	uint8_t ret = 0;
	send_command(MPU6500_MODULE, MPU6500_CHECK);
	ret = (int8_t) get_data(nullptr);
	return ret;
}

void MPU6500_getData(int16_t *pIMU)
{
	send_command(MPU6500_MODULE, MPU6500_GETDATA);
	get_data((uint8_t *) pIMU);
}

int8_t MPU6500_Init(uint8_t *Configs, uint16_t len)
{
	PARAMETER *args;
	uint8_t *data = nullptr;
	uint8_t *datap = nullptr;
	int i = 0;
	uint8_t addr = 0;
	int8_t ret = 0;

	args = (PARAMETER *) malloc(sizeof(PARAMETER) * 2);
	data = (uint8_t *) (malloc(1 + 2));
	datap = data;


	if ( Configs == nullptr ) {
		addr = 0;
	} else {
		addr = PROTOCOL_DATA1;
		send_data(PROTOCOL_DATA1, Configs, static_cast<uint16_t>(len * 2));
		ret = (int8_t) get_data(nullptr);
		if ( ret != 0 ) {
			printf("[MPU6500_Init]send fail\n");
			return -1;
		}
	}

	add_PARAMETER(addr, 1);
	add_PARAMETER(len, 2);
	fflush(stdout);
	send_commend_with_arg(MPU6500_MODULE, MPU6500_INIT, 2, args, data);
	ret = (int8_t) get_data(nullptr);
	return ret;
}
