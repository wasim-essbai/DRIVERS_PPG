
#include "MAX86916.h"
#include "main.h"
#include "string.h"
#include "stm32f4xx.h"

extern I2C_HandleTypeDef hi2c_ppg_max;

/// Actual configuration
MAX86916_Init_TypeDef ppg_config;

/**
 * Write MAX86916 register(s)
 */
bool MAX86916_I2C_Write(uint8_t regName, uint8_t* regValue, uint8_t numBytes) {
	uint8_t tx_buffer[numBytes + 1];
	uint8_t i;
	tx_buffer[0] = regName;
	for (i = 0; i < numBytes; i++)
		tx_buffer[i + 1] = regValue[i];

	return HAL_I2C_Master_Transmit(&hi2c_ppg_max, MAX86916_I2C_ADDRESS, tx_buffer,
			numBytes + 1, 100) == HAL_OK;
}

/**
 * Read MAX86916 register(s)
 */
bool MAX86916_I2C_Read(uint8_t regName, uint8_t* readByte, uint8_t numBytes) {
	bool res = true;
	res &= (HAL_I2C_Master_Transmit(&hi2c_ppg_max, MAX86916_I2C_ADDRESS, &regName,
			1, 100) == HAL_OK);
	res &= HAL_I2C_Master_Receive(&hi2c_ppg_max, MAX86916_I2C_ADDRESS, readByte,
			numBytes, 100) == HAL_OK;
	return res;
}

/**
 * Read sensor part ID
 */
uint8_t MAX86916_Read_Part_ID(void) {
	uint8_t part_id;
	MAX86916_I2C_Read(MAX86916_REG_PART_ID, &part_id, 1);
	return part_id;
}

/**
 * Read revision ID
 */
uint8_t MAX86916_Read_Revision_ID(void) {
	uint8_t rev_id;
	MAX86916_I2C_Read(MAX86916_REG_REVISION_ID, &rev_id, 1);
	return rev_id;
}

/**
 * Check part ID, revision ID and whether all registers have been written successfully
 */
bool MAX86916_Check(void) {
	bool check = true;

	uint8_t reg_value, temp;

	// Read REV_ID e PART_ID to check if they are correct
	if (MAX86916_Read_Part_ID() != MAX86916_PART_ID_VALUE)
		check = false;

	// Check mode configuration 1
	check &= MAX86916_I2C_Read(MAX86916_REG_MODE_CONFIGURATION1, &reg_value, 1);
	temp = ppg_config.shutdown | ppg_config.mode;
	if (reg_value != temp)
		check = false;

	// Check mode configuration 2
	check &= MAX86916_I2C_Read(MAX86916_REG_MODE_CONFIGURATION2, &reg_value, 1);
	temp = ppg_config.full_scale | ppg_config.frequency
			| ppg_config.pulse_width;
	if (reg_value != temp)
		check = false;

	// Check led pulse amplitudes
	check &= MAX86916_I2C_Read(MAX86916_REG_LED1_PULSE_AMPLITUDE, &reg_value, 1);
	temp = ppg_config.led_pa[0];
	if (reg_value != temp)
		check = false;

	check &= MAX86916_I2C_Read(MAX86916_REG_LED2_PULSE_AMPLITUDE, &reg_value,1);
	temp = ppg_config.led_pa[1];
	if (reg_value != temp)
		check = false;

	if (ppg_config.mode == MAX86916_MODE_FLEX) {
		check &= MAX86916_I2C_Read(MAX86916_REG_LED3_PULSE_AMPLITUDE, &reg_value, 1);
		temp = ppg_config.led_pa[2];
		if (reg_value != temp)
			check = false;
		
		check &= MAX86916_I2C_Read(MAX86916_REG_LED4_PULSE_AMPLITUDE, &reg_value, 1);
		temp = ppg_config.led_pa[3];
		if (reg_value != temp)
			check = false;
	}

	return check;
}
/**
 * Configuration of MAX86916 operation
 */
bool MAX86916_Config(MAX86916_Init_TypeDef initStruct) {
	uint8_t temp;
	uint8_t fifo_config = 0x06;
	uint8_t led_seq1 = 0x21;
	uint8_t led_rge = 0x55;
	
	bool result = true;

	//Store configuration parameters
	memcpy((uint8_t*) &ppg_config, (uint8_t*) &initStruct, sizeof(MAX86916_Init_TypeDef));

	// 1. MODE CONFIGURATION 1
	temp = initStruct.shutdown | initStruct.mode;
	//uint8_t prova = 0;
	result &= MAX86916_I2C_Write(MAX86916_REG_MODE_CONFIGURATION1, &temp, 1);

	// 2. MODE CONFIGURATION 2
	temp = initStruct.full_scale | initStruct.frequency | initStruct.pulse_width;
	result &= MAX86916_I2C_Write(MAX86916_REG_MODE_CONFIGURATION2, &temp, 1);

	/*Configurazioni proibite da verificare*/
	// Forbidden configuration HR mode
	if (initStruct.mode == MAX86916_MODE_HR) {
		if (initStruct.frequency > MAX86916_SR_400Hz && initStruct.pulse_width == MAX86916_PW_420)
			initStruct.frequency = MAX86916_SR_400Hz;
		if (initStruct.frequency > MAX86916_SR_1000Hz && initStruct.pulse_width == MAX86916_PW_220)
			initStruct.frequency = MAX86916_SR_1000Hz;
		if (initStruct.frequency > MAX86916_SR_1600Hz && initStruct.pulse_width == MAX86916_PW_120)
			initStruct.frequency = MAX86916_SR_1600Hz;
	}

	// Forbidden configuration SPO2 mode
	if (initStruct.mode == MAX86916_MODE_SPO2) {
		if (initStruct.frequency > MAX86916_SR_200Hz && initStruct.pulse_width == MAX86916_PW_420)
			initStruct.frequency = MAX86916_SR_200Hz;
		if (initStruct.frequency > MAX86916_SR_400Hz && initStruct.pulse_width == MAX86916_PW_220)
			initStruct.frequency = MAX86916_SR_400Hz;
		if (initStruct.frequency > MAX86916_SR_1000Hz && initStruct.pulse_width == MAX86916_PW_120)
			initStruct.frequency = MAX86916_SR_1000Hz;
		if (initStruct.frequency > MAX86916_SR_1600Hz && initStruct.pulse_width == MAX86916_PW_70)
			initStruct.frequency = MAX86916_SR_1600Hz;
	}

	// Forbidden configuration Flex mode
	if (initStruct.mode == MAX86916_MODE_FLEX) {
			if (initStruct.frequency > MAX86916_SR_100Hz && initStruct.pulse_width == MAX86916_PW_420)
				initStruct.frequency = MAX86916_SR_100Hz;
			if (initStruct.frequency > MAX86916_SR_200Hz && initStruct.pulse_width == MAX86916_PW_220)
				initStruct.frequency = MAX86916_SR_200Hz;
			if (initStruct.frequency > MAX86916_SR_400Hz && initStruct.pulse_width == MAX86916_PW_120)
				initStruct.frequency = MAX86916_SR_400Hz;
			if (initStruct.frequency > MAX86916_SR_800Hz && initStruct.pulse_width == MAX86916_PW_70)
				initStruct.frequency = MAX86916_SR_800Hz;
	}

	// 3. LED PULSE AMPLITUDE
	result &= MAX86916_I2C_Write(MAX86916_REG_LED1_PULSE_AMPLITUDE, initStruct.led_pa, 2);
	result &= MAX86916_I2C_Write(MAX86916_REG_LED_SEQUENCE1, &led_seq1, 1);
	result &= MAX86916_I2C_Write(MAX86916_REG_LED_RANGE, &led_rge, 1);

	// Configure LED3 and LED4 amplitude and Flex-Mode control registers if FLEX_MODE is enabled
	if (initStruct.mode == MAX86916_MODE_FLEX) {
		temp = 0x43;
		result &= MAX86916_I2C_Write(MAX86916_REG_LED_SEQUENCE2, &temp, 1);
		result &= MAX86916_I2C_Write(MAX86916_REG_LED3_PULSE_AMPLITUDE, initStruct.led_pa + 2, 2);
	}

	// 4. FIFO CONFIGURATION
	if (initStruct.fifo_a_full > 15) {
		initStruct.fifo_a_full = 15;
	}
	temp = initStruct.fifo_avg | initStruct.fifo_rollover | initStruct.fifo_a_full;
	result &= MAX86916_I2C_Write(MAX86916_REG_FIFO_CONFIGURATION, &fifo_config, 1);

	// 5. CLEAR FIFO
	MAX86916_Clear_Fifo();

	// SAVE SETTINGS
	ppg_config.mode = ppg_config.mode;
	ppg_config.shutdown = initStruct.shutdown;
	ppg_config.full_scale = initStruct.full_scale;
	ppg_config.frequency = initStruct.frequency;
	ppg_config.pulse_width = initStruct.pulse_width;
	uint8_t i;
	for (i = 0; i < 4; i++) {
		ppg_config.led_pa[i] = initStruct.led_pa[i];
	}

	// Check if registers have been written
	bool flag = MAX86916_Check();
	if (flag == false)
		return false;

	return true;
}

/**
 * Raw data readout
 */
bool MAX86916_ReadData(uint8_t* raw_data, uint8_t* len) {
	uint8_t i;
	bool result = true;
	switch (ppg_config.mode) {
	case MAX86916_MODE_SPO2:
		*len = 6;
		break;
	case MAX86916_MODE_FLEX:
		*len = 12;
		break;
	default:
		*len = 3;
		break;
	}
	result &= MAX86916_I2C_Read(MAX86916_REG_FIFO_DATA, raw_data, *len);
	for (i = 0; i < *len / 3; i++) {
		raw_data[i * 3 + 2] &= 0x07;
	}
	return result;
}

/**
 * Read data when the module is configured in HR mode
 */
bool MAX86916_Read_Sample_Hr_Mode(uint8_t* raw_red) {
	uint8_t temp[3];
	bool result = true;
	result &= MAX86916_I2C_Read(MAX86916_REG_FIFO_DATA, temp, 3);
	raw_red[0] = temp[0] & 0x07;
	raw_red[1] = temp[1];
	raw_red[2] = temp[2];
	
	return result;
}

/**
 * Read data when the module is configured in SpO2 mode
 */
bool MAX86916_Read_Sample_Spo2_Mode(uint8_t* raw_red, uint8_t* raw_ired) {
	uint8_t temp[6];
	bool result = true;
	result &= MAX86916_I2C_Read(MAX86916_REG_FIFO_DATA, temp, 6);
	raw_red[0] = temp[0] & 0x07;
	raw_red[1] = temp[1];
	raw_red[2] = temp[2];
	raw_ired[0] = temp[3] & 0x07;
	raw_ired[1] = temp[4];
	raw_ired[2] = temp[5];

	return result;
}

/**
 * Read data when the module is configured in flex mode
 */

bool MAX86916_Read_Sample_Flex_Mode(uint8_t* raw_ired, uint8_t* raw_red, uint8_t* raw_green, uint8_t* raw_blue) {
	uint8_t temp[12];
	bool result = true;
	__disable_irq();
	result &= MAX86916_I2C_Read(MAX86916_REG_FIFO_DATA, temp, 12);
	__enable_irq();
	raw_ired[0] = temp[0] & 0x07;
	raw_ired[1] = temp[1];
	raw_ired[2] = temp[2];
	raw_red[0] = temp[3] & 0x07;
	raw_red[1] = temp[4];
	raw_red[2] = temp[5];
	raw_green[0] = temp[6] & 0x07;
	raw_green[1] = temp[7];
	raw_green[2] = temp[8];
	raw_blue[0] = temp[9] & 0x07;
	raw_blue[1] = temp[10];
	raw_blue[2] = temp[11];

	return result;
}

/**
 * Convert a PPG sample
 */
uint32_t MAX86916_ConvertSample(uint8_t* raw_data) {
	uint32_t value;
	value = ((((uint32_t) raw_data[0]) << 16) & 0xFF0000)
			| ((((uint32_t) raw_data[1]) << 8) & 0x00FF00)
			| (((uint32_t) raw_data[2]) & 0x0000FF);
	value &= 0x03FFFF;
	return value;
}

/**
 * Clear the interrupts
 */
bool MAX86916_Clear_Interrupts(void) {
	uint8_t temp;
	bool result = true;
	result &= MAX86916_I2C_Read(MAX86916_REG_INTERRUPT_STATUS1, &temp, 1);
	return result;
}

/**
 * Sensor power-down function
 */
bool MAX86916_Power_Down(bool flag) {
	uint8_t temp;
	bool result = true;
	result &= MAX86916_I2C_Read(MAX86916_REG_MODE_CONFIGURATION1, &temp, 1);

	if ((temp & MAX86916_SHDNMODE_SHUTDOWN) == MAX86916_SHDNMODE_SHUTDOWN) {
		if (!flag) {
			temp = temp & 0x7F;
			result &= MAX86916_I2C_Write(MAX86916_REG_MODE_CONFIGURATION1, &temp, 1);
		}
	} else {
		if (flag) {
			temp = temp | MAX86916_SHDNMODE_SHUTDOWN;
			result &= MAX86916_I2C_Write(MAX86916_REG_MODE_CONFIGURATION1, &temp, 1);
		}
	}
	return result;
}

/**
 * Software reset of MAX86916
 */
bool MAX86916_Reset(void) {
	uint8_t temp;
	bool result = true;
	result &= MAX86916_I2C_Read(MAX86916_REG_MODE_CONFIGURATION1, &temp, 1);
	temp = temp | MAX86916_RSTMODE_RESET_ON;
	result &= MAX86916_I2C_Write(MAX86916_REG_MODE_CONFIGURATION1, &temp, 1);
	return result;
}


/**
 * Enable/Disable interrupts
 */
bool MAX86916_Set_Interrupt(uint8_t arg) {
	uint8_t temp;
	bool result = true;
	temp = arg & 0xF0; // Mask for interrupt enable 1
	result &= MAX86916_I2C_Write(MAX86916_REG_INTERRUPT_ENABLE1, &temp, 1);
	result &= MAX86916_Clear_Fifo();
	result &= MAX86916_Clear_Interrupts();
	return result;
}

/**
 * Read interrupt 1
 */
uint8_t MAX86916_Get_Interrupt(void) {
	uint8_t temp;
	MAX86916_I2C_Read(MAX86916_REG_INTERRUPT_STATUS1, &temp, 1);
	return temp;
}

/**
 * Clear Fifo registers
 */
bool MAX86916_Clear_Fifo(void) {
	uint8_t reset = 0x00;
	bool result = true;
	result &= MAX86916_I2C_Write(MAX86916_REG_FIFO_WRITE_PTR, &reset, 1);
	result &= MAX86916_I2C_Write(MAX86916_REG_FIFO_OVERFLOW_COUNTER, &reset, 1);
	result &= MAX86916_I2C_Write(MAX86916_REG_FIFO_READ_PTR, &reset, 1);
	return result;
}

/**
 * Shortcut to initialize the sensor in SpO2 mode
 */
bool MAX86916_Init_SPO2(uint8_t* led_pulse_amplitude) {
	MAX86916_Init_TypeDef ppg_init;
	ppg_init.mode = MAX86916_MODE_SPO2;
	ppg_init.shutdown = MAX86916_SHDNMODE_SHUTDOWN; // partiamo in power down mode.
	ppg_init.full_scale = MAX86916_FS_8192;
	ppg_init.frequency = MAX86916_SR_400Hz;
	ppg_init.pulse_width = MAX86916_PW_420;
	ppg_init.fifo_a_full = 0x06;
	ppg_init.fifo_rollover = MAX86916_FIFO_ROLLOVER_OFF;
	ppg_init.fifo_avg = MAX86916_FIFO_AVG_2;

	uint8_t i;
	for (i = 0; i < 2; i++) {
		ppg_init.led_pa[i] = led_pulse_amplitude[i];
	}

	return MAX86916_Config(ppg_init);
}

/**
 * Shortcut to initialize the sensor in Multiled mode
 */
bool MAX86916_Init_Multiled(uint8_t* led_pulse_amplitude) {
	MAX86916_Init_TypeDef ppg_init;
	ppg_init.mode = MAX86916_MODE_FLEX;
	ppg_init.shutdown = MAX86916_SHDNMODE_SHUTDOWN;
	ppg_init.full_scale = MAX86916_FS_8192;
	ppg_init.frequency = MAX86916_SR_100Hz;
	ppg_init.pulse_width = MAX86916_PW_420;
	ppg_init.fifo_a_full = 0x06;
	ppg_init.fifo_rollover = MAX86916_FIFO_ROLLOVER_OFF;
	ppg_init.fifo_avg = MAX86916_FIFO_AVG_1;

	uint8_t i;
	for (i = 0; i < 4; i++) {
		ppg_init.led_pa[i] = led_pulse_amplitude[i];
	}
	return MAX86916_Config(ppg_init);
}
