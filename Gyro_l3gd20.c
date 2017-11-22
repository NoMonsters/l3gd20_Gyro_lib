#include "stm32l4xx_hal.h"
#include "Gyro_l3gd20.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
//--------------------------------------------------------
extern SPI_HandleTypeDef hspi2;
extern UART_HandleTypeDef huart2;
uint8_t buf2[8]={0};
char str1[30]={0};
uint8_t test_var=10;
//--------------------------------------------------------
static void Error()
{
	LD_red_ON;
}
//--------------------------------------------------------
uint8_t SPIxWriteRead(uint8_t Byte)
{
	uint8_t RecivedByte = 0;
	if(HAL_SPI_TransmitReceive(&hspi2, (uint8_t*) &Byte, (uint8_t*) &RecivedByte, 1, 0x1000 ) != HAL_OK)
	{
		Error();
	}
	return RecivedByte;
}
//--------------------------------------------------------
void Gyro_IO_Read(uint8_t *pBuffer, uint8_t RegAddr, uint16_t NumByteToRead)
{
	if(NumByteToRead > 0x01)
	{
		RegAddr |= (uint8_t) (READWRITE_CMD | MULTIBYTE);
	}		
	else
	{
		RegAddr |= (uint8_t) READWRITE_CMD;
	}
	CS_RESET;
	SPIxWriteRead(RegAddr);
	while(NumByteToRead>0)
	{
		*pBuffer=SPIxWriteRead(DUMMY);	
		NumByteToRead--;
		pBuffer++;
	}
	CS_SET;
}
//--------------------------------------------------------
void Gyro_IO_Write(uint8_t *pBuffer, uint8_t RegAddr, uint16_t NumByteToWrite)
{
	CS_SET;
	if(NumByteToWrite > 0x01)
	{
		RegAddr |= (uint8_t) MULTIBYTE;
	}		
	CS_RESET;
	SPIxWriteRead(RegAddr);
	while(NumByteToWrite>=0x01)
	{
		SPIxWriteRead(*pBuffer);
		NumByteToWrite--;
		pBuffer++;
	}
	CS_SET;
}
//--------------------------------------------------------
uint8_t Gyro_ReadID(void)
{
	uint8_t ctrl=0;
	Gyro_IO_Read(&ctrl, WHO_AM_I_ADDR, 1);	
	return ctrl;
}
//--------------------------------------------------------
void GyroInit(uint8_t InitStruct[])
{
	//uint8_t ctrl=0;
	//ctrl=(uint8_t) (InitStruct);
	Gyro_IO_Write(&InitStruct[0], CTR_REG1_ADDR, 1);
	//ctrl = (uint8_t) (InitStruct>>8);
	Gyro_IO_Write(&InitStruct[1], CTR_REG4_ADDR, 1);
	Gyro_IO_Write(&InitStruct[2], CTR_REG5_ADDR, 1);
	Gyro_IO_Write(&InitStruct[3], CTR_REG2_ADDR, 1);
	
	
}
//--------------------------------------------------------
void Gyro_Ini()
{
	uint8_t check=0,ctrl[4]={0};
	HAL_Delay(1000);
	if(Gyro_ReadID() == 0xD4)
	{
		LD_green_ON;
	}		
	else Error(); 
	
	ctrl[0] = DATARATE_190 | XYZ_ENABLE | PWR_NORMAL_MODE; //CTRL_REG1 set up
	ctrl[1] =	SERIALINTERFACE_4WIRE | RANGE_500 | BLOCK_DATA_UPDATE;          //CTRL_REG4 set up
	ctrl[2] = HP_FILTER_ENABLE;                            //CTRL_REG5 set up
	ctrl[3] = HP_FILTER_NORMALMODE; //CTRL_REG2 set up
	
	GyroInit(ctrl);

}
//--------------------------------------------------------
void Gyro_GetXYZ(int16_t* pData)
{
	int8_t buffer[6];
//	uint8_t i = 0x00;
//	float valueinfloat = 0;
	Gyro_IO_Read( (uint8_t*)& buffer[0], OUT_X_L_ADDR, 1);
	Gyro_IO_Read( (uint8_t*)& buffer[1], OUT_X_H_ADDR, 1);
	Gyro_IO_Read( (uint8_t*)& buffer[2], OUT_Y_L_ADDR, 1);
	Gyro_IO_Read( (uint8_t*)& buffer[3], OUT_Y_H_ADDR, 1);
	Gyro_IO_Read( (uint8_t*)& buffer[4], OUT_Z_L_ADDR, 1);
	Gyro_IO_Read( (uint8_t*)& buffer[5], OUT_Z_H_ADDR, 1);
//	for(i=0; i<3; i++)
//	{
//		valueinfloat = ((buffer[2*i+1] << 8) + buffer[2*i]);
//		pData[i] = (int16_t) valueinfloat;
//	}
	pData[0]= buffer[0] | (buffer[1]<<8); //X DATA
	pData[1]= buffer[2] | (buffer[3]<<8); //Y DATA
	pData[2]= buffer[4] | (buffer[5]<<8); //Z DATA
	
}
//--------------------------------------------------------
void Gyro_Read(void)
{
	int16_t buffer[3]={0};
	float xval=0, yval=0, zval = 0;
	Gyro_GetXYZ(buffer);
	xval = buffer[0]*0.0175;
	yval = buffer[1]*0.0175;
	zval = buffer[2]*0.0175;
	//sprintf(str1,"X:06%d Y:06%d Z:06%d\r\n", xval, yval, zval);
	sprintf(str1,"%f %f %f\r\n", xval, yval, zval);
	HAL_UART_Transmit(&huart2, (uint8_t*) str1, strlen(str1), 0xFFFF);	
	HAL_Delay(10);
}
//--------------------------------------------------------
