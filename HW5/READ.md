# CSE 6010 - Computational Problem Solving
# Assignment 5 - Total Amazement

## Instructions of the compiler and operating system 

 We use "sublime" as our text editor this time, and we compile our maze_solve program via typing the command "make" on the Mac terminal, which will execute the makefile. In the makefile, we have already set up the compiler, gcc. Even though MacOS uses clang as the compiler, the command "gcc" will automatically transform to execute the clang. For the maze_generate program, we simply compile it in the terminal by typing "gcc -o ./maze_generate maze_generate.c". 

 After compiling, we can simply type "cd /Users/..../tliao32" to get to the file directory, and we have to type in the following:

 * Type in "./main_generate maze_adjacency_list.txt 10 10" in order to fulfill the requirement of the initial input to execute the maze generating program. 

 * After generating the maze, we can type in "./main_solve maze_adjacency_list.txt" to execute the maze solution program. 

 Therefore, by compiling on the operating system (MacOS), our compiler is "clang", version - 1000.10.44.4.
