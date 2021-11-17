1. FCFS:

-Start times vs N - 
--P1 will have a start time of 0. 
--P2 will have a start time close to 0, due to P1 having less computation time requirement
--P3 will have a start time very high, as P2 takes a long time to complete

-Wait times vs N -
--P1 will have a wait time equal to 0. 
--P2 will have a wait time close to 0, due to P1 having less computation time requirement
--P3 will have a wait time very high, as P2 takes a long time to complete

-Turn around time vs N -
--P1 will have a low turn around time, as it is not IO intensive
--P2 will have a high turn around time, due to the IO requirement of reading and writing it back
--P3 will have a slightly higher turn around time, as it has to wait for more time idly, despite lesser execution time

2. RR:

-Start Times vs N -
--P1, P2 and P3 will have start times evenly spaced out equal to the time quantum, due to how round robin schedules

-Wait Times vs N - 
--P2 and P3 have similar wait times, as the work done in each quanta becomes equivalent for high values
--P1 has the least wait time, as it is less intensive compared to the other 2


-Turn Around Times vs N - 
-- Turn around time for P2 will be the highest, due to the necessity of reading from a file and printing out to a console, the most IO intensive process
-- Turn around time for P3 will be lower than P2, as it reads from a file and adds, as compared to printing out in P2
-- Turn around time for P1 will be the least, as it has the lowest waiting and the lowest execution

Inferences:-
1. RR - TAT and WT for P1 starts increasing after 800, as it needs more waiting time. This in turn leads to a higher WT and TAT for P2 and P3.
2. FCFS leads to the least total time required for all 3 processes for all N, compared to RR
3. P3 performs considerably less efficient in FCFS as compared to RR, as it needs to wait for a considerably larger time, offsetting its lesser execution time compared to the P2

Graphs to view these are in the graph folder