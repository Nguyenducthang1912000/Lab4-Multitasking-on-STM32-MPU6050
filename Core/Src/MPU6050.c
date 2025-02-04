/*
 * MPU6050.c
 *
 *  Created on: Jan 29, 2021
 *      Author: Duc Thang
 */

#include "MPU6050.h"
/* Raw value */
float Accel_X_RAW,Accel_Y_RAW,Accel_Z_RAW;
float Gyro_X_RAW,Gyro_Y_RAW,Gyro_Z_RAW;
void MPU6050_Init(void)
{
	uint8_t check, Data;
	// check device ID WHO_AM_I

	HAL_I2C_Mem_Read(&hi2c1, MPU6050_ADDR, WHO_AM_I_REG, 1 , &check, 1, 1000);

	if (check == 104)
	{
		// power management register 0X6B we should write all 0's to wake the sensor up
		Data = 0;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, PWR_MGMT_1_REG, 1,&Data, 1, 1000);

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		Data = 0x07;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, 1000);
	}
}
void MPU6050_Read_Accel(MPU6050 *Accel)
{
	uint8_t Rec_Data[6];
	// Read 6 BYTES of data starting from ACCEL_XOUT_H register

	HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, 1000);

	Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

	/*** convert the RAW values into acceleration in 'g'
	     we have to divide according to the Full scale value set in FS_SEL
	     I have configured FS_SEL = 0. So I am dividing by 16384.0
	     for more details check ACCEL_CONFIG Register              ****/

	Accel->x = Accel_X_RAW/16384.0;  // get the float g
	Accel->y = Accel_Y_RAW/16384.0;
	Accel->z = Accel_Z_RAW/16384.0;

}
void MPU6050_Read_Gyro(MPU6050 *Gyro)
{
	uint8_t Rec_Data[6];
	// Read 6 BYTES of data starting from GYRO_XOUT_H register

	HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, 1000);

	Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

	/*** convert the RAW values into dps (°/s)
	     we have to divide according to the Full scale value set in FS_SEL
	     I have configured FS_SEL = 0. So I am dividing by 131.0
	     for more details check GYRO_CONFIG Register              ****/

	Gyro->x = Gyro_X_RAW/131.0;
	Gyro->y = Gyro_Y_RAW/131.0;
	Gyro->z = Gyro_Z_RAW/131.0;

}
