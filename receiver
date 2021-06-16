import pandas as pd
import bms_sender_data

numlist = bms_sender_data.streaming_bms_readings(5)

window_size = 3

num_series = pd.Series(numlist)

windows = num_series.rolling(window_size)

moving_averages = windows.mean()

moving_averages = moving_averages.tolist()

moving_averages_without_nans = moving_averages_list[window_size - 1:]

print(moving_averages_without_nans)
