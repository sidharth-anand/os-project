import os
import pandas as pd
from tqdm import tqdm

def read_perf_from_file():
    result = []

    perf_file = open('performance/perf.txt')
    for lines in perf_file.readlines():
        numbers = lines.split('-')
        result.append([float(i) for i in numbers[1:]])

    return result

def append_to_df(df, n, scheduler, result):
    return df.append({
        
        'n': n,
        'scheduler': scheduler,
        'st_1': result[0][0],
        'st_2': result[1][0],
        'st_3': result[2][0],
        'wt_1': result[0][1],
        'wt_2': result[1][1],
        'wt_3': result[2][1],
        'tat_1': result[0][2],
        'tat_2': result[1][2],
        'tat_3': result[2][2],
    }, ignore_index=True)

compile_command = 'gcc ./src/main.c ./src/source/app.c ./src/source/pipeTransport.c ./src/source/processes.c ./src/source/performance.c ./src/source/schedulers.c ./src/source/threadUtils.c ./src/source/utils.c -pthread -Wno-int-to-pointer-cast'
os.system(compile_command + ' > graph/compile.log')

f1 = open('data/file2.txt', 'w')
f2 = open('data/file3.txt', 'w')

df = pd.DataFrame(columns=['n','scheduler','st_1','st_2', 'st_3','wt_1','wt_2','wt_3','tat_1','tat_2','tat_3'])

for i in tqdm(range(1, 1000000, 1000)):
    f1.write(str(i) + '\n')
    f2.write(str(i) + '\n')

    os.system(f'./a.out {i} 1 1 data/file2.txt data/file3.txt > graph/rr.log')
    df = append_to_df(df, i, 'rr', read_perf_from_file())

    os.system(f'./a.out {i} 1 2 data/file2.txt data/file3.txt > graph/fcfs.log')
    df = append_to_df(df, i, 'fcfs', read_perf_from_file())

f1.close()
f2.close()

df.to_csv('graph/data.csv')
