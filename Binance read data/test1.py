
import yfinance as yf
from matplotlib import pyplot as plt
df = yf.download("BTC-USD", interval="1m", period="7d")

plt.figure(1)
plt.plot(df["Volume"].values)

plt.figure(2)
plt.plot(df["Open"].values)

plt.plot(df["High"].values)
plt.plot(df["Close"].values)


plt.show()
