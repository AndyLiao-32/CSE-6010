# CSE 6010 - Computational Problem Solving
# Assignment 7 - Monte Carlo Integration using OpenMP

## Instructions of the compiler and operating system 

 I used "sublime" as my text editor, then I compiled and ran the whole program on the PACE-ICE.

 For the whole compiling and executing process, the following steps will lead you to successfully complete it.

 * First, connect to the VPN of GATech and open the terminal.

 * Then, simply type the command "ssh GTusername@coc-ice.pace.gatech.edu" to login to the PACE-ICE

 * I uploaded the c file using FileZilla.

 * Type in "qsub -I -q coc-ice -l nodes=1:ppn=20 -l walltime=00:60:00" to set the parallel computing environment (the number of ppn can be adjusted, in my case, it could be changed to 8 because I set the MAX_Threads to be 8 in my program).

 * Type in "gcc -o ./montecarlo montecarlo.c -fopenmp -lm" to compile the program. 

 * Type in "./montecarlo" to execute the program. 

 * The result will show on the screen.

 Therefore, by compiling on the operating system (MacOS), our compiler is "clang", version - 1000.10.44.4.