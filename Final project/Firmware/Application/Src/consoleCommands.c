// ConsoleCommands.c
// This is where you add commands:
//		1. Add a protoype
//			static eCommandResult_T ConsoleCommandVer(const char buffer[]);
//		2. Add the command to mConsoleCommandTable
//		    {"ver", &ConsoleCommandVer, HELP("Get the version string")},
//		3. Implement the function, using ConsoleReceiveParam<Type> to get the parameters from the buffer.

#include "string.h"
#include "stdio.h"
#include "consoleCommands.h"
#include "console.h"
#include "consoleIo.h"
#include "version.h"

#include "state_defines.h"

#include "mpu6050.h"

extern I2C_HandleTypeDef hi2c3;

#define IGNORE_UNUSED_VARIABLE(x)     if ( &x == &x ) {}


static eCommandResult_T ConsoleCommandComment(const char buffer[]);
static eCommandResult_T ConsoleCommandVer(const char buffer[]);
static eCommandResult_T ConsoleCommandHelp(const char buffer[]);
static eCommandResult_T ConsoleCommandParamExampleInt16(const char buffer[]);
static eCommandResult_T ConsoleCommandParamExampleHexUint16(const char buffer[]);

static eCommandResult_T ConsoleCommandReadImu(void);
//static eCommandResult_T ConsoleCommandLedPattern(const char buffer[]);

static const sConsoleCommandTable_T mConsoleCommandTable[] =
{
    {";", ConsoleCommandComment, HELP("Comment! You do need a space after the semicolon. ")},
    {"help", ConsoleCommandHelp, HELP("Lists the commands available")},
    {"ver", ConsoleCommandVer, HELP("Get the version string")},
    {"int", ConsoleCommandParamExampleInt16, HELP("How to get a signed int16 from params list: int -321")},
    {"u16h", ConsoleCommandParamExampleHexUint16, HELP("How to get a hex u16 from the params list: u16h aB12")},

	{"readImu", ConsoleCommandReadImu, HELP("Reads the accelerometer, gyro and temperature from the imu")},

	CONSOLE_COMMAND_TABLE_END // must be LAST
};

static eCommandResult_T ConsoleCommandComment(const char buffer[])
{
	// do nothing
	IGNORE_UNUSED_VARIABLE(buffer);
	return COMMAND_SUCCESS;
}

static eCommandResult_T ConsoleCommandHelp(const char buffer[])
{
	uint32_t i;
	uint32_t tableLength;
	eCommandResult_T result = COMMAND_SUCCESS;

    IGNORE_UNUSED_VARIABLE(buffer);

	tableLength = sizeof(mConsoleCommandTable) / sizeof(mConsoleCommandTable[0]);
	for ( i = 0u ; i < tableLength - 1u ; i++ )
	{
		ConsoleIoSendString(mConsoleCommandTable[i].name);
#if CONSOLE_COMMAND_MAX_HELP_LENGTH > 0
		ConsoleIoSendString(" : ");
		ConsoleIoSendString(mConsoleCommandTable[i].help);
#endif // CONSOLE_COMMAND_MAX_HELP_LENGTH > 0
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandParamExampleInt16(const char buffer[])
{
	int16_t parameterInt;
	eCommandResult_T result;
	result = ConsoleReceiveParamInt16(buffer, 1, &parameterInt);
	if ( COMMAND_SUCCESS == result )
	{
		ConsoleIoSendString("Parameter is ");
		ConsoleSendParamInt16(parameterInt);
		ConsoleIoSendString(" (0x");
		ConsoleSendParamHexUint16((uint16_t)parameterInt);
		ConsoleIoSendString(")");
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}
static eCommandResult_T ConsoleCommandParamExampleHexUint16(const char buffer[])
{
	uint16_t parameterUint16;
	eCommandResult_T result;
	result = ConsoleReceiveParamHexUint16(buffer, 1, &parameterUint16);
	if ( COMMAND_SUCCESS == result )
	{
		ConsoleIoSendString("Parameter is 0x");
		ConsoleSendParamHexUint16(parameterUint16);
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandVer(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;

    IGNORE_UNUSED_VARIABLE(buffer);

	ConsoleIoSendString(VERSION_STRING);
	ConsoleIoSendString(FIRMWARE_MAJOR);
	ConsoleIoSendString(FIRMWARE_MINOR);
	ConsoleIoSendString(FIRMWARE_BUILD);
	ConsoleIoSendString(STR_ENDLINE);
	return result;
}

const sConsoleCommandTable_T* ConsoleCommandsGetTable(void)
{
	return (mConsoleCommandTable);
}

static eCommandResult_T ConsoleCommandReadImu(void)
{
	MPU6050_t imuData;
	eCommandResult_T result = COMMAND_SUCCESS;
	char string[300];

	//Read imuData
	MPU6050_Read_All(&hi2c3, &imuData);
	ConsoleIoSendString("IMU Data: ");
	sprintf(string, "ax: %f, ay: %f, az: %f - gx: %f, gy: %f, gz: %f - temp: %f °C", imuData.Ax, imuData.Ay, imuData.Az, imuData.Gx, imuData.Gy, imuData.Gz, imuData.Temperature);
	ConsoleIoSendString(string);
	ConsoleIoSendString(STR_ENDLINE);

	return result;

}


