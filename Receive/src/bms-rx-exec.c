#include "bms-rx-data.h"


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


