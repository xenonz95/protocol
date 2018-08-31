//
// Created by root on 18-8-29.
//

#ifndef PROTOCOL_LIB_H
#define PROTOCOL_LIB_H


#include <cstdlib>

#include "protocol.h"


//PWM
uint8_t PWM_setting(uint8_t power);
//PWM END

//SPI
uint8_t SPI_setFast();
uint16_t SPI_rw_1(uint16_t readBuf,uint16_t writeBuf);
//SPI END

//STEPPER
int8_t Stepper_Init(uint8_t ch); // ch = 2 PA0 PA1
//int8_t Stepper_Enable(uint8_t ch, uint8_t enable);
int8_t Stepper_Set_Speed(uint8_t ch, uint32_t max_speed, uint32_t min_speed); // max 1500 min 500
//int8_t Stepper_Set_Home(uint8_t ch);
//int32_t Stepper_Get_Position(uint8_t ch);
int8_t Stepper_Move(uint8_t ch, uint8_t dir, uint32_t steps); //use this
//int8_t Stepper_Run(uint8_t ch, uint8_t dir);
//int8_t Stepper_Stop(uint8_t ch);
//int8_t Stepper_Hard_Stop(uint8_t ch);
//int8_t Stepper_Is_Busy(uint8_t ch);
//STEPPER END

//MPU6500
#define BUF_SIZE 2
union u8u16
{
	uint8_t u8[BUF_SIZE];
	uint16_t u16;
};
/*=====================================================================================================*/
/*=====================================================================================================*/
/*
|     |            ACCELEROMETER           |
| LPF |  BandW  |  Delay  | Noise | Sample |
+-----+---------+---------+-------+--------+
|  x  |  1130Hz |  0.75ms | 250Hz |  4kHz  |
|  0  |   460Hz |  1.94ms | 250Hz |  1kHz  |
|  1  |   184Hz |  5.80ms | 250Hz |  1kHz  |
|  2  |    92Hz |  7.80ms | 250Hz |  1kHz  |
|  3  |    41Hz | 11.80ms | 250Hz |  1kHz  |
|  4  |    20Hz | 19.80ms | 250Hz |  1kHz  |
|  5  |    10Hz | 35.70ms | 250Hz |  1kHz  |
|  6  |     5Hz | 66.96ms | 250Hz |  1kHz  |
|  7  |   460Hz |  1.94ms | 250Hz |  1kHz  |
*/
/*
|     |          GYROSCOPE         |    TEMPERATURE    |
| LPF |  BandW  |  Delay  | Sample |  BandW  |  Delay  |
+-----+---------+---------+--------+---------+---------+
|  x  |  8800Hz | 0.064ms |  32kHz |  4000Hz |  0.04ms |
|  x  |  3600Hz |  0.11ms |  32kHz |  4000Hz |  0.04ms |
|  0  |   250Hz |  0.97ms |   8kHz |  4000Hz |  0.04ms |
|  1  |   184Hz |   2.9ms |   1kHz |   188Hz |   1.9ms |
|  2  |    92Hz |   3.9ms |   1kHz |    98Hz |   2.8ms |
|  3  |    41Hz |   5.9ms |   1kHz |    42Hz |   4.8ms |
|  4  |    20Hz |   9.9ms |   1kHz |    20Hz |   8.3ms |
|  5  |    10Hz | 17.85ms |   1kHz |    10Hz |  13.4ms |
|  6  |     5Hz | 33.48ms |   1kHz |     5Hz |  18.6ms |
|  7  |  3600Hz |  0.17ms |   8kHz |  4000Hz |  0.04ms |
*/

typedef enum
{
	MPU_GyrLPS_250Hz = 0x00,
	MPU_GyrLPS_184Hz = 0x01,
	MPU_GyrLPS_92Hz = 0x02,
	MPU_GyrLPS_41Hz = 0x03,
	MPU_GyrLPS_20Hz = 0x04,
	MPU_GyrLPS_10Hz = 0x05,
	MPU_GyrLPS_5Hz = 0x06,
	MPU_GyrLPS_3600Hz = 0x07,
} MPU_GyrLPF_TypeDef;

typedef enum
{
	MPU_AccLPS_460Hz = 0x00,
	MPU_AccLPS_184Hz = 0x01,
	MPU_AccLPS_92Hz = 0x02,
	MPU_AccLPS_41Hz = 0x03,
	MPU_AccLPS_20Hz = 0x04,
	MPU_AccLPS_10Hz = 0x05,
	MPU_AccLPS_5Hz = 0x06,
	MPU_AccLPS_Disable = 0x07,
} MPU_AccLPF_TypeDef;

typedef enum
{
	MPU_GyrFS_250dps = 0x00,
	MPU_GyrFS_500dps = 0x08,
	MPU_GyrFS_1000dps = 0x10,
	MPU_GyrFS_2000dps = 0x18
} MPU_GyrFS_TypeDef;

typedef enum
{
	MPU_AccFS_2g = 0x00,
	MPU_AccFS_4g = 0x08,
	MPU_AccFS_8g = 0x10,
	MPU_AccFS_16g = 0x18
} MPU_AccFS_TypeDef;

typedef enum
{
	MPU_MagFS_14b = 0x00,
	MPU_MagFS_16b = 0x10
} MPU_MagFS_TypeDef;

typedef struct
{
	MPU_GyrFS_TypeDef MPU_Gyr_FullScale;
	MPU_GyrLPF_TypeDef MPU_Gyr_LowPassFilter;
	MPU_AccFS_TypeDef MPU_Acc_FullScale;
	MPU_AccLPF_TypeDef MPU_Acc_LowPassFilter;
	MPU_MagFS_TypeDef MPU_Mag_FullScale;
} MPU_ConfigTypeDef;

/* ---- Sensitivity --------------------------------------------------------- */

#define MPU6500A_2g ((float)0.000061035156f)  // 0.000061035156 g/LSB
#define MPU6500A_4g ((float)0.000122070312f)  // 0.000122070312 g/LSB
#define MPU6500A_8g ((float)0.000244140625f)  // 0.000244140625 g/LSB
#define MPU6500A_16g ((float)0.000488281250f) // 0.000488281250 g/LSB

#define MPU6500G_250dps ((float)0.007633587786f)  // 0.007633587786 dps/LSB
#define MPU6500G_500dps ((float)0.015267175572f)  // 0.015267175572 dps/LSB
#define MPU6500G_1000dps ((float)0.030487804878f) // 0.030487804878 dps/LSB
#define MPU6500G_2000dps ((float)0.060975609756f) // 0.060975609756 dps/LSB

#define MPU6500T_85degC ((float)0.002995177763f) // 0.002995177763 degC/LSB

/* ---- MPU6500 Reg --------------------------------------------------------- */

#define MPU6500_I2C_ADDR ((uint8_t)0xD0)
#define MPU6500_Device_ID ((uint8_t)0x70) // In MPU6500

#define MPU6500_SELF_TEST_XG ((uint8_t)0x00)
#define MPU6500_SELF_TEST_YG ((uint8_t)0x01)
#define MPU6500_SELF_TEST_ZG ((uint8_t)0x02)
#define MPU6500_SELF_TEST_XA ((uint8_t)0x0D)
#define MPU6500_SELF_TEST_YA ((uint8_t)0x0E)
#define MPU6500_SELF_TEST_ZA ((uint8_t)0x0F)
#define MPU6500_XG_OFFSET_H ((uint8_t)0x13)
#define MPU6500_XG_OFFSET_L ((uint8_t)0x14)
#define MPU6500_YG_OFFSET_H ((uint8_t)0x15)
#define MPU6500_YG_OFFSET_L ((uint8_t)0x16)
#define MPU6500_ZG_OFFSET_H ((uint8_t)0x17)
#define MPU6500_ZG_OFFSET_L ((uint8_t)0x18)
#define MPU6500_SMPLRT_DIV ((uint8_t)0x19)
#define MPU6500_CONFIG ((uint8_t)0x1A)
#define MPU6500_GYRO_CONFIG ((uint8_t)0x1B)
#define MPU6500_ACCEL_CONFIG ((uint8_t)0x1C)
#define MPU6500_ACCEL_CONFIG_2 ((uint8_t)0x1D)
#define MPU6500_LP_ACCEL_ODR ((uint8_t)0x1E)
#define MPU6500_MOT_THR ((uint8_t)0x1F)
#define MPU6500_FIFO_EN ((uint8_t)0x23)
#define MPU6500_I2C_MST_CTRL ((uint8_t)0x24)
#define MPU6500_I2C_SLV0_ADDR ((uint8_t)0x25)
#define MPU6500_I2C_SLV0_REG ((uint8_t)0x26)
#define MPU6500_I2C_SLV0_CTRL ((uint8_t)0x27)
#define MPU6500_I2C_SLV1_ADDR ((uint8_t)0x28)
#define MPU6500_I2C_SLV1_REG ((uint8_t)0x29)
#define MPU6500_I2C_SLV1_CTRL ((uint8_t)0x2A)
#define MPU6500_I2C_SLV2_ADDR ((uint8_t)0x2B)
#define MPU6500_I2C_SLV2_REG ((uint8_t)0x2C)
#define MPU6500_I2C_SLV2_CTRL ((uint8_t)0x2D)
#define MPU6500_I2C_SLV3_ADDR ((uint8_t)0x2E)
#define MPU6500_I2C_SLV3_REG ((uint8_t)0x2F)
#define MPU6500_I2C_SLV3_CTRL ((uint8_t)0x30)
#define MPU6500_I2C_SLV4_ADDR ((uint8_t)0x31)
#define MPU6500_I2C_SLV4_REG ((uint8_t)0x32)
#define MPU6500_I2C_SLV4_DO ((uint8_t)0x33)
#define MPU6500_I2C_SLV4_CTRL ((uint8_t)0x34)
#define MPU6500_I2C_SLV4_DI ((uint8_t)0x35)
#define MPU6500_I2C_MST_STATUS ((uint8_t)0x36)
#define MPU6500_INT_PIN_CFG ((uint8_t)0x37)
#define MPU6500_INT_ENABLE ((uint8_t)0x38)
#define MPU6500_INT_STATUS ((uint8_t)0x3A)
#define MPU6500_ACCEL_XOUT_H ((uint8_t)0x3B)
#define MPU6500_ACCEL_XOUT_L ((uint8_t)0x3C)
#define MPU6500_ACCEL_YOUT_H ((uint8_t)0x3D)
#define MPU6500_ACCEL_YOUT_L ((uint8_t)0x3E)
#define MPU6500_ACCEL_ZOUT_H ((uint8_t)0x3F)
#define MPU6500_ACCEL_ZOUT_L ((uint8_t)0x40)
#define MPU6500_TEMP_OUT_H ((uint8_t)0x41)
#define MPU6500_TEMP_OUT_L ((uint8_t)0x42)
#define MPU6500_GYRO_XOUT_H ((uint8_t)0x43)
#define MPU6500_GYRO_XOUT_L ((uint8_t)0x44)
#define MPU6500_GYRO_YOUT_H ((uint8_t)0x45)
#define MPU6500_GYRO_YOUT_L ((uint8_t)0x46)
#define MPU6500_GYRO_ZOUT_H ((uint8_t)0x47)
#define MPU6500_GYRO_ZOUT_L ((uint8_t)0x48)
#define MPU6500_EXT_SENS_DATA_00 ((uint8_t)0x49)
#define MPU6500_EXT_SENS_DATA_01 ((uint8_t)0x4A)
#define MPU6500_EXT_SENS_DATA_02 ((uint8_t)0x4B)
#define MPU6500_EXT_SENS_DATA_03 ((uint8_t)0x4C)
#define MPU6500_EXT_SENS_DATA_04 ((uint8_t)0x4D)
#define MPU6500_EXT_SENS_DATA_05 ((uint8_t)0x4E)
#define MPU6500_EXT_SENS_DATA_06 ((uint8_t)0x4F)
#define MPU6500_EXT_SENS_DATA_07 ((uint8_t)0x50)
#define MPU6500_EXT_SENS_DATA_08 ((uint8_t)0x51)
#define MPU6500_EXT_SENS_DATA_09 ((uint8_t)0x52)
#define MPU6500_EXT_SENS_DATA_10 ((uint8_t)0x53)
#define MPU6500_EXT_SENS_DATA_11 ((uint8_t)0x54)
#define MPU6500_EXT_SENS_DATA_12 ((uint8_t)0x55)
#define MPU6500_EXT_SENS_DATA_13 ((uint8_t)0x56)
#define MPU6500_EXT_SENS_DATA_14 ((uint8_t)0x57)
#define MPU6500_EXT_SENS_DATA_15 ((uint8_t)0x58)
#define MPU6500_EXT_SENS_DATA_16 ((uint8_t)0x59)
#define MPU6500_EXT_SENS_DATA_17 ((uint8_t)0x5A)
#define MPU6500_EXT_SENS_DATA_18 ((uint8_t)0x5B)
#define MPU6500_EXT_SENS_DATA_19 ((uint8_t)0x5C)
#define MPU6500_EXT_SENS_DATA_20 ((uint8_t)0x5D)
#define MPU6500_EXT_SENS_DATA_21 ((uint8_t)0x5E)
#define MPU6500_EXT_SENS_DATA_22 ((uint8_t)0x5F)
#define MPU6500_EXT_SENS_DATA_23 ((uint8_t)0x60)
#define MPU6500_I2C_SLV0_DO ((uint8_t)0x63)
#define MPU6500_I2C_SLV1_DO ((uint8_t)0x64)
#define MPU6500_I2C_SLV2_DO ((uint8_t)0x65)
#define MPU6500_I2C_SLV3_DO ((uint8_t)0x66)
#define MPU6500_I2C_MST_DELAY_CTRL ((uint8_t)0x67)
#define MPU6500_SIGNAL_PATH_RESET ((uint8_t)0x68)
#define MPU6500_MOT_DETECT_CTRL ((uint8_t)0x69)
#define MPU6500_USER_CTRL ((uint8_t)0x6A)
#define MPU6500_PWR_MGMT_1 ((uint8_t)0x6B)
#define MPU6500_PWR_MGMT_2 ((uint8_t)0x6C)
#define MPU6500_FIFO_COUNTH ((uint8_t)0x72)
#define MPU6500_FIFO_COUNTL ((uint8_t)0x73)
#define MPU6500_FIFO_R_W ((uint8_t)0x74)
#define MPU6500_WHO_AM_I ((uint8_t)0x75) // ID = 0x70 In MPU6500
#define MPU6500_XA_OFFSET_H ((uint8_t)0x77)
#define MPU6500_XA_OFFSET_L ((uint8_t)0x78)
#define MPU6500_YA_OFFSET_H ((uint8_t)0x7A)
#define MPU6500_YA_OFFSET_L ((uint8_t)0x7B)
#define MPU6500_ZA_OFFSET_H ((uint8_t)0x7D)
#define MPU6500_ZA_OFFSET_L ((uint8_t)0x7E)

#define MPU6500_I2C_SLVx_EN ((uint8_t)0x80)
#define MPU6500_I2C_SLV4_DONE ((uint8_t)0x40)
#define MPU6500_I2C_SLV4_NACK ((uint8_t)0x10)
/*=====================================================================================================*/
/*=====================================================================================================*/
uint16_t MPU6500_RWReg(uint16_t Data, uint8_t addr, uint8_t writeLen);
int8_t MPU6500_Init(uint8_t *Configs, uint16_t len);
int8_t MPU6500_Check();
void MPU6500_getData(int16_t *pIMU);
//MPU6500 END


#endif //PROTOCOL_LIB_H
