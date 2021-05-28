
#define MAX86916_H_

#include "stdint.h"
#include <stdbool.h>

#define MAX86916

/// Set I2C properly
#define hi2c_ppg_max hi2c3

/// MAX30310x I2C ADDRESS
#define	MAX86916_I2C_ADDRESS					0xAE

/// MAX86916 REGISTER MAP
/// Status registers
#define MAX86916_REG_INTERRUPT_STATUS1			0x00
#define MAX86916_REG_INTERRUPT_ENABLE1			0x02

/// FIFO registers
#define MAX86916_REG_FIFO_WRITE_PTR			0x04
#define MAX86916_REG_FIFO_OVERFLOW_COUNTER		0x05
#define MAX86916_REG_FIFO_READ_PTR				0x06
#define MAX86916_REG_FIFO_DATA					0x07

/// Configuration registers
#define MAX86916_REG_FIFO_CONFIGURATION			0x08
#define MAX86916_REG_MODE_CONFIGURATION1		0x09
#define MAX86916_REG_MODE_CONFIGURATION2		0x0A

/// Led pulse amplitude
#define MAX86916_REG_LED1_PULSE_AMPLITUDE		0x0C /// IRED
#define MAX86916_REG_LED2_PULSE_AMPLITUDE		0x0D /// RED
#define MAX86916_REG_LED3_PULSE_AMPLITUDE		0x0E /// GREEN
#define MAX86916_REG_LED4_PULSE_AMPLITUDE		0x0F /// BLUE
#define MAX86916_REG_LED_RANGE					0x11
#define MAX86916_REG_PILOT_PA					0x12

/// Led sequence control
#define MAX86916_REG_LED_SEQUENCE1				0x13
#define MAX86916_REG_LED_SEQUENCE2				0x14

/// Proximity mode
#define MAX86916_REG_PROX_INTERRUPT_THRESH		0x30

/// Part ID
#define MAX86916_REG_REVISION_ID				0xFE
#define MAX86916_REG_PART_ID					0xFF

/*##########################
 * MODE CONFIGURATION1 [0x09] -> MAX86916_MODE_CFG
 * Bit 7: Shutdown control
 * Bit 6: Reset control
 * Bits 1:0: Mode control
 *########################## */

typedef enum {
	MAX86916_MODE_HR = 0x01, MAX86916_MODE_SPO2 = 0x02
	, MAX86916_MODE_FLEX = 0x03
} MAX86916_Mode;

typedef enum {
	MAX86916_SHDNMODE_SHUTDOWN = 0x80, MAX86916_SHDNMODE_ON = 0x00
} MAX86916_ShutdownMode;

typedef enum {
	MAX86916_RSTMODE_RESET_ON = 0x40, MAX86916_RSTMODE_NO_RESET = 0x00
} MAX86916_ResetMode;

/*##########################
 * MODE CONFIGURATION2 [0x0A] -> MAX86916_SPO2_CFG
 * Bits 6:5: ADC Range Control
 * Bits 4:2: Sample Rate Control
 * Bits 1:0: LED Pulse Width Control
 *########################## */

typedef enum {
	MAX86916_FS_4096 = 0x00,
	MAX86916_FS_8192 = 0x20,
	MAX86916_FS_16384 = 0x40,
	MAX86916_FS_32768 = 0x60
} MAX86916_FullScale;

// MODE CONFIGURATION2: SAMPLE RATE
// SS = samples per second
typedef enum {
	MAX86916_SR_50Hz = 0x00,
	MAX86916_SR_100Hz = 0x04,
	MAX86916_SR_200Hz = 0x08,
	MAX86916_SR_400Hz = 0x0C,
	MAX86916_SR_800Hz = 0x10,
	MAX86916_SR_1000Hz = 0x14,
	MAX86916_SR_1600Hz = 0x18,
	MAX86916_SR_3200Hz = 0x1C
} MAX86916_SampleRate;

// MODE CONFIGURATION2: LED PULSE WIDTH CONTROL
// PW = pulse width (us)
// Resolution 19 bits
typedef enum {
	MAX86916_PW_70 = 0x00,		
	MAX86916_PW_120 = 0x01, 		
	MAX86916_PW_220 = 0x02,		
	MAX86916_PW_420 = 0x03		
} MAX86916_LedPulseWidth;

/*##########################
 * FIFO CONFIGURATION [0x08] -> MAX86916_FIFO_CFG
 * Bits 7:5: Sample Averaging
 * Bit 4: FIFO Rolls on Full
 * Bits 3:0: FIFO Almost Full Value
 *########################## */

// Sample averaging --> FIFO CONFIGURATION
typedef enum {
	MAX86916_FIFO_AVG_1 = 0x00,	// no average
	MAX86916_FIFO_AVG_2 = 0x20,	// average on 2 samples
	MAX86916_FIFO_AVG_4 = 0x40,
	MAX86916_FIFO_AVG_8 = 0x60,
	MAX86916_FIFO_AVG_16 = 0x80,
	MAX86916_FIFO_AVG_32 = 0xE0
} MAX86916_Sample_Avg;

typedef enum {
	MAX86916_FIFO_ROLLOVER_ON = 0x10, MAX86916_FIFO_ROLLOVER_OFF = 0x00
} MAX86916_FifoRollover;

// MAX86916 initialization structure
typedef struct {
	MAX86916_Mode mode;
	MAX86916_ShutdownMode shutdown;
	MAX86916_FullScale full_scale;
	MAX86916_SampleRate frequency;
	MAX86916_LedPulseWidth pulse_width;
	MAX86916_Sample_Avg fifo_avg;
	MAX86916_FifoRollover fifo_rollover;
	uint8_t fifo_a_full;
	uint8_t led_pa[4];
} MAX86916_Init_TypeDef;

/// Interrupts status
#define MAX86916_IT_A_FULL			0x80
#define MAX86916_IT_SMP_RDY			0x40
#define MAX86916_IT_ALC_OVF			0x20
#define MAX86916_IT_PROX_INT		0x10
#define MAX86916_IT_PWR_RDY			0x01

/// Interrupts enabled
#define MAX86916_IT_A_FULL_EN		0x80
#define MAX86916_IT_SMP_RDY_EN		0x40
#define MAX86916_IT_ALC_OVF_EN		0x20
#define MAX86916_IT_PROX_INT_EN		0x10

/// I2C communication functions
/**
 * Write MAX86916 register(s)
 * @param regName Register address
 * @param regValue Value(s) to be written
 * @param numBytes Number of bytes to be read
 * @return True if successful, false otherwise
 */
bool MAX86916_I2C_Write(uint8_t regName, uint8_t* regValue, uint8_t numBytes);

/**
 * Read MAX86916 register(s)
 * @param regName Register address
 * @param readByte Read value(s)
 * @param numBytes Number of bytes to be read
 * @return True if successful, false otherwise
 */
bool MAX86916_I2C_Read(uint8_t regName, uint8_t* readByte, uint8_t numBytes);

/// CHECK FUNCTIONS
/**
 * Read sensor part ID
 * @return	Part ID (MAX86916_PART_ID_VALUE = 0x15)
 */
uint8_t MAX86916_Read_Part_ID(void);

/**
 * Read revision ID
 * @return	Revision ID (MAX86916_REVISION_ID_VALUE = 0x06)
 */
uint8_t MAX86916_Read_Revision_ID(void);

/**
 * Check part ID, revision ID and whether all registers have been written successfully
 * @return	true if the sensor has been configured correctly, false otherwise
 */
bool MAX86916_Check(void);

/// CONFIG FUNCTIONS
/**
 * Configuration of MAX86916 operation
 * @param initStruct Initialization structure
 * @return True if successful, false otherwise
 */
bool MAX86916_Config(MAX86916_Init_TypeDef initStruct);

/// READOUT FUNCTIONS
/**
 * Raw data readout
 * @param raw_data Raw data (3 Bytes red + 3 Bytes IR + 3 Bytes green)
 * @param len Raw data length
 * @return True if successful, false otherwise
 * @details Data length depends on the operating mode: HR 3 Bytes, SpO2 6 Bytes, Multiled 9 Bytes
 */
bool MAX86916_ReadData(uint8_t* raw_data, uint8_t* len);

/**
 * Read data when the module is configured in HR mode
 * @param raw_red Red led raw data
 * @return True if successful, false otherwise
 */
bool MAX86916_Read_Sample_Hr_Mode(uint8_t* raw_red);

/**
 * Read data when the module is configured in SpO2 mode
 * @param raw_red Red led raw data
 * @param raw_ired IR led raw data
 * @return True if successful, false otherwise
 */
bool MAX86916_Read_Sample_Spo2_Mode(uint8_t* raw_red, uint8_t* raw_ired);

/**
 * Read data when the module is configured in Multiled mode
 * @param raw_red Red led raw data
 * @param raw_ired IR led raw data
 * @param raw_green Green led raw data
 * @return True if successful, false otherwise
 */
bool MAX86916_Read_Sample_Flex_Mode(uint8_t* raw_red, uint8_t* raw_ired, uint8_t* raw_green, uint8_t* raw_blue);

/**
 * Convert a PPG sample
 * @param raw_data Raw data (array of three uint8_t)
 * @return Converted value
 */
uint32_t MAX86916_ConvertSample(uint8_t* raw_data);

/// OTHER FUNCTIONS
/**
 * Clear the interrupts
 * @return True if successful, false otherwise
 */
bool MAX86916_Clear_Interrupts(void);

/**
 * Sensor power-down function
 * @param flag true (power-down), false (power-up)
 * @return True if successful, false otherwise
 */
bool MAX86916_Power_Down(bool flag);

/**
 * Software reset of MAX86916
 * @return True if successful, false otherwise
 */
bool MAX86916_Reset(void);

/**
 * Enable/Disable interrupts
 * @param arg See MAX86916_IT_ constants
 * @return True if successful, false otherwise
 */
bool MAX86916_Set_Interrupt(uint8_t arg);

/**
 * Read interrupt 1
 * @return Interrupt status 1 register content
 */
uint8_t MAX86916_Get_Interrupt1(void);

/**
 * Read interrupt 2
 * @return Interrupt status 1 register content
 */
uint8_t MAX86916_Get_Interrupt2(void);

/**
 * Clear Fifo registers
 * @return True if successful, false otherwise
 */
bool MAX86916_Clear_Fifo(void);

/**
 * Shortcut to initialize the sensor in SpO2 mode
 * @param led_pulse_amplitude Array of 2 elements describing the led amplitudes (red, IR)
 * @return True if successful, false otherwise
 * @details 0.2 mA/LSB
 */
bool MAX86916_Init_SPO2(uint8_t* led_pulse_amplitude);

/**
 * Shortcut to initialize the sensor in Multiled mode
 * @param led_pulse_amplitude Array of 3 elements describing the led amplitudes (red, IR, green)
 * @return True if successful, false otherwise
 * @details 0.2 mA/LSB
 */
bool MAX86916_Init_Multiled(uint8_t* led_pulse_amplitude);
