* In case files get corrupt, live version available on NCSU GitHub at: 
    https://github.ncsu.edu/jmskripc/Program2

1. To compile the C++ code:

    dependency: gcc version 7.5.0 
    tested on NCSU VCL: Ubuntu 18.04 LTS Base
    shell-command: bash compile.sh

    
2. File Description:

==usage==
   compile.sh: shell script wrapper to compile the code
        use: bash compile.sh
   
   run_apsp.sh: shell script wrapper to run the code
        use: bash run_apsp.sh [f/dw] [path-to-input-.gph-file] > output.out
        
   silent_run_apsp.sh: same as run_apsp.sh except that stdout is redirected to /dev/null 
        use: bash silent_run_apsp.sh [f/dw] [path-to-input-.gph-file]

==code==
   dependencies.h: contains imports of C++ packages
   utils.cpp: contains utility functions required to write graph-search algorithms including
                reading graphs from files; printing graphs for debugging, implementation of 
                D-ary heap, etc.
   all_shortest_path_algos.cpp: includes implementation of Dijkstra's Single-source shortest
                paths algorithm and Floyd-Warshall algorithm.
                
   controller_main.cpp: this is the main program that controls the flow. It takes user instructions
                        as command-line arguments and calls appropriate functions to provide output 
                        on standard-out and standard-error.
   
==misc==        
   collaborators.csv: names and emails of team-members 
   Fahad Alqahtani (fsalqath)
    
