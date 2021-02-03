/*
 * Lis3DSH.h
 *
 *  Created on: Jan 11, 2021
 *      Author: msitest
 */

#ifndef INC_YNV_LIS3DSH_H_
#define INC_YNV_LIS3DSH_H_

#include "stm32f4xx_hal.h"
#include <stdbool.h>


/* Register Address Define */

#define LIS3DSH_CTRL_REG4			0x20
#define LIS3DSH_CTRL_REG5			0x24
#define LIS3DSH_STATUS				0x27
#define LIS3DSH_OUT_X				0x28
#define LIS3DSH_OUT_Y				0x2A
#define LIS3DSH_OUT_Z				0x2C


/* Configuration Parameters define */

#define LIS3DSH_X_ENABLE			((uint8_t)0x01)
#define LIS3DSH_Y_ENABLE			((uint8_t)0x02)
#define LIS3DSH_Z_ENABLE			((uint8_t)0x04)
#define LIS3DSH_X_DISABLE			((uint8_t)0x00)
#define LIS3DSH_Y_DISABLE			((uint8_t)0x00)
#define LIS3DSH_Z_DISABLE			((uint8_t)0x00)

#define LIS3DSH_DATA_UPDATE_ENABLE	((uint8_t)0x00)
#define LIS3DSH_DATA_UPDATE_DISABLE	((uint8_t)0x08)

/* Output Data Rate (Hz) */
#define LIS3DSH_ODR_DISABLE			((uint8_t)0x00)
#define LIS3DSH_ODR_RATE_3_125_HZ	((uint8_t)0x10)
#define LIS3DSH_ODR_RATE_6_25_HZ	((uint8_t)0x20)
#define LIS3DSH_ODR_RATE_12_5_HZ	((uint8_t)0x30)
#define LIS3DSH_ODR_RATE_25_HZ		((uint8_t)0x40)
#define LIS3DSH_ODR_RATE_50_HZ		((uint8_t)0x50)
#define LIS3DSH_ODR_RATE_100_HZ		((uint8_t)0x60)
#define LIS3DSH_ODR_RATE_400_HZ		((uint8_t)0x70)
#define LIS3DSH_ODR_RATE_800_HZ		((uint8_t)0x80)
#define LIS3DSH_ODR_RATE_1600_HZ	((uint8_t)0x90)

/* Choice of full-scale (g) */
#define LIS3DSH_FSCALE_2_g			((uint8_t)0x00)
#define LIS3DSH_FSCALE_4_g			((uint8_t)0x08)
#define LIS3DSH_FSCALE_6_g			((uint8_t)0x10)
#define LIS3DSH_FSCALE_8_g			((uint8_t)0x18)
#define LIS3DSH_FSCALE_16_g			((uint8_t)0x20)

/* Choice Anti-aliasing filter bandwidth (Hz) */
#define LIS3DSH_BANDWITH_800_HZ		((uint8_t)0x00)
#define LIS3DSH_BANDWITH_200_HZ		((uint8_t)0x40)
#define LIS3DSH_BANDWITH_400_HZ		((uint8_t)0x80)
#define LIS3DSH_BANDWITH_50_HZ		((uint8_t)0xC0)

/* Return Status define */
#define LIS3DSH_STATUS_OK 			"LIS3DSH OK !\n\r"
#define LIS3DSH_STATUS_ERROR		"LIS3DSH ERROR !\n\r"

/* Init Struct */
typedef struct
{
	uint8_t XEnable;
	uint8_t YEnable;
	uint8_t ZEnable;
	uint8_t DataUptadeEnable;
	uint8_t OutputDataRate;
	uint8_t FullScale;
	uint8_t Bandwith;
}LIS3DSH_init_t;

/* Status enum */
typedef enum
{
	LIS3DSH_OK,
	LIS3DSH_ERROR,
}LIS3DSH_Status_t;

/* Write Function */
LIS3DSH_Status_t LIS3DSH_Write_Reg(SPI_HandleTypeDef *posSPI,
		uint8_t reg_addr,
		uint8_t *dataW,
		uint8_t size);

/* Read Function */
LIS3DSH_Status_t LIS3DSH_Read_Reg(SPI_HandleTypeDef *posSPI,
		uint8_t reg_addr,
		uint8_t *dataR,
		uint8_t size);
/* Init Function */
LIS3DSH_Status_t LIS3DSH_Init(SPI_HandleTypeDef *posSPI,
		uint8_t dev_addr,
		LIS3DSH_init_t *posInitDef);

LIS3DSH_Status_t LIS3DSH_Init_2(SPI_HandleTypeDef *posSPI,
		uint8_t dev_addr,
		LIS3DSH_init_t *posInitDef);
/* Get position X */
LIS3DSH_Status_t LIS3DSH_Get_X(SPI_HandleTypeDef *posSPI,
		uint8_t reg_addr,
		float *pos);
/* Get position Y */
LIS3DSH_Status_t LIS3DSH_Get_Y(SPI_HandleTypeDef *posSPI,
		uint8_t reg_addr,
		float *pos);
/* Get position Z */
LIS3DSH_Status_t LIS3DSH_Get_Z(SPI_HandleTypeDef *posSPI,
		uint8_t reg_addr,
		float *pos);


#endif /* INC_YNV_LIS3DSH_H_ */
