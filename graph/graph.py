import pandas as pd
import seaborn as sb

df = pd.read_csv('graph/data.csv')

n = df['n'].to_numpy()

wt_1 = df['wt_1'].to_numpy()

sb.lineplot(x=n,y=wt_1)

