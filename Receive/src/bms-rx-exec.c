#include "bms-rx-data.h"

#if(TEST_MODE)
int TestCount[NumberOfParameters] = {0};
char strInput[TestSize][100] = {0};

float TestSMAOuputValue[TestSize][NumberOfParameters] = {0.0};
float TestMinOuputValue[TestSize][NumberOfParameters] = {0.0};
float TestMaxOuputValue[TestSize][NumberOfParameters] = {0.0};
#endif


/************************ Function Definitions **************************/
void sighandler(int signum) {
    printf("User stopped reading, i.e, Signum value : %d received", signum);
    isStopRequestedByUser = true;
}

float movingAverageValue(float *ptrArrNumbers, float *ptrSum, int paramID, int range, float nextNum)
{
    static int pos[NumberOfParameters]= {0};
    
    if(range>1)
    {
   
       *ptrSum = *ptrSum - ptrArrNumbers[pos[paramID]] + nextNum;
  
        ptrArrNumbers[pos[paramID]] = nextNum;
        
        pos[paramID]++;
        if (pos[paramID] >= range)
        {
            pos[paramID] = 0;
        }
        
        return *ptrSum / range;
        
    }
    else if (range == 1)
    {
       return nextNum;
        
    }
    else
    {
        return INVALID_SMARANGE;
    }
 
}


bool UpdateTemperature (BatParamsOut_s BatteryParamEvaluated)
{
     /*This function can be adapted in production based on the usage, say to append data to file or Printing as needed*/
    #if(TEST_MODE)
    int i=TestCount[TEMPERATURE];
    TestSMAOuputValue[i][TEMPERATURE] = BatteryParamEvaluated.SMA;
    TestMinOuputValue[i][TEMPERATURE] = BatteryParamEvaluated.minRx;
    TestMaxOuputValue[i][TEMPERATURE] = BatteryParamEvaluated.maxRx;
    TestCount[TEMPERATURE]++;
    if(TestCount[TEMPERATURE] >= TestSize)
    {
        isStopRequestedByUser = true;
    }
    else
    {
        isStopRequestedByUser = false;
    }
    #endif
    if (BatteryParamEvaluated.SMA == INVALID_VALUE)
    {
       printf("No Valid Temperature data received\n");
    }
    else
    {
        printf("Temperature -> SMA : %.2f degrees, Minimum : %.2f degrees , Maximum : %0.2f degrees \n", BatteryParamEvaluated.SMA, BatteryParamEvaluated.minRx, BatteryParamEvaluated.maxRx);
    }
        
    return 1;
}


bool UpdateChargeRate (BatParamsOut_s BatteryParamEvaluated)
{
     /*This function can be adapted in production based on the usage, say to append data to file or Printing as needed*/
    #if(TEST_MODE)
    int i = TestCount[CHARGERATE];
    TestSMAOuputValue[i][CHARGERATE] = BatteryParamEvaluated.SMA;
    TestMinOuputValue[i][CHARGERATE] = BatteryParamEvaluated.minRx;
    TestMaxOuputValue[i][CHARGERATE] = BatteryParamEvaluated.maxRx;
    TestCount[CHARGERATE]++;
    if(TestCount[CHARGERATE] >= TestSize)
    {
        isStopRequestedByUser = true;
    }
    else
    {
        isStopRequestedByUser = false;
    }
    #endif
    
    if (BatteryParamEvaluated.SMA == INVALID_VALUE)
    {
       printf("No Valid Charge Rate data received\n");
    }
    else
    {
        printf("ChargeRate -> SMA : %.2f A , Minimum : %.2f A, Maximum : %0.2f A\n", BatteryParamEvaluated.SMA, BatteryParamEvaluated.minRx, BatteryParamEvaluated.maxRx);
    }
    
    return 1;
}

/****************************************************************************************
*Func desc : The function check if the passed value is within the range passed 
*Param     : value   - The value for which range is to be checked
             min     - The range minimum value 
             max     - The range minimum value 
*Return    : valid status - bool type 
             If 1 : Within Range,else out of range or Invalid range
*****************************************************************************************/

bool IsWithinRange(float value, float min, float max)
{
    if(min<max)
    {
        return ((value>=min)&&(value<=max));
    }
    else
    {
        printf("Minimum value passes is greater than Maximum");
        return 0;
    }
}


float MinimumValue(float num1, float num2)
{
    if (num1 < num2)
    {
        return num1;
    }
    else 
    {
        return num2;
    }
}


float MaximumValue(float num1, float num2)
{
    if (num1 > num2)
    {
        return num1;
    }
    else 
    {
        return num2;
    }
}


