def check_and_alert(battery_inputs,bmsParam_value,alertTarget):
  return (alertType[alertTarget](battery_inputs,bmsParam_value))

def send_to_controller(breachType):
  header = 0xfeed
  print(f'{header}, {breachType}')
  return f'{header}, {breachType}'
  
def send_to_console(battery_inputs,bmsParam_value):
  print(battery_inputs)
  for values in bmsParam_value:
      print(values)
  return True

def send_to_email(breachType):
  recepient = "a.b@c.com"
  print("breachtypes")
  return True
    
alertType = {"TO_CONTROLLER": send_to_controller, "TO_EMAIL" : send_to_email, "TO_CONSOLE" : send_to_console}
