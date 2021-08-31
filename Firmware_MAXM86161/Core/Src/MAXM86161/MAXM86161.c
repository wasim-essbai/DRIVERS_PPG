
#include "MAXM86161.h"
#include "main.h"
#include "string.h"
#include "stm32f4xx.h"

extern I2C_HandleTypeDef hi2c_ppg_max;

/// Actual configuration
MAXM86161_Init_TypeDef ppg_config;

/**
 * Write MAXM86161 register(s)
 */
bool MAXM86161_I2C_Write(uint8_t regName, uint8_t* regValue, uint8_t numBytes) {
	uint8_t tx_buffer[numBytes + 1];
	uint8_t i;
	tx_buffer[0] = regName;
	for (i = 0; i < numBytes; i++)
		tx_buffer[i + 1] = regValue[i];

	return HAL_I2C_Master_Transmit(&hi2c_ppg_max, MAXM86161_I2C_ADDRESS, tx_buffer,
			numBytes + 1, 100) == HAL_OK;
}

/**
 * Read MAXM86161 register(s)
 */
bool MAXM86161_I2C_Read(uint8_t regName, uint8_t* readByte, uint8_t numBytes) {
	bool res = true;
	res &= (HAL_I2C_Master_Transmit(&hi2c_ppg_max, MAXM86161_I2C_ADDRESS, &regName,
			1, 100) == HAL_OK);
	res &= HAL_I2C_Master_Receive(&hi2c_ppg_max, MAXM86161_I2C_ADDRESS, readByte,
			numBytes, 100) == HAL_OK;
	return res;
}

/**
 * Read sensor part ID
 */
uint8_t MAXM86161_Read_Part_ID(void) {
	uint8_t part_id;
	MAXM86161_I2C_Read(MAXM86161_REG_PART_ID, &part_id, 1);
	return part_id;
}

/**
 * Check part ID, revision ID and whether all registers have been written successfully
 */
bool MAXM86161_Check(void) {
	bool check = true;

	// Read PART_ID to check if they are correct
	if (MAXM86161_Read_Part_ID() != MAXM86161_PART_ID_VALUE)
		check = false;

	// Check mode configuration 1
	//TODO
	return check;
}

/**
 * Configuration of MAXM86161 operation
 */
bool MAXM86161_Config(MAXM86161_Init_TypeDef initStruct){
	bool result = true;
	uint8_t temp;

	temp = 0x01; //Soft Reset
	result &= MAXM86161_I2C_Write(MAXM86161_SYSTEM_CONTROL, &temp, 1);
	HAL_Delay(1);

	temp = initStruct.shutdown | initStruct.low_power;
	result &= MAXM86161_I2C_Write(MAXM86161_SYSTEM_CONTROL, &temp, 1);

	temp = initStruct.integration_time | initStruct.full_scale;
	result &= MAXM86161_I2C_Write(MAXM86161_PPG_CONFIGURATION_1, &temp, 1);

	temp = initStruct.sample_avg | initStruct.frequency;
	result &= MAXM86161_I2C_Write(MAXM86161_PPG_CONFIGURATION_2, &temp, 1);

	temp = initStruct.led1_range | initStruct.led2_range | initStruct.led3_range;
	result &= MAXM86161_I2C_Write(MAXM86161_LED_RANGE_1, &temp, 1);

	result &= MAXM86161_I2C_Write(MAXM86161_LED1_PA, &initStruct.pa[0], 1);
	result &= MAXM86161_I2C_Write(MAXM86161_LED2_PA, &initStruct.pa[1], 1);
	result &= MAXM86161_I2C_Write(MAXM86161_LED3_PA, &initStruct.pa[2], 1);

	temp = 0x21;
	result &= MAXM86161_I2C_Write(MAXM86161_LED_SEQUENCE_REGISTER_1, &temp, 1);
	temp = 0x03;
	result &= MAXM86161_I2C_Write(MAXM86161_LED_SEQUENCE_REGISTER_2, &temp, 1);

	temp = initStruct.fifo_rollover;
	result &= MAXM86161_I2C_Write(MAXM86161_REG_FIFO_CONF_2, &temp, 1);


	return result;
}

/**
 * Raw data readout
 */
bool MAXM86161_ReadData(uint8_t* raw_data_green, uint8_t* raw_data_ir, uint8_t* raw_data_red) {
	bool result = true;
	uint8_t temp[9];

	__disable_irq();
	result &= MAXM86161_I2C_Read(MAXM86161_REG_FIFO_DATA, temp, 9);
	__enable_irq();



	for(int i = 0; i < 9; i += 3){
		switch(temp[i] & 0xF8){
		case 0x08:
			raw_data_green[0] = temp[i] & 0x07;
			raw_data_green[1] = temp[i + 1];
			raw_data_green[2] = temp[i + 2];
			break;
		case 0x10:
			raw_data_ir[0] = temp[i] & 0x07;
			raw_data_ir[1] = temp[i + 1];
			raw_data_ir[2] = temp[i + 2];
			break;
		case 0x18:
			raw_data_red[0] = temp[i] & 0x07;
			raw_data_red[1] = temp[i + 1];
			raw_data_red[2] = temp[i + 2];
			break;
		}
	}
	return result;
}

/**
 * Read data when the module is configured in flex mode
 */
bool MAXM86161_Read_Sample_Flex_Mode(uint8_t* raw_red, uint8_t* raw_ired, uint8_t* raw_green, uint8_t* raw_blue) {

	return true;
}

/**
 * Clear Fifo registers
 */
bool MAXM86161_Clear_Fifo(void) {
	return true;
}
