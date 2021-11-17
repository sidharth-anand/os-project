"""
    File for running the algorithm for n values from 1 to 1 million
"""
import os
from math import ceil
import pandas as pd
from tqdm import tqdm
from multiprocessing import Pool, cpu_count

#Process data from performance file
def read_perf_from_file(path):
    result = []

    perf_file = open(path)
    for lines in perf_file.readlines():
        numbers = lines.split('-')
        result.append([float(i) for i in numbers[1:]])

    return result

#Add results to the the dataframes
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

#Run the algorithm
def run_C(process_data):
    start = process_data['start']
    end = process_data['end']
    step = process_data['step']
    file2_path = process_data['file2_path']
    file3_path = process_data['file3_path']
    perf_path = process_data['perf_path']
    csv_path = process_data['csv_path']

    df = pd.DataFrame(columns=['n','scheduler','st_1','st_2', 'st_3','wt_1','wt_2','wt_3','tat_1','tat_2','tat_3'])

    f1 = open(file2_path, 'w')
    f2 = open(file3_path, 'w')

    for i in range(1, start * step):
        f1.write(str(i) + '\n')
        f2.write(str(i) + '\n')

    for i in tqdm(range(start,end),position=pid):
        for j in range((i-1) * step, i*step + 1):
            f1.write(str(j) + '\n')
            f2.write(str(j) + '\n')

        n = (i-1)*1000 + 1
    
        os.system(f'./a.out {n} 1 1 {file2_path} {file3_path} {perf_path} > /dev/null')
        df = append_to_df(df,n,'rr',read_perf_from_file(perf_path))

        os.system(f'./a.out {n} 1 2 {file2_path} {file3_path} {perf_path} > /dev/null')
        df = append_to_df(df,n,'fcfs',read_perf_from_file(perf_path))
    
    df.to_csv(csv_path)
    f1.close()
    f2.close()

#Main code to combine and run above functions
compile_command = 'gcc ./src/main.c ./src/source/app.c ./src/source/pipeTransport.c ./src/source/processes.c ./src/source/performance.c ./src/source/schedulers.c ./src/source/threadUtils.c ./src/source/utils.c -pthread -Wno-int-to-pointer-cast'
os.system(compile_command + ' > graph/compile.log')

#Set parameters
step = 1000
range_ = 1000000
processes = cpu_count()
num_steps = ceil(range_ / step)
steps_per_process = ceil(num_steps / processes)
print(num_steps,steps_per_process)

split_data = []
pid = 0
for i in range(1,num_steps,steps_per_process):
    split_data.append({
        "start":i,
        "end": i+steps_per_process,
        'file2_path': f'data/file2_{pid}.txt',
        'file3_path': f'data/file3_{pid}.txt',
        'perf_path': f'performance/perf_{pid}.txt',
        'csv_path': f'csvs/data_{pid}.csv',
        'step':step,
        'pid':pid

    })
    pid += 1

print(split_data)

#Run via multi-core processing
pool = Pool(processes=processes)

try:
    print("Started {} processes..".format(processes))
    pool.map(run_C, split_data)
    # Wait until all parallel processes are done and then execute main script
    pool.close()
    pool.join()

except KeyboardInterrupt:
    pool.close()
    pool.join()
    

