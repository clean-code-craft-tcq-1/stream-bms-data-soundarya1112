import unittest
import bms_sender_data

class test_battery_current_ranges(unittest.TestCase):
  
    def test_bms_limits(self):
        self.assertTrue(bms_sender_data.battery_is_ok({'temperature': 15,'state_of_charge': 65, 'charge_rate': 0.6}) is True) 
        self.assertTrue(bms_sender_data.battery_is_ok({'temperature': 70,'state_of_charge': 90, 'charge_rate': 0.9}) is False)  
        
    def test_bms_param_generation(self):
        battery_param = bms_sender_data.bms_parameters_generation()
        self.assertTrue(bms_param['temperature'])
        self.assertTrue(bms_param['state_of_charge'])

      
if __name__ == '__main__':
  unittest.main()
