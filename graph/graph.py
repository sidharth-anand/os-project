"""
    File used to generate plots for comparing waiting times, turn around times with number of inputs for the 2 scheduling algorithms
"""
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from seaborn.rcmod import set_style

#Concatenate the geenrated CSVs
li = []
for i in range(8):
    df = pd.read_csv(f'csvs/data_{i}.csv', index_col=None)
    li.append(df)
df = pd.concat(li, axis=0, ignore_index=True)

#Pre-processing the data for generating graphs
rr = df[df['scheduler'] == 'rr']
fcfs = df[df['scheduler'] == 'fcfs']

rr_start = pd.melt(rr,id_vars=['n'], value_vars=['st_1','st_2','st_3'])
rr_wait = pd.melt(rr,id_vars=['n'], value_vars=['wt_1','wt_2','wt_3'])
rr_tat = pd.melt(rr,id_vars=['n'], value_vars=['tat_1','tat_2','tat_3'])

fcfs_start = pd.melt(fcfs,id_vars=['n'], value_vars=['st_1','st_2','st_3'])
fcfs_wait = pd.melt(fcfs,id_vars=['n'], value_vars=['wt_1','wt_2','wt_3'])
fcfs_tat = pd.melt(fcfs,id_vars=['n'], value_vars=['tat_1','tat_2','tat_3'])

sns.set(rc = {'figure.figsize':(32,20)})
sns.set_style('dark')

#Round Robin
#Start Time
p = sns.lineplot(x='n',y='value',data=rr_start,hue='variable')
p.set_ylabel('Time')
plt.show()
#Waiting Time
p = sns.lineplot(x='n',y='value',data=rr_wait,hue='variable')
p.set_ylabel('Time')
plt.show()
#Turn Around Time
p = sns.lineplot(x='n',y='value',data=rr_tat,hue='variable')
p.set_ylabel('Time')
plt.show()

##FCFS
#Start Time
p = sns.lineplot(x='n',y='value',data=fcfs_start,hue='variable')
p.set_ylabel('Time')
plt.show()
#Wait Time
p = sns.lineplot(x='n',y='value',data=fcfs_wait,hue='variable')
p.set_ylabel('Time')
plt.show()
#Turn Around Time
p = sns.lineplot(x='n',y='value',data=fcfs_tat,hue='variable')
p.set_ylabel('Time')
plt.show()