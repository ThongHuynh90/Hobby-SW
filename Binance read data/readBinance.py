import requests
import time
import numpy as np
import h5py as hdf
from datetime import datetime

BUFFER_SIZE=10000
saveDataBuffer = np.zeros(BUFFER_SIZE)
saveTimeBuffer = np.zeros(BUFFER_SIZE)
i=0
while True:
    try:
        if( i<BUFFER_SIZE):
            response = requests.get('https://www.binance.com/api/v3/ticker/price?symbol=BTCUSDT')
            saveTimeBuffer[i] = datetime.timestamp(datetime.now()) #convert back to datatime by datetime.fromtimestamp(saveTimeBuffer[i])
            data = response.json()
            saveDataBuffer[i]=float(data['price'])
           # print(data)
            i=i+1
        else:
            i=0
            now = datetime.now()
            fileName = now.strftime("%Y%m%d%H%M%S")
            hf = hdf.File(fileName + '.h5', 'w')
            hf.create_dataset('Price', data=saveDataBuffer)
            hf.create_dataset('Time', data=saveTimeBuffer)
            hf.create_dataset('Name', data='BTCUSDT')
            hf.close()

    except requests.exceptions.RequestException as e:
        print('Error:', e)
    
    time.sleep(2)  # wait for 1 second before making the next request