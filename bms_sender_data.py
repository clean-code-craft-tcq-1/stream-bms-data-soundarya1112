import random
import time

battery_allowedValues = {
        'temperature'      : {'min': 0, 'max': 45},
        'state_of_charge'  : {'min': 20, 'max': 80},
        'charge_rate'      : {'min': 0,'max': 0.8}
                     }

def battery_validationcheck(battery_inputs):
        outOfIndex_Values = []
        for bmsParam_name,bmsParam_value in battery_inputs.items() :
            battery_Limit_Check(bmsParam_name,bmsParam_value,outOfIndex_Values)
        return outOfIndex_Values
      
def battery_Limit_Check(bmsParam_name,bmsParam_value,outOfIndex_Values): 
        if (bmsParam_value < battery_allowedValues[bmsParam_name]['min']) or (bmsParam_value > battery_allowedValues[bmsParam_name]['max']):
            outOfIndex_Values.append(bmsParam_name)
       
                   
def battery_is_ok(battery_inputs):
        battery_range_check = battery_validationcheck(battery_inputs)
        if len(battery_range_check) == 0:
            return True
        else :
            return False
          
def bms_parameters_generation():
        bms_params = {}
        bms_params["temperature"] = random.randint(battery_allowedValues['temperature']['min'],battery_allowedValues['temperature']['max'])
        bms_params["state_of_charge"] = random.randint(battery_allowedValues['state_of_charge']['min'], battery_allowedValues['state_of_charge']['max'])
        bms_params["charge_rate"] = random.randint(battery_allowedValues['charge_rate']['min'], battery_allowedValues['charge_rate']['max'])   
        return bms_params

def _streaming_bms_readings(max_count):
        bmsparams_count = 0
        while(bmsparams_count < max_count):
             print(bms_parameters_generation())
             bmsparams_count += 1
             time.sleep(3)
          
