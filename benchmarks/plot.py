import pandas as pd
import matplotlib.pyplot as plt
import sys

df = pd.read_csv(sys.argv[1])
plt.figure(figsize=(10, 6))
for impl in df["impl"].unique():
    sub = df[df["impl"] == impl]
    plt.plot(sub["dim"], sub["time_us"], marker="o", label=impl)

plt.xlabel("Dimensione input (N)")
plt.ylabel("Tempo (us)")
plt.title("Benchmark FFT")
plt.legend()
plt.grid(True)
plt.xscale("log", base=2)
plt.tight_layout()
plt.show()
