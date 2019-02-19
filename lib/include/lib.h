//
// Created by root on 18-8-29.
//

#ifndef PROTOCOL_LIB_H
#define PROTOCOL_LIB_H


#include "function.h"
#include "protocol.h"

extern uint8_t data_holder1[1024];
extern uint8_t DATA_counter;

PROTOCOL_INS pack_vm(uint8_t opcode, uint8_t funt, uint8_t rs1, int32_t ris2, int8_t rt, uint8_t
sw);

PROTOCOL_INS pack_data_i(uint16_t module,
                       uint16_t command,
                       PROTOCOL_DATA data);

PROTOCOL_INS pack_data(uint16_t module,
                                     uint16_t command,
                                     uint8_t data[16]);

PROTOCOL_INS pack_function(uint16_t module,
                                         uint16_t command,
                                         int32_t p1,
                                         int32_t p2,
                                         int32_t p3,
                                         int32_t p4);

enum{
	PROTOCOL_MODULE = 0,
	SPI_MODULE = 1,
	PWM_MODULE,
	MPU6500_MODULE,
	GPIO_MODULE,
	STEPPER_MODULE,
	DATA_MODULE,
	VM_MODULE,
	STOPWATCH_MODULE,
};

enum{
	PROTOCOL_FAIL = 0,
	PROTOCOL_NORMAL,
	PROTOCOL_PURE_DATA,
	PROTOCOL_DEBUG,
	PROTOCOL_PRINT,
	PROTOCOL_BACK,
	PROTOCOL_SHOW_DATA,
	PROTOCOL_TEST,
	PROTOCOL_SHOW_STOPWATCH,

};

enum{
	LIB_DATA1 = 0,
	LIB_DATA2,
	LIB_DATA3,
	LIB_DATA4,
	LIB_NULL,
};

enum{
	VM_COMMAND = 1,
	VM_DEBUG,
	VM_USE_REG,
	VM_NOTUSE_REG,
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

enum {
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

enum{
	STOPWATCH_TIC = 1,
	STOPWATCH_TOC,
};

#endif //PROTOCOL_LIB_H
