/*
 * YNV_Lis3DSH.c
 *
 *  Created on: 12 janv. 2021
 *      Author: msitest
 */

#include "YNV_Lis3DSH.h"

float Sensitivity;

LIS3DSH_Status_t LIS3DSH_Write_Reg(SPI_HandleTypeDef *posSPI,uint8_t reg_addr,uint8_t *dataW,uint8_t size)
{
	uint8_t buffer[2] = {reg_addr,*dataW};


	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3,GPIO_PIN_RESET);
	if(HAL_SPI_Transmit(posSPI, buffer, size, 10) == HAL_OK)
	{
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
		return LIS3DSH_OK;
	}
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
	return LIS3DSH_ERROR;
}

LIS3DSH_Status_t LIS3DSH_Read_Reg(SPI_HandleTypeDef *posSPI,uint8_t reg_addr,uint8_t *dataR,uint8_t size)
{
	uint8_t spiBuf[4];
	// Mask read bit on register addr, to set bit 8 to 1 to say it's a reading
	spiBuf[0] = reg_addr | 0x80;
	//Enable CS
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3,GPIO_PIN_RESET);
	// Send register addr
	if(HAL_SPI_Transmit(posSPI, spiBuf, 1, 10) ==HAL_OK)
	{
		// Get Register value
		if(HAL_SPI_Receive(posSPI, spiBuf, size, 10) == HAL_OK)
		{
			for(uint8_t i = 0; i < size ; i++)
			{
				dataR[i] = spiBuf[i];
			}
			//Disable CS
			HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
			return LIS3DSH_OK;
		}
	}
	//Disable CS
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
	return LIS3DSH_ERROR;
}
/* config CTRL_REG4 */

LIS3DSH_Status_t LIS3DSH_Init(SPI_HandleTypeDef *posSPI,uint8_t reg_addr,LIS3DSH_init_t *posInitDef)
{
	uint8_t SPIData = 0x00;
	uint8_t SPICheckData = 0x00;

	/* Data register config */
	SPIData |= (posInitDef->XEnable & 0x01);
	SPIData |= (posInitDef->YEnable & 0x02);
	SPIData |= (posInitDef->ZEnable & 0x04);
	SPIData |= (posInitDef->DataUptadeEnable & 0x00);
	SPIData |= (posInitDef->OutputDataRate & 0x10);

	if(LIS3DSH_Write_Reg(posSPI,LIS3DSH_CTRL_REG4,&SPIData,2) == LIS3DSH_OK)
	{
		if (LIS3DSH_Read_Reg(posSPI,LIS3DSH_CTRL_REG4,&SPICheckData,1) == LIS3DSH_OK)
		{
			if(SPICheckData == SPIData)
			{
				return LIS3DSH_OK;
			}
		}
	}
	return LIS3DSH_ERROR;
}
/* config CTRL_REG5 */

LIS3DSH_Status_t LIS3DSH_Init_2(SPI_HandleTypeDef *posSPI,uint8_t reg_addr,LIS3DSH_init_t *posInitDef)
{
	uint8_t SPIData =0x00;
	uint8_t SPICheckData = 0x00;
	/* coef result */

	switch (posInitDef->FullScale)
	{
	case LIS3DSH_FSCALE_2_g:
		Sensitivity = 0.06;
		break;
	case LIS3DSH_FSCALE_4_g:
		Sensitivity = 0.12;
		break;
	case LIS3DSH_FSCALE_6_g:
		Sensitivity = 0.18;
		break;
	case LIS3DSH_FSCALE_8_g:
		Sensitivity = 0.24;
		break;
	case LIS3DSH_FSCALE_16_g:
		Sensitivity = 0.73;
		break;

	}
	/* Data register config */
	SPIData |= (posInitDef->FullScale & 0x00);
	SPIData |= (posInitDef->Bandwith & 0x80);


	if(LIS3DSH_Write_Reg(posSPI,LIS3DSH_CTRL_REG5,&SPIData,2) == LIS3DSH_OK)
	{
		if (LIS3DSH_Read_Reg(posSPI,LIS3DSH_CTRL_REG5,&SPICheckData,1) == LIS3DSH_OK)
		{
			return LIS3DSH_OK;
		}
	}
	return LIS3DSH_ERROR;
}
/* Get position X */

LIS3DSH_Status_t LIS3DSH_Get_X(SPI_HandleTypeDef *posSPI,uint8_t reg_addr,float *pos)
{
	uint8_t dataR[2] = {0x00, 0x00};
	int16_t posX = 0x0000;

	if(LIS3DSH_Read_Reg(posSPI,LIS3DSH_OUT_X,dataR,2) == LIS3DSH_OK )
	{
		posX = ((dataR[1]<<8) | dataR[0]);
		*pos = posX * Sensitivity;
		return LIS3DSH_OK;
	}
	return LIS3DSH_ERROR;
}

/* Get position Y */

LIS3DSH_Status_t LIS3DSH_Get_Y(SPI_HandleTypeDef *posSPI,uint8_t reg_addr,float *pos)
{
	uint8_t dataR[2] = {0x00, 0x00};
	int16_t posY = 0x0000;

	if(LIS3DSH_Read_Reg(posSPI,LIS3DSH_OUT_Y,dataR,2) == LIS3DSH_OK )
	{
		posY = ((dataR[1]<<8) | dataR[0]);
		*pos=posY * Sensitivity;
		return LIS3DSH_OK;
	}
	return LIS3DSH_ERROR;
}

/* Get position X */

LIS3DSH_Status_t LIS3DSH_Get_Z(SPI_HandleTypeDef *posSPI,uint8_t reg_addr, float *pos)
{
	uint8_t dataR[2] = {0x00, 0x00};
	int16_t posZ = 0x0000;

	if(LIS3DSH_Read_Reg(posSPI,LIS3DSH_OUT_Z,dataR,2) == LIS3DSH_OK )
	{
		posZ = ((dataR[1]<<8) | dataR[0]);
		*pos=posZ * Sensitivity;
		return LIS3DSH_OK;
	}
	return LIS3DSH_ERROR;
}



