#include "bms_rx-data.h"


BatParams_s BatteryData[NumberOfParameters] = {{"temperature", TEMPERATURE_MIN , TEMPERATURE_MAX},
                                                  {"charge_rate", CHARGERATE_MIN , CHARGERATE_MAX}};

UpdateSMAData UpdateSMADataParam[NumberOfParameters] = {UpdateTemperature , UpdateChargeRate};


void BMSDataReceiveFromConsole()
{
    int batteryParamIterater;
    int eofReached = 0; 

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
        for (int batteryParamIterater=0 ; batteryParamIterater < NumberOfParameters; batteryParamIterater++)
        {
            BMSParamValueRx[batteryParamIterater] = getParameterFromConsole(str,(BmsParameters_e)batteryParamIterater);
            
            if(IsWithinRange(BMSParamValueRx[batteryParamIterater], BatteryParam[batteryParamIterater].minValue , BatteryParam[batteryParamIterater].maxValue))
            {
                BatteryParamEvaluated[batteryParamIterater].SMA =  movingAverageValue((ReadingsBuffer[batteryParamIterater]), (ReadingsSum+batteryParamIterater), batteryParamIterater, SMA_RANGE, BMSParamValueRx[batteryParamIterater]);
                
                BatteryParamEvaluated[batteryParamIterater].minRxd = MinimumValue(BMSParamValueRx[batteryParamIterater],BatteryParamEvaluated[batteryParamIterater].minRxd);
                
                BatteryParamEvaluated[batteryParamIterater].maxRxd = MaximumValue(BMSParamValueRx[batteryParamIterater],BatteryParamEvaluated[batteryParamIterater].maxRxd);
                
                UpdateParamSMAData[batteryParamIterater](BatteryParamEvaluated[batteryParamIterater]);
                
            }
            else
            {
               UpdateParamSMAData[batteryParamIterater](INVALID_VALUE_s);
            } 
           
           #if(TEST_MODE)
        printf("Temperature:%f, ChargeRate:%f\n",BMSParamValueRx[0],BMSParamValueRx[1]);
        printf("SMA Temperature:%f, ChargeRate:%f\n",BatteryParamEvaluated[0].SMA,BatteryParamEvaluated[1].SMA);
        printf("Min Temperature:%f, ChargeRate:%f\n",BatteryParamEvaluated[0].minRx,BatteryParamEvaluated[1].minRx);
        printf("Max Temperature:%f, ChargeRate:%f\n\n",BatteryParamEvaluated[0].maxRx,BatteryParamEvaluated[1].maxRx);
        #endif      
           
        }
    }while((!isStopRequestedByUser) || (eofReached != 1))

}


float getParameterFromConsole(char *getLine, BmsParameters_e BatParam)
{
  char splitStrCategory[NumberOfParameters*2][12]={'\0'};
  char splitStrParams[NumberOfParameters*2][12]={'\0'};
  char *tokenCategory;
  char *tokenParams;  
  int k=0, p =0;
  float temp;
  char buffer[MAXLENGTH];
  char pyString[MAXLENGTH];
  
  strcpy(buffer,getLine);
  tokenCategory = strtok (buffer,",");
  
  while (tokenCategory != NULL)
  {
    
    strcpy((splitStrCategory[k]),tokenCategory);
    k++;
    tokenCategory = strtok (NULL, ",");
  }

  for(int r = 0; r < (NumberOfParameters); r++)
  {
	tokenParams = strtok ((splitStrCategory[r]), ":");
	
	while(tokenParams != NULL)
	{
		strcpy((splitStrParams[p]), tokenParams);
		p++;
		tokenParams = strtok (NULL, ":")
	}
  }
  
  for(int j=0;j < (NumberOfParameters*3);j=j+2)
  {
      pyString = "'" + BatteryData[BatParam].ParameterName + "'";
      printf("pyString value : %s ", pyString);
      if(strcmp((splitStrParams[j]), pyString) == 0)
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
    #if(TEST_MODE)
    strcpy(getterString,strInput[TestCount[TEMPERATURE]]);
    #else

    if(fgets(getterString,stringSize,stdin)== NULL)
    {
        strcpy(getterString,"EOF Reached");
        printf("EOF Reached, Stop Reading\n");
        eof  = 1;
    }
    #endif
    return eof;
}