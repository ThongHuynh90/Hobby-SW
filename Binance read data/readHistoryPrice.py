import requests
import json
import pandas as pd
from datetime import datetime

# set the API endpoint
endpoint = 'https://api.binance.com/api/v3/klines'

# set the parameters
symbol = 'BTCUSDT' # cryptocurrency pair
interval = '1d' # time interval for the candles (1 day)
limit = 90 # number of candles to fetch (max. 1000)
startTime = int((datetime.now().timestamp() - (limit * 24 * 60 * 60)) * 1000) # start time for the data (90 days ago)

# set the query parameters
params = {
    'symbol': symbol,
    'interval': interval,
    'limit': limit,
    'startTime': startTime
}

# send the request and get the response
response = requests.get(endpoint, params=params)

if response.ok:
    # convert the response data to a Pandas DataFrame
    data = json.loads(response.text)
    df = pd.DataFrame(data, columns=['Open time', 'Open', 'High', 'Low', 'Close', 'Volume', 'Close time', 'Quote asset volume', 'Number of trades', 'Taker buy base asset volume', 'Taker buy quote asset volume', 'Ignore'])
    df['Open time'] = pd.to_datetime(df['Open time'], unit='ms')
    df = df.set_index('Open time')
    df.index.name = None
    df = df[['Open', 'High', 'Low', 'Close', 'Volume']]
    
    print(df)
else:
    print(f'Error fetching data: {response.status_code}')
