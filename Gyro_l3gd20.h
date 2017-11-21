#ifndef GYRO_L3GD20_H_
#define GYRO_L3GD20_H_
//--------------------------------------------------------
#include "stm32l4xx_hal.h"
#include "string.h"
//-----------------------LEDs-----------------------------
#define LD_red GPIO_PIN_2
#define LD_green GPIO_PIN_8
#define LD_red_ON HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
#define LD_red_OFF HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
#define LD_green_ON HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_SET);
#define LD_green_OFF HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, GPIO_PIN_RESET);
//--------------------------------------------------------

//---------------SPI Chip select config-------------------
#define CS_RESET HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET)
#define CS_SET HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET)
#define DUMMY ((uint8_t) 0x00)
#define WHO_AM_I_ADDR 0x0F
//--------------------------------------------------------

//----------------Set RW and MS bits----------------------
#define READWRITE_CMD ((uint8_t) 0x80)
#define MULTIBYTE ((uint8_t) 0x40)
//--------------------------------------------------------

//--------------------------------------------------------
//--------------Gyro params description-------------------
//--------------------------------------------------------
#define CTR_REG1_ADDR 0x20 //power mode, x, y, z, enable, bandwidth, datarate
#define CTR_REG2_ADDR 0x21 //filter's settings
//#define CTR_REG3_ADDR 0x22
#define CTR_REG4_ADDR 0x23 //dps range, SPI mode (3 or 4 wire)
#define CTR_REG5_ADDR 0x24 // filter enable 
//--------------------------------------------------------
#define TEMP_REG 0x26
//--------------------------------------------------------
#define PWR_NORMAL_MODE ((uint8_t) 0x08)
//--------------------------------------------------------
#define DATARATE_95 ((uint8_t) 0x00)
#define DATARATE_190 ((uint8_t) 0x40)
#define DATARATE_380 ((uint8_t) 0x80)
#define DATARATE_760 ((uint8_t) 0xC0)
//--------------------------------------------------------
#define X_ENABLE ((uint8_t) 0x02)
#define Y_ENABLE ((uint8_t) 0x01)
#define Z_ENABLE ((uint8_t) 0x04)
#define XYZ_ENABLE ((uint8_t) 0x07)
//--------------------------------------------------------
#define RANGE_250 ((uint8_t) 0x00)
#define RANGE_500 ((uint8_t) 0x10)
#define RANGE_2000 ((uint8_t) 0x20)
#define BLOCK_DATA_UPDATE ((uint8_t) 0x80)
//--------------------------------------------------------
#define SERIALINTERFACE_4WIRE ((uint8_t) 0x00)
#define SERIALINTERFACE_3WIRE ((uint8_t) 0x01)
//--------------------------------------------------------
#define HP_FILTER_ENABLE ((uint8_t) 0x10)
#define HP_FILTER_NORMALMODE ((uint8_t) 0x20) 
#define HP_FILTER_CUTOFF_1_8 ((uint8_t) 0x03)
#define HP_FILTER_CUTOFF_0_018 ((uint8_t) 0x09)
//--------------------------------------------------------
#define OUT_X_L_ADDR 0x28
#define OUT_X_H_ADDR 0x29
#define OUT_Y_L_ADDR 0x2A
#define OUT_Y_H_ADDR 0x2B
#define OUT_Z_L_ADDR 0x2C
#define OUT_Z_H_ADDR 0x2D
//--------------------------------------------------------
//--------------------------------------------------------
//--------------------------------------------------------

void Gyro_Ini(void);
void Gyro_Read(void);
//--------------------------------------------------------
/* GYRO_L3GD20_H_ */
#endif
