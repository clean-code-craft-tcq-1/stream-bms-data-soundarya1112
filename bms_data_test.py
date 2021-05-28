import unittest
import bms_sender_data

class test_battery_current_ranges(unittest.TestCase):
  
    def test_bms_limits(self):
        self.assertTrue(bms_sender_data.battery_is_ok({'temperature': 15,'state_of_charge': 65, 'charge_rate': 0.6}) is True) 
        self.assertTrue(bms_sender_data.battery_is_ok({'temperature': 70,'state_of_charge': 90, 'charge_rate': 0.9}) is False)  
      
 if __name__ == '__main__':
  unittest.main()
