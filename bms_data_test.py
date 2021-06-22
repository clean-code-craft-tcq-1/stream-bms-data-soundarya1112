import unittest
import bms_sender_data

class test_battery_current_ranges(unittest.TestCase):
  
    def test_bms_limits(self):
        self.assertTrue(bms_sender_data.battery_is_ok({'temperature': 15,'state_of_charge': 65, 'charge_rate': 0.6}) is True) 
        self.assertTrue(bms_sender_data.battery_is_ok({'temperature': 70,'state_of_charge': 90, 'charge_rate': 0.9}) is False)  
        
    def test_bms_parameters_generation(self):
        bmsparams = bms_sender_data.bms_parameters_generation()
        bmsparamkeys = list(bmsparams.keys())
        self.assertFalse(bmsparamkeys == ['charge_rate', 'soc'])

    def test_streaming_bms_readings(self):
        bms_sender_data.streaming_bms_readings(5)
        
    
if __name__ == '__main__':
  unittest.main()
