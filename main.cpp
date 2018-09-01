#include <cstdio>
#include <cstring>
#include "lib.h"

#define MPU6500_InitRegNum 11
int main()
{

	 uint8_t MPU6500_InitData[MPU6500_InitRegNum][2] = {
	     {0x80, MPU6500_PWR_MGMT_1},     // [0]  Reset Device
	     {0x04, MPU6500_PWR_MGMT_1},     // [1]  Clock Source
	     {0x10, MPU6500_INT_PIN_CFG},    // [2]  Set INT_ANYRD_2CLEAR
	     {0x01, MPU6500_INT_ENABLE},     // [3]  Set RAW_RDY_EN
	     {0x00, MPU6500_PWR_MGMT_2},     // [4]  Enable Acc & Gyro
	     {0x00, MPU6500_SMPLRT_DIV},     // [5]  Sample Rate Divider
	     {0x18, MPU6500_GYRO_CONFIG},    // [6]  default : +-2000dps
	     {0x08, MPU6500_ACCEL_CONFIG},   // [7]  default : +-4G
	     {0x07, MPU6500_CONFIG},         // [8]  default : LPS_41Hz
	     {0x03, MPU6500_ACCEL_CONFIG_2}, // [9]  default : LPS_41Hz
	     {0x30, MPU6500_USER_CTRL},      // [10] Set I2C_MST_EN, I2C_IF_DIS
	 };


	uint8_t my_InitData[MPU6500_InitRegNum][2] = {
			{0x80, MPU6500_PWR_MGMT_1},
			{0x04, MPU6500_PWR_MGMT_1},
			{0x09, MPU6500_GYRO_CONFIG},
			{0x00, MPU6500_INT_ENABLE},
			{0x00, MPU6500_PWR_MGMT_2},
			{0x00, MPU6500_SMPLRT_DIV},
			{0x00, MPU6500_INT_PIN_CFG},
			{0x08, MPU6500_ACCEL_CONFIG},
			{0x07, MPU6500_CONFIG},
			{0x0B, MPU6500_ACCEL_CONFIG_2},
			{0x09, MPU6500_GYRO_CONFIG},
	};

	int16_t data[7]={0};
	uint8_t raw_data[14]={0};

	int8_t ret = 0;
	uint16_t ret2 = 0;
	protocol_init();
#if 0
	ret = MPU6500_Check();
	printf("ret check = %d\n",ret);
	ret2 = MPU6500_RWReg(1000, 0x75 , 0);
	printf("ret2 reg= %d\n",ret2);
	ret2 = MPU6500_RWReg(1000, 0x75 , 0);
	printf("ret2 reg= %d\n",ret2);

	fflush(stdout);
	ret = Stepper_Init(2);
	printf("ret = %d\n",ret);
	Stepper_Init(3);

	Stepper_Set_Speed(2, 250, 250);
	Stepper_Set_Speed(3, 500, 500);

	Stepper_Move(2, 1, 2000*5/10);
	Stepper_Move(3, 0, 2000);
#endif
	//printf("init is %d\n",MPU6500_Init((uint8_t*)MPU6500_InitData, 11));
	printf("init is %d\n",MPU6500_Init((uint8_t*)my_InitData, 11));
	//printf("init is %d\n",MPU6500_Init(nullptr,11));

	usleep(20000);
	//SPI_setSpeed(SPI_BaudRatePrescaler_8);
	usleep(20000);
while(1)
{
	MPU6500_getData(data);
	for (int i = 0; i < 7; ++i) {
		printf("data[%d] = %d\n", i, data[i]);
	}
	usleep(10000);
}
//	while(ret != '\r')
//	{
//		ret = get_data();
//		if(ret != 0xAA)
//			printf("%4x, %c\n",ret,ret);
//	}
	protocol_deinit();
	return 0;
}