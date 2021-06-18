#include "stdint.h"
#include <stdbool.h>

/// Define this only if you are using MAX30101 IC
#define MAXM86161

/// Set I2C properly
#define hi2c_ppg_max hi2c3 //TODO

/// MAX30310x I2C ADDRESS
#define	MAXM86161_I2C_ADDRESS					0xC4

/// MAX30101/MAX30102 REGISTER MAP
/// Status registers
#define MAXM86161_REG_INTERRUPT_ENABLE1			0x02

/// System Control
#define MAXM86161_SYSTEM_CONTROL				0X0D

/// PPG Configuration
#define MAXM86161_PPG_CONFIGURATION_1			0X11
#define MAXM86161_PPG_CONFIGURATION_2			0X12
#define MAXM86161_PPG_CONFIGURATION_3			0X13

/// Led Sequence Control
#define MAXM86161_LED_SEQUENCE_REGISTER_1		0X20
#define MAXM86161_LED_SEQUENCE_REGISTER_2		0X21
#define MAXM86161_LED_SEQUENCE_REGISTER_3		0X22

/// Led Pulse Amplitude
#define MAXM86161_LED1_PA						0X23 //GREEN
#define MAXM86161_LED2_PA						0X24 //IR
#define MAXM86161_LED3_PA						0X25 //RED
#define MAXM86161_LED_RANGE_1					0X2A

/// Part ID
#define MAXM86161_REG_PART_ID					0xFF

/// Constants
#define MAXM86161_PART_ID_VALUE					0x36

/*##########################
 * SYSTEM CONTROL [0x0D]
 * Bit 1: Shutdown control
 * Bits 0: Reset control
 *########################## */

typedef enum {
	MAXM86161_SHDNMODE_SHUTDOWN = 0x02, MAXM86161_SHDNMODE_ON = 0x00
} MAXM86161_ShutdownMode;

typedef enum {
	MAXM86161_RSTMODE_RESET_ON = 0x01, MAX3010x_RSTMODE_NO_RESET = 0x00
} MAXM86161_ResetMode;

/*##########################
 * PPG CONFIGURATION [0x11]
 * Bits 7: ALC Disable
 * Bits 2:3: ADC Range Control
 * Bits 0:1: Integration time of ADC
 *########################## */

typedef enum {
	MAXM86161_FS_4096 = 0x00,
	MAXM86161_FS_8192 = 0x04,
	MAXM86161_FS_16384 = 0x08,
	MAXM86161_FS_37628 = 0x0C
} MAXM86161_FullScale;

// Integration time of ADC [us]
typedef enum {
	MAXM86161_FS_4096 = 0x00,
	MAXM86161_FS_8192 = 0x04,
	MAXM86161_FS_16384 = 0x08,
	MAXM86161_FS_37628 = 0x0C
} MAXM86161_IntegrationTime;

/// Interrupts
#define MAXM86161_DATA_RDY		0x40

/// I2C communication functions
/**
 * Write MAX3010x register(s)
 * @param regName Register address
 * @param regValue Value(s) to be written
 * @param numBytes Number of bytes to be read
 * @return True if successful, false otherwise
 */
bool MAX3010x_I2C_Write(uint8_t regName, uint8_t* regValue, uint8_t numBytes);

/**
 * Read MAX3010x register(s)
 * @param regName Register address
 * @param readByte Read value(s)
 * @param numBytes Number of bytes to be read
 * @return True if successful, false otherwise
 */
bool MAX3010x_I2C_Read(uint8_t regName, uint8_t* readByte, uint8_t numBytes);

/// CHECK FUNCTIONS
/**
 * Read sensor part ID
 * @return	Part ID (MAX3010x_PART_ID_VALUE = 0x15)
 */
uint8_t MAX3010x_Read_Part_ID(void);

/**
 * Check part ID and whether all registers have been written successfully
 * @return	true if the sensor has been configured correctly, false otherwise
 */
bool MAX3010x_Check(void);
