# DMP-MLC
---------------------------------------

How to compile and create the executable
----------------------------------------

$ g++ Read.cpp Greedy.cpp SA.cpp HC.cpp TSP.h TSPSolver.cpp -o tsp

--------------------------------------------------------------------------------

How to run tsp.exe
--------------------
tsp.exe takes 4 input arguments and must be input in the following order:

 i) the filename of a dataset
 ii) the cut-off time (in seconds) 
 iii) the method to use 
 iv) a random seed

For i), the dataset must have the same format as in TSPLIB.
For iii), use specific name to indicate which method you want to use:

"Greedy"------ greedy with farthest insertion
"LS1"--------- Iterated Hill Climbing
"LS2"--------- Simulated Annealing

For example:

If you want to use Iterated Hill Climbing, write in the command line:

./tsp burma14.tsp 10 LS1 3
