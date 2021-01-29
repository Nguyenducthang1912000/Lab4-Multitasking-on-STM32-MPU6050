/*
 * MPU6050.h
 *
 *  Created on: Jan 29, 2021
 *      Author: Duc Thang
 */

#ifndef SRC_MPU6050_H_
#define SRC_MPU6050_H_
#include "stm32f4xx_hal.h"
#include "main.h"

/* MPU6050 register address */
#define MPU6050_ADDR 0xD0
#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75

I2C_HandleTypeDef hi2c1;
typedef struct {
	float x,y,z;
}MPU6050;
void MPU6050_Init(void);
void MPU6050_Read_Accel(MPU6050 *Accel);
void MPU6050_Read_Gyro(MPU6050 *Gyro);
#endif /* SRC_MPU6050_H_ */
