//
// Created by root on 18-10-29.
//

#include "../include/function.h"
#include "../include/protocol.h"
#include "../include/lib.h"
#include <string.h>


uint8_t PWM_setting(uint8_t power)
{
	PROTOCOL_INS ins = pack_function(PWM_MODULE, PWM_SETTING, power, 0, 0, 0);
	PROTOCOL_send(1, &ins);
	return (uint8_t) PROTOCOL_decode();
}

uint8_t SPI_setSpeed(uint16_t prescaler)
{
	PROTOCOL_INS ins = pack_function(SPI_MODULE, SPI_SETSPEED, prescaler, 0, 0, 0);
	PROTOCOL_send(1, &ins);
	return (uint8_t) PROTOCOL_decode();
}

uint16_t SPI_rw_1(uint16_t readBuf, uint16_t writeBuf)
{
	PROTOCOL_INS ins = pack_function(SPI_MODULE, SPI_RW_1, readBuf, writeBuf, 0, 0);
	PROTOCOL_send(1, &ins);
	return (uint16_t) PROTOCOL_decode();
}

// STEPPER_MODULE

int8_t Stepper_Init(uint8_t ch)
{
	PROTOCOL_INS ins = pack_function(STEPPER_MODULE, STEPPER_INIT, ch, 0, 0, 0);
	PROTOCOL_send(1, &ins);
	return (int8_t) PROTOCOL_decode();
}


int8_t Stepper_Set_Speed(uint8_t ch, uint32_t max_speed, uint32_t min_speed)
{
	PROTOCOL_INS ins = pack_function(STEPPER_MODULE, STEPPER_SET_SPEED, ch, max_speed, min_speed,
	                                 0);
	PROTOCOL_send(1, &ins);
	return (int8_t) PROTOCOL_decode();
}

int8_t Stepper_Move(uint8_t ch, uint8_t dir, uint32_t steps)
{
	PROTOCOL_INS ins = pack_function(STEPPER_MODULE, STEPPER_MOVE, ch, dir, steps, 0);
	PROTOCOL_send(1, &ins);
	return (int8_t) PROTOCOL_decode();
}


// MPU6500_MODULE
uint16_t MPU6500_RWReg(uint16_t Data, uint8_t addr, uint8_t writeLen)
{
	PROTOCOL_INS ins = pack_function(MPU6500_MODULE, MPU6500_RWREG, Data, addr, writeLen, 0);
	PROTOCOL_send(1, &ins);
	return (uint16_t) PROTOCOL_decode();
}

int8_t MPU6500_Check()
{
	PROTOCOL_INS ins = pack_function(MPU6500_MODULE, MPU6500_CHECK, 0, 0, 0, 0);
	PROTOCOL_send(1, &ins);
	return (int8_t) PROTOCOL_decode();
}

void MPU6500_getData(int16_t *pIMU, uint32_t lag)
{
	PROTOCOL_INS ins = pack_function(MPU6500_MODULE, MPU6500_GETDATA, 0, lag, 0, 0);
	PROTOCOL_send(1, &ins);
	PROTOCOL_decode();
	memcpy(pIMU, data_holder1, 14);
}

void MPU6500_getRAWData(uint8_t *data1, uint32_t lag)
{
	PROTOCOL_INS ins = pack_function(MPU6500_MODULE, MPU6500_GETRAWDATA, 0, lag, 0, 0);
	PROTOCOL_send(1, &ins);
	PROTOCOL_decode();
	memcpy(data1, data_holder1, 14);
}

int8_t MPU6500_Init(uint8_t *Configs, uint16_t len)
{
	PROTOCOL_INS ins[200];
	int16_t copied_len = 0;
	uint16_t i = 0;
	uint8_t buf[16] = {0,};
	while (len > copied_len) {
		if ( len - copied_len < 16 ) {
			memcpy(buf, Configs + copied_len, size_t(len*2 - copied_len));
			ins[i++] = pack_data(DATA_MODULE, LIB_DATA1, buf);
		} else {
			ins[i++] = pack_data(DATA_MODULE, LIB_DATA1, Configs + copied_len);
		}
		copied_len += 16;
	}ins[i++] = pack_function(PROTOCOL_MODULE, PROTOCOL_BACK, LIB_DATA1, 0, 0, 0);
	ins[i++] = pack_function(MPU6500_MODULE, MPU6500_INIT, LIB_DATA1, len, 0, 0);

	PROTOCOL_send(i, ins);
	return (int8_t)PROTOCOL_decode();
}


//==================================
void Protocol_debug(uint32_t d1, uint32_t d2, uint32_t d3, uint32_t d4)
{
	PROTOCOL_INS ins = pack_function(PROTOCOL_MODULE, PROTOCOL_DEBUG, d1, d2, d3, d4);
	PROTOCOL_send(1, &ins);
	PROTOCOL_decode();
}

//==================================
void Data_data_n(uint8_t n, uint8_t *data, int len)
{
	PROTOCOL_INS ins[200];
	int16_t copied_len = 0;
	int i = 0;
	uint8_t buf[16] = {0,};
	while (len > copied_len) {
		if ( len - copied_len < 16 ) {
			memcpy(buf, data + copied_len, size_t(len - copied_len));
			ins[i++] = pack_data(DATA_MODULE, n, buf);
		} else {
			ins[i++] = pack_data(DATA_MODULE, n, data + copied_len);
		}
		copied_len += 16;
	}
	ins[i++] = pack_function(PROTOCOL_MODULE, PROTOCOL_SHOW_DATA, n, 0, 0, 0);
	PROTOCOL_send(uint16_t(i), ins);
	PROTOCOL_decode();
}

void Data_back(uint8_t n, uint8_t *data_send, uint8_t *data_recv, int len)
{
	PROTOCOL_INS ins[200];
	int16_t copied_len = 0;
	int i = 0;
	uint8_t buf[16] = {0,};
	while (len > copied_len) {
		if ( len - copied_len < 16 ) {
			memcpy(buf, data_send + copied_len, size_t(len - copied_len));
			ins[i++] = pack_data(DATA_MODULE, n, buf);
		} else {
			ins[i++] = pack_data(DATA_MODULE, n, data_send + copied_len);
		}
		copied_len += 16;
	}
	ins[i++] = pack_function(PROTOCOL_MODULE, PROTOCOL_BACK, n, 0, 0, 0);
	PROTOCOL_send(uint16_t(i), ins);
	PROTOCOL_decode();
	memcpy(data_recv, data_holder1, len);
}