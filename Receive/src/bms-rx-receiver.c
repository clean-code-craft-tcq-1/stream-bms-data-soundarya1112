#include "bms-rx-data.h"


BatParams_s BatteryData[NumberOfParameters] = {{"\'temperature\'", TEMPERATURE_MIN , TEMPERATURE_MAX},
                                                  {"\'charge_rate\'", CHARGERATE_MIN , CHARGERATE_MAX}};

UpdateSMAData UpdateSMADataParam[NumberOfParameters] = {UpdateTemperature , UpdateChargeRate};


void BMSDataReceiveFromConsole()
{
    int batteryParamIterater;
    int eofReached = 0; 
    int count = 0;

    float BMSParamValueRx[NumberOfParameters] = {0};
    float ReadingsBuffer[NumberOfParameters][SMA_RANGE]= {0};
    float ReadingsSum[NumberOfParameters]={0};
    char str[MAXLENGTH];
    BatParamsOut_s INVALID_VALUE_s = {INVALID_VALUE,INVALID_VALUE,INVALID_VALUE};
   

    BatParamsOut_s BatteryParamEvaluated[NumberOfParameters]= {{0, TEMPERATURE_MIN, TEMPERATURE_MAX},
                                                             {0, CHARGERATE_MIN , CHARGERATE_MAX}};
  
  
    do
    {
        eofReached = getParamsFromString(str, MAXLENGTH);
        for (batteryParamIterater=0 ; batteryParamIterater < NumberOfParameters; batteryParamIterater++)
        {
            BMSParamValueRx[batteryParamIterater] = getParameterFromConsole(str,(BmsParameters_e)batteryParamIterater);
            
            if(IsWithinRange(BMSParamValueRx[batteryParamIterater], BatteryData[batteryParamIterater].minValue , BatteryData[batteryParamIterater].maxValue))
            {
                BatteryParamEvaluated[batteryParamIterater].SMA =  movingAverageValue((ReadingsBuffer[batteryParamIterater]), (ReadingsSum+batteryParamIterater), batteryParamIterater, SMA_RANGE, BMSParamValueRx[batteryParamIterater]);
                
                BatteryParamEvaluated[batteryParamIterater].minRx = MinimumValue(BMSParamValueRx[batteryParamIterater],BatteryParamEvaluated[batteryParamIterater].minRx);
                
                BatteryParamEvaluated[batteryParamIterater].maxRx = MaximumValue(BMSParamValueRx[batteryParamIterater],BatteryParamEvaluated[batteryParamIterater].maxRx);
                
                UpdateSMADataParam[batteryParamIterater](BatteryParamEvaluated[batteryParamIterater]);
                
            }
            else
            {
               UpdateSMADataParam[batteryParamIterater](INVALID_VALUE_s);
            } 
           count++;
        }
    //}while((!isStopRequestedByUser) || (eofReached != 1)); 
    }while((!isStopRequestedByUser) || (eofReached != 1) || (count=100)); // to avoid running infinitely
}


float getParameterFromConsole(char *getLine, BmsParameters_e BatParam)
{
  char splitStrCategory[NumberOfParameters*3][500]={'\0'};
  char splitStrParams[NumberOfParameters*3][500]={'\0'};
  char *tokenCategory;
  char *tokenParams;  
  int k=0, p =0;
  float temp = VALUE_NOTFOUND;
  char buffer[MAXLENGTH];
  getLine++[strlen(getLine)-1] = 0;
  
  strcpy(buffer,getLine);
  tokenCategory = strtok (buffer,",");
  
  while (tokenCategory != NULL)
  {
    strcpy((splitStrCategory[k]),tokenCategory);
    k++;
    tokenCategory = strtok (NULL, ",");
  }

  for(int r = 0; r < NumberOfParameters; r++)
  {
    tokenParams = strtok ((splitStrCategory[r]), ":");
    
    while(tokenParams != NULL)
    {
        strcpy((splitStrParams[p]), tokenParams);
        p++;
        tokenParams = strtok (NULL, ":");
    }
  }
  
  for(int j=0;j < (NumberOfParameters*3);j=j+2)
  {
      if(strcmp((splitStrParams[j]), BatteryData[BatParam].ParameterName) == 0)
      {
         temp = atof(splitStrParams[j+1]);
         break;
      }
      else
      {
          temp = VALUE_NOTFOUND;
      }
  }

  tokenCategory = NULL;
  tokenParams = NULL;

  return temp; 
}

int getParamsFromString(char *getterString, int stringSize)
{
    int eof = 0;

    if(fgets(getterString,stringSize,stdin)== NULL)
    {
        strcpy(getterString,"EOF Reached");
        printf("EOF Reached, Stop Reading\n");
        eof  = 1;
    }
    return eof;
}