/************************ Includes **************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif



/************************ Defines **************************/

#define TEMPERATURE_MIN     20.0
#define TEMPERATURE_MAX     80.0
#define CHARGERATE_MIN 0.0
#define CHARGERATE_MAX 5.0

#define SMA_RANGE 5
#define MAXLENGTH 100

#define VALUE_NOTFOUND 65532
#define INVALID_SMARANGE 65530
#define INVALID_VALUE 65535




/************************ Variables **************************/
enum BmsParameters_e{
    temperature = 0,
    charge_rate,
    NumberOfParameters
};

typedef struct BatteryParameters{
    char ParameterName[20];
    float minValue;
    float maxValue;
}BatParams_s;

typedef struct BatteryParametersOut{
    float SMA;
    float minRx;
    float maxRx;
}BatParamsOut_s;

//extern struct BatteryParam_s BatteryParam[NumberOfParameters];

extern bool isStopRequestedByUser;

#if(TEST_MODE)
#define  TestSize 13
extern float TestSMAOuputValue[TestSize][NumberOfParameters];
extern float TestMaxOuputValue[TestSize][NumberOfParameters];
extern float TestMinOuputValue[TestSize][NumberOfParameters];
extern int TestCount[NumberOfParameters];
extern char strInput[TestSize][100];
#endif


/**************Function prototype section*********************/

void sighandler(int);

float getParameterFromConsole(char *getLine, BmsParameters_e BatParam);

void BMSDataReceiveFromConsole();

typedef bool (*UpdateSMAData)(BatParamsOut_s BatteryParamEvaluated);

bool UpdateTemperature (BatParamsOut_s BatteryParamEvaluated);

bool UpdateChargeRate (BatParamsOut_s BatteryParamEvaluated);

bool IsWithinRange(float value, float min, float max);

float MinimumValue(float num1, float num2);

float MaximumValue(float num1, float num2);

float movingAverageValue(float *ptrArrNumbers, float *ptrSum, int paramID, int range, float nextNum);

int getParamsFromString(char *getterString, int stringSize);
